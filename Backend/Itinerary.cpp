#include "Itinerary.h"

Itinerary::Itinerary():
                items(),
                items_paid(),
                is_paid(false),
                company_(""),
                user_payment_()
{}

std::vector<bool> Itinerary::get_items_paid() const
{
    if (is_paid)
        return items_paid;
    
    auto e{"get_items_paid method can't called before pay the itinerary."};
    throw std::invalid_argument(e);// will call the destructor to free the heap memory
}

double Itinerary::get_total_cost() const
{
    auto total_cost {0.0}; //from now I'll try to use auto as much as possible
    for (auto i : items)
    {
        total_cost += std::stod(i->get_pay_info()[1]);
    }
    return total_cost;
}

void Itinerary::pay(std::string company, PaymentInfo user_payment)
{
    if(is_paid)
    {
        auto e{"Itinerary can't paid more than once."};
        throw std::invalid_argument(e);// will call the destructor to free the heap memory
    }

    user_payment_= user_payment;
    company_= company;
    auto payment{PaymentFactory::create_payment_helper(company_)}; //heap (delete needed)

    for (auto i : items)
    {
        //reserve the item then pay it

        auto reserve_success{i->reserve()}; 
        if(! reserve_success){items_paid.push_back(false); continue;}

        auto pay_success{payment->company_transfer(user_payment_, CompanyTransferInfo{i->get_pay_info()})};
        if(! pay_success)
        {
            //if the reservation is successful and the pay isn't we need to cancel the reservation.
            items_paid.push_back(false);
            i->cancel_reserve(); //if cancel reservation didn't success //later
            continue;
        }

        items_paid.push_back(true);
    }

    delete payment;
    is_paid= true;
}

void Itinerary::cancel_pay()
{
    if(!is_paid)
    {
        auto e{"You can't cancel pay without pay the itinerary."};
        throw std::invalid_argument(e);
    }
    
    auto payment{PaymentFactory::create_payment_helper(company_)};//heap (delete needed)

    for (auto i : items)
    {
        payment->company_transfer(user_payment_, CompanyTransferInfo{i->get_pay_info()});
        i->cancel_reserve();
    }
    
    items_paid.clear();
    company_= "";
    user_payment_= PaymentInfo{};
    delete payment;
    is_paid= false;    
}

void Itinerary::print() const
{
    auto msg{std::string{}};
    if(is_paid)
    {
        msg+= "=-=-=-=-==-=-=-=-=-=-=\n";
        msg+= "=-=-Itinerary Paid-=-=\n";
        msg+= "=-=-=-=-==-=-=-=-=-=-=\n";
    }
    else
    {
        msg+= "=-=-=-=-==-=-=-=-=-=-=\n";
        msg+= "=-Itinerary Not Paid-=\n";
        msg+= "=-=-=-=-==-=-=-=-=-=-=\n";
    }

    for (int i = 0; i < int(items.size()); i++)
    {
        auto pay_info {items[i]->get_pay_info()};
        auto info {items[i]->get_info()};
        msg+= "----------------------------\n";
        
        if(is_paid)
            if(items_paid[i])
                msg+= "=-=-=-=- Paid -=-=-=-=\n";
            else
                msg+= "=+=+=+ Not Paid +=+=+=\n";
        else
            msg+= "=+=+=+ Not Paid +=+=+=\n";

        msg+= "Type and company: " + info.get_item_type()+" -> "+info.get_item_company()+"\n";
        msg+= "Service: " + pay_info[2] +"\n";
        msg+= "Price: " + pay_info[1] +"\n";

        if(info.get_printing_info()!="")
            msg+= "More info: " + info.get_printing_info() + "\n";
    }
    msg+= "##########################\n";    
    msg+= "Total Price: "+ std::to_string(get_total_cost())+"\n";
    msg+= "##########################\n";
    std::cout<<msg;
}

void Itinerary::add_hotel(const Room& room, int number_of_nights, const std::string& printing_info)
{
    items.push_back(new items_::HotelItem{room, number_of_nights, printing_info});
}

void Itinerary::add_flight(const Flight& flight, const std::string& printing_info)
{
    items.push_back(new items_::FlightItem{flight, printing_info});
}

Itinerary::~Itinerary()
{
    for (auto i : items)
    {
        //call the destructor of the children (because the base class' destructor is virtual) + free the heap memory 
        delete i;
    }
    items.clear();
}