#include "Itinerary.h"

Itinerary::Itinerary(bool allow_copy):
                items(),
                items_paid(),
                is_paid_(false),
                company_(""),
                user_payment_(),
                allow_copy_(allow_copy)
{}

///start-> Copy constructor + deep copy methods

void Itinerary::get_deep_copy_(const Itinerary& itinerary)
{
    if(items.size()!=0)
        throw std::invalid_argument("The itinerary must be empty to get deep copy.");

    for (auto i : itinerary.items)
    {
        this->items.push_back(i->clone());
    }
    items_paid= itinerary.items_paid;
    is_paid_= itinerary.is_paid_;
    company_= itinerary.company_;
    user_payment_= itinerary.user_payment_;
    allow_copy_= itinerary.allow_copy_;
}


Itinerary::Itinerary(const Itinerary& itinerary)
{
    if(!itinerary.allow_copy_)
        throw std::invalid_argument("Copy constructor called and allow_copy==false\nPlease use get_deep_copy method or change allow_copy to true.");
    
    get_deep_copy_(itinerary);
}

void Itinerary::get_deep_copy(const Itinerary& itinerary)
{
    get_deep_copy_(itinerary);
}

void Itinerary::get_deep_copy(const Itinerary* const itinerary)
{
    get_deep_copy_(*itinerary);
}

/// End -> Copy constructor + deep copy methods

int Itinerary::get_number_of_items() const
{
    return items.size();
}

bool Itinerary::is_paid() const
{
    return is_paid_;
}

const std::vector<bool>& Itinerary::get_items_paid() const
{
    return items_paid;
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

void Itinerary::pay(const std::string& company, const PaymentInfo& user_payment)
{
    //Need another check from API (if it's valid) //Future Update
    if(user_payment.is_empty())
    {
        auto e{"Can't pay with empty payment info."};
        throw std::invalid_argument(e);
    }

    user_payment_= user_payment;
    company_= company;
    auto payment{PaymentFactory::create_payment_helper(company_)}; //heap (delete needed)

    for (int i = 0; i < (int)items.size(); i++)
    {
        //if the item didn't already paid. 
        if(!items_paid[i])
        {
            //reserve the item then pay it

            auto reserve_success{items[i]->reserve()}; 
            if(! reserve_success)
                continue;

            auto pay_success{payment->company_transfer(user_payment_, CompanyTransferInfo{items[i]->get_pay_info()})};
            if(! pay_success)
            {
                //if the reservation is successful and the pay isn't we need to cancel the reservation.
                items[i]->cancel_reserve(); //if cancel reservation didn't success //Future Update
                continue;
            }

            items_paid[i]= true;
        }
    }

    delete payment;
    is_paid_= true;
}

void Itinerary::cancel_pay()
{
    if(!is_paid_)
    {
        //return;
        auto e{"You can't cancel pay without pay the itinerary."};
        throw std::invalid_argument(e);
    }
    
    auto payment{PaymentFactory::create_payment_helper(company_)};//heap (delete needed)


    for (int i = 0; i < (int)items.size(); i++)
    {
        if(items_paid[i])
        {
            payment->company_transfer(user_payment_, CompanyTransferInfo{items[i]->get_pay_info()});
            items[i]->cancel_reserve();
        }
    }

    for (int i = 0; i < (int)items_paid.size(); i++)
        items_paid[i]= false;

    company_= "";
    user_payment_= PaymentInfo{};
    delete payment;
    is_paid_= false;    
}

std::string Itinerary::print() const
{
    auto msg{std::string{}};
    if(is_paid_)
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
        msg+= "----------------------\n";
        
        if(is_paid_)
            if(items_paid[i])
                msg+= "=-=-= Item  Paid =-=-=\n";
            else
                msg+= "=+= Item  Not Paid =+=\n";
        else
            msg+= "=+= Item  Not Paid =+=\n";

        msg+= "Type and company: " + info.get_item_type()+" -> "+info.get_item_company()+"\n";
        msg+= "Service: " + pay_info[2] +"\n";
        msg+= "Price: " + pay_info[1].erase(pay_info[1].length()-4) +"\n";

        if(info.get_printing_info()!="")
            msg+= "More info: " + info.get_printing_info() + "\n";
    }
    msg+= "----------------------\n";
    msg+= "######################\n";    
    msg+= "Total Price: "+ std::to_string(get_total_cost()).erase(std::to_string(get_total_cost()).length()-4)+"\n";
    msg+= "######################\n";
    return msg;
}

void Itinerary::add_room(const Room& room, int number_of_nights, const std::string& printing_info)
{
    items.push_back(new items_::HotelItem{room, number_of_nights, printing_info});
    items_paid.push_back(false);
}

void Itinerary::add_flight(const Flight& flight, const std::string& printing_info)
{
    items.push_back(new items_::FlightItem{flight, printing_info});
    items_paid.push_back(false);
}

void Itinerary::remove_item(unsigned int idx)
{
    if(idx > items.size()-1)
        throw std::invalid_argument("Invalid index");

    if(items_paid[idx])
        //Cancel reservation before delete the item
        items[idx]->cancel_reserve(); //if it's false + cancel pay and return money //Future Updates

    delete items[idx];
    items.erase(items.begin()+idx);
}

Itinerary::~Itinerary()
{
    //for (int i = 0; i < items.size(); i++)
    long long unsigned int size{items.size()};
    for (int i = 0; i < size; i++)
    {
        //call the destructor of the children (because the base class' destructor is virtual) + free the heap memory 
        remove_item(0); //remove the first item and erase it till the vector cleared
    }

    items.clear();
}