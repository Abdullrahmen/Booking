#include "Flight.h"
#include "Hotel.h"
#include "Payment.h"

int main()
{    
    auto payment_pointer{PaymentFactory::create_payment_helper("PayPal")};

    std::cout<<payment_pointer->company_transfer(PaymentInfo{},CompanyTransferInfo{std::vector<std::string>{"Hilton Hotel","260.51","Room Reservation"}});
    
    delete payment_pointer;
    payment_pointer= nullptr;
    return 0;
}