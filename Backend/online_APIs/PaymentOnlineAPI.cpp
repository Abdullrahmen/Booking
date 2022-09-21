#include "PaymentOnlineAPI.h"
using namespace online_payment_api;

/*
================
Stripe Payment
================
*/
//////////////////
//StripeCompanyTransferInfo Class
//////////////////

StripeCompanyTransferInfo::StripeCompanyTransferInfo(std::vector<std::string> payment_info):
    money(std::stod(payment_info[0])),
    company_name(payment_info[1]),
    service_info(payment_info[2]){}
const double& StripeCompanyTransferInfo::get_money() const {return money;}
const std::string& StripeCompanyTransferInfo::get_company_name() const {return company_name;}
const std::string& StripeCompanyTransferInfo::get_service_info() const {return service_info;}
StripeCompanyTransferInfo::~StripeCompanyTransferInfo(){}

//////////////////
//StripeUserInfo Class
//////////////////

StripeUserInfo::StripeUserInfo(const std::string& name, const std::string& address):name(name),address(address){}
const std::string& StripeUserInfo::get_name() const {return name;}
const std::string& StripeUserInfo::get_address() const {return address;}
StripeUserInfo::~StripeUserInfo(){}

//////////////////
//StripeCardInfo Class
//////////////////

StripeCardInfo::StripeCardInfo(const std::string& id, const std::string& expiry_date):id(id),expiry_date(expiry_date){}
const std::string& StripeCardInfo::get_id() const{return id;}
const std::string& StripeCardInfo::get_expiry_date() const{return expiry_date;}
StripeCardInfo::~StripeCardInfo(){}

//////////////////
//StripePaymentAPI Class
//////////////////

bool StripePaymentAPI::company_transfer(const StripeUserInfo& user, const StripeCardInfo& card, const StripeCompanyTransferInfo& transfer)
{return true;}


/*
================
PayPal Payment
================
*/
//////////////////
//PayPalCompanyTransferInfo Class
//////////////////

PayPalCompanyTransferInfo::PayPalCompanyTransferInfo(std::vector<std::string> payment_info):
    company_name(payment_info[0]),
    money(std::stod(payment_info[1])),
    service_info(payment_info[2]){}
const double& PayPalCompanyTransferInfo::get_money() const {return money;}
const std::string& PayPalCompanyTransferInfo::get_company_name() const {return company_name;}
const std::string& PayPalCompanyTransferInfo::get_service_info() const {return service_info;}
PayPalCompanyTransferInfo::~PayPalCompanyTransferInfo(){}

//////////////////
//PayPalCompanyTransferInfo Class
//////////////////

PayPalCreditCard::PayPalCreditCard(const std::string& name, const std::string& address,
                        const std::string& id, const std::string& expire_date, const int& ccv):
                        name(name),address(address),id(id),expire_date(expire_date),ccv(ccv){}
const std::string& PayPalCreditCard::get_name() const {return name;}
const std::string& PayPalCreditCard::get_address() const {return address;}
const std::string& PayPalCreditCard::get_id() const {return id;}
const std::string& PayPalCreditCard::get_expire_date() const {return expire_date;}
const int& PayPalCreditCard::get_ccv() const {return ccv;}
PayPalCreditCard::~PayPalCreditCard(){}

//////////////////
//PayPalOnlinePaymentAPI Class
//////////////////]

PayPalOnlinePaymentAPI::PayPalOnlinePaymentAPI():card(PayPalCreditCard{}){}
PayPalOnlinePaymentAPI::PayPalOnlinePaymentAPI(const PayPalCreditCard& card):card(card){}
void PayPalOnlinePaymentAPI::set_card(PayPalCreditCard card){this->card=card;}
bool PayPalOnlinePaymentAPI::company_transfer(const PayPalCompanyTransferInfo& transfer){return true;}