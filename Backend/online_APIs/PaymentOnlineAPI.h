#ifndef PaymentOnlineAPI_H_
#define PaymentOnlineAPI_H_

#include <iostream>
#include <vector>

namespace online_payment_api
{
    //Stripe payment online API
    class StripeCompanyTransferInfo
    {
    private:
        double money;
        std::string company_name;
        std::string service_info;
    public:
        /// @param payment_info money, company name, service info(details of the product)
        StripeCompanyTransferInfo(std::vector<std::string> payment_info);
        //Getters 
        const double& get_money() const;
        const std::string& get_company_name() const;
        const std::string& get_service_info() const;
        
        ~StripeCompanyTransferInfo();
    };
    class StripeUserInfo
    {
    private:
        std::string name;
        std::string address;
    public:
        StripeUserInfo(const std::string& name, const std::string& address);
        const std::string& get_name() const;
        const std::string& get_address() const;
        ~StripeUserInfo();
    };
    class StripeCardInfo
    {
    private:
        std::string id;
        std::string expiry_date;
    public:
        StripeCardInfo(const std::string& id, const std::string& expiry_date);
        const std::string& get_id() const;
        const std::string& get_expiry_date() const;
        ~StripeCardInfo();
    };
    class StripePaymentAPI
    {
    public:
        static bool company_transfer(const StripeUserInfo& user, const StripeCardInfo& card, const StripeCompanyTransferInfo& transfer);
    };

    //Paypal payment online API
    class PayPalCompanyTransferInfo
    {
    private:
        double money;
        std::string company_name;
        std::string service_info;
    public:
        /// @param payment_info company name, money, service info(details of the product)
        PayPalCompanyTransferInfo(std::vector<std::string> payment_info);
        //Getters 
        const double& get_money() const;
        const std::string& get_company_name() const;
        const std::string& get_service_info() const;
        
        ~PayPalCompanyTransferInfo();
    };
    class PayPalCreditCard
    {
    private:
        std::string name;
        std::string address;
        std::string id;
        std::string expire_date;
        int ccv;
    public:
        PayPalCreditCard(const std::string& name="", const std::string& address="",
                        const std::string& id="", const std::string& expire_date="", const int& ccv=0);
        const std::string& get_name() const;
        const std::string& get_address() const;
        const std::string& get_id() const;
        const std::string& get_expire_date() const;
        const int& get_ccv() const;
        ~PayPalCreditCard();
    };
    class PayPalOnlinePaymentAPI
    {
    private:
        PayPalCreditCard card;
    public:
        PayPalOnlinePaymentAPI();
        PayPalOnlinePaymentAPI(const PayPalCreditCard& card);
        void set_card(PayPalCreditCard card);
        //after setting the card
        bool company_transfer(const PayPalCompanyTransferInfo& transfer);
    };
}
#endif //PaymentOnlineAPI_H_