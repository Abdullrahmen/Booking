#include "Payment.h"
using namespace payment_;

//////////////////
//CompanyTransferInfo Class
//////////////////

CompanyTransferInfo::CompanyTransferInfo(std::vector<std::string> payment_info):
    company_name(payment_info[0]),
    money(std::stod(payment_info[1])),
    service_info(payment_info[2]){}

CompanyTransferInfo::CompanyTransferInfo(const StripeCompanyTransferInfo& info):
    money(info.get_money()),company_name(info.get_company_name()),service_info(info.get_service_info()){}

CompanyTransferInfo::CompanyTransferInfo(const PayPalCompanyTransferInfo& info):
    money(info.get_money()),company_name(info.get_company_name()),service_info(info.get_service_info()){}

const double& CompanyTransferInfo::get_money() const{return money;}
const std::string& CompanyTransferInfo::get_comapany_name() const{return company_name;}
const std::string& CompanyTransferInfo::get_service_info() const{return service_info;}

CompanyTransferInfo::~CompanyTransferInfo(){}

//////////////////
//PaymentInfo Class
//////////////////

PaymentInfo::PaymentInfo(const std::string& name, const std::string& address, const std::string& id,
                const std::string& expire_date, const int& ccv):
                name(name),address(address),id(id),expire_date(expire_date),ccv(ccv){}

const std::string& PaymentInfo::get_name() const{return name;}
const std::string& PaymentInfo::get_address() const{return address;}
const std::string& PaymentInfo::get_id() const{return id;}
const std::string& PaymentInfo::get_expire_date() const{return expire_date;}
const int& PaymentInfo::get_ccv() const{return ccv;}

const bool PaymentInfo::is_empty() const 
{
    if(name=="" && address=="" && id=="" && expire_date=="" && ccv==0){return true;}
    return false;
}

PaymentInfo::~PaymentInfo(){}

//////////////////
//PayPalPayment Class
//////////////////

bool PayPalPayment::company_transfer(const PaymentInfo& payment_info, const CompanyTransferInfo& transfer_info)
{
    //Setting the card for the paypal api
    PayPalCreditCard paypal_card{payment_info.get_name(),payment_info.get_address(),payment_info.get_id(),
                                payment_info.get_expire_date(),payment_info.get_ccv()};
    PayPalOnlinePaymentAPI paypal_api{paypal_card};

    //in paypal api the order is company name, money, service info(details of the product)
    PayPalCompanyTransferInfo paypal_transfer_info{std::vector<std::string>{transfer_info.get_comapany_name(),
                                                                    std::to_string(transfer_info.get_money()),
                                                                    transfer_info.get_service_info()}};

    return paypal_api.company_transfer(paypal_transfer_info);
}

//////////////////
//StripePayment Class
//////////////////

bool StripePayment::company_transfer(const PaymentInfo& payment_info, const CompanyTransferInfo& transfer_info)
{
    //Setting the user for the stripe api
    StripeUserInfo stripe_user{payment_info.get_name(),payment_info.get_address()};
    //Setting the card for the stripe api
    StripeCardInfo stripe_card{payment_info.get_id(),payment_info.get_expire_date()};
    
    //in stripe api the order is money, company name, service info(details of the product)
    StripeCompanyTransferInfo stripe_transfer_info{std::vector<std::string>{std::to_string(transfer_info.get_money()),
                                                                    transfer_info.get_comapany_name(),    
                                                                    transfer_info.get_service_info()}};

    return StripePaymentAPI::company_transfer(stripe_user,stripe_card,stripe_transfer_info);
}

//////////////////
//PaymentFactory Class
//////////////////

std::vector<std::string> PaymentFactory::payment_methods{"PayPal","Stripe"};

IPayment* PaymentFactory::create_payment_helper(const std::string& payment_method)
{
    try
    {
        if(payment_method=="PayPal")
            return new PayPalPayment;
        else if(payment_method=="Stripe")
            return new StripePayment;
        else
            {
                std::string error_msg{"PaymentFactory class doesn't support \""};
                error_msg+= payment_method;
                error_msg+= "\" payment\nPlease make sure to choose one of the following supported payments: \n{";
                for (auto &payment_method : payment_methods)
                {error_msg+= payment_method;
                error_msg+= ",  ";}
                error_msg+= "}";
                throw std::invalid_argument(error_msg);
            }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
}
const std::vector<std::string>& PaymentFactory::get_payment_methods()
{
    return payment_methods;
}