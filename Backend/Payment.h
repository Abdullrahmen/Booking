#ifndef Payment_H_
#define Payment_H_

#include "online_APIs\\PaymentOnlineAPI.h"
using namespace online_payment_api;
//Transfer info from users to companies
class CompanyTransferInfo
{
private:
    double money;
    std::string company_name;
    std::string service_info;
public:
    /// @brief Initilize all the members with thier values
    /// @param payment_info company name, money, service_info(details of the product)
    CompanyTransferInfo(std::vector<std::string> payment_info);

    //Castings
    CompanyTransferInfo(const StripeCompanyTransferInfo& stripe_info);
    CompanyTransferInfo(const PayPalCompanyTransferInfo& paypal_info);

    //Getters 
    const double& get_money() const;
    const std::string& get_comapany_name() const;
    const std::string& get_service_info() const;
    
    ~CompanyTransferInfo();
};

//General payment info class
class PaymentInfo
{
private:
    std::string name;
    std::string address;
    std::string id;
    std::string expire_date;
    int ccv;
public:
    //Initilize all the members with their default values
    PaymentInfo(const std::string& name="", const std::string& address="", const std::string& id="",
                const std::string& expire_date="", const int& ccv=0);

    //Getters
    const std::string& get_name() const;
    const std::string& get_address() const;
    const std::string& get_id() const;
    const std::string& get_expire_date() const;
    const int& get_ccv() const;

    const bool is_empty() const;
    ~PaymentInfo();
};

namespace payment_
{
    //Payments interface
    class IPayment
    {
    public:
        virtual bool company_transfer(const PaymentInfo& payment_info, const CompanyTransferInfo& transfer_info)=0;
    };

    //Converts from PayPal API to general IPayment interface
    class PayPalPayment: public IPayment
    {
    public:
        bool company_transfer(const PaymentInfo& payment_info, const CompanyTransferInfo& transfer_info) final;
    };

    //Converts from Stripe API to general IPayment interface
    class StripePayment: public IPayment
    {
    public:
        bool company_transfer(const PaymentInfo& payment_info, const CompanyTransferInfo& transfer_info) final;
    };
}

//Payments abstract factory
class PaymentFactory
{
private:
    //Supported payment methods
    static std::vector<std::string> payment_methods;
public:
    static payment_::IPayment* create_payment_helper(const std::string& payment_method);
    //Supported payment methods
    static const std::vector<std::string>& get_payment_methods();
};

#endif //Payment_H_