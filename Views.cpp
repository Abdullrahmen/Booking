/*
Contains:
* Customer view
* Admin view
* Utilz
*/

#include "Backend//User.h"
#include "Frontend//InputsMenu.h"
#include "Frontend//OptionsMenu.h"

/**************** Utilz ****************/

/// @return False
bool pre_menu() {return false;}

/// @brief Ask the user for payment info
/// @return empty PaymentInfo if there is a problem.
PaymentInfo ask_payment_info()
{
    try
    {
        auto error_msg{std::string{""}};
        //Loop until all info wrote correctly
        while (true)
        {
            std::cout<<"\033[2J\033[1;1H";//clear cmd
            std::cout<<error_msg;
            error_msg="";//reset error message

            InputsMenu menu;
            menu.add_input("Name", '\n');
            menu.add_input("Address", '\n');
            menu.add_input("Id", ' ');
            menu.add_input("Expire date", ' ');
            menu.add_input("ccv", ' '); //must check if it's int

            menu.run(false);

            //convert ccv to int
            int ccv{0};
            auto ccv_ {menu.get_answers()[menu.get_answers().size()-1]};
            try
            {
                ccv= std::stoi(ccv_);
            }
            catch(const std::exception& e)
            {
                error_msg+= "ccv invalid argument\n\n";
                continue;
            }

            auto &a{menu.get_answers()};
            return PaymentInfo{a[0], a[1], a[2], a[3], ccv};
        }
    }
    catch(const std::exception& e)
    {
        return PaymentInfo{};
    }
}

/// @brief List supported payment companies and ask the user to choose one.
/// @return Choosed payment company or an empty string if cancel
std::string find_payment_company()
{
    OptionsMenu menu{"Choose payment method:\n"};

    auto supported_methods {Data::get_payment_methods()};
    for (auto &i : supported_methods)
        menu.add_option(i);
    
    menu.add_option("Cancel", pre_menu);

    if(!menu.run())
        return "";

    return menu.get_choosed_option();
}

/// @brief Ask the user about the room details and list available rooms and hotels.
/// @return Choosed room or an empty room if cancel
Room find_room();

/// @brief Ask the user about the flight details and list available flights and airlines.
/// @return Choosed flight or an empty flight if cancel
Flight find_flight();

/**************** Finished Utilz ****************/

/// @brief Create a new itinerary and add it to the customer's itineraries (or cancel and won't add anything).
void create_new_itinerary(Customer& customer)
{
    auto itinerary{Itinerary{}};
    auto payment_company{std::string{""}};
    auto payment_info{PaymentInfo{}};

    // Itineary items loop.   
    while (true)
    {
        OptionsMenu menu{"Itinerary options: \n"};
        menu.add_option("Add flight");
        menu.add_option("Add room");
        if(itinerary.get_number_of_items()!=0)
        {
            if(!itinerary.is_paid())
            {
                menu.add_option("Pay");
                menu.add_option("Finish (without paying)");
            }
            else
            {
                for (auto i : itinerary.get_items_paid())
                    if(!i)
                    {
                        menu.add_option("Pay the rest");
                        break;
                    }
                    
                menu.add_option("Finish");
            }
        }
        menu.add_option("Cancel",pre_menu);

        if(!menu.run())
        {
            //Cancel reservations before cencel
            if(itinerary.is_paid())
                itinerary.cancel_pay();

            return;
        }

        if(menu.get_choosed_option()=="Add flight")
        {
            //Get choosed flight from user
            auto choosed_flight{find_flight()};

            //choosed flight is empty (cancel in find_flight func)
            if(choosed_flight.get_airlines()=="")
                continue; // begin of itinerary items loop
        }
        else if(menu.get_choosed_option()=="Add room")
        {
            //Get choosed room from user
            auto choosed_room{find_room()};

            //if choosed room is empty (cancel in find_room)
            if(choosed_room.get_hotel()=="")
                continue; // begin of itinerary items loop
        }
        else if(menu.get_choosed_option()=="Pay" || menu.get_choosed_option()=="Pay the rest")
        {
            if(payment_company!="")
            {
                OptionsMenu menu{"Do you want to use the same payment method? ("+payment_company+")\n"};
                menu.add_option("Yes");
                menu.add_option("No", pre_menu);
                if(!menu.run())
                    payment_company= "";
            }

            if(payment_company=="")
                payment_company= find_payment_company();

            if(payment_company=="")
                continue; // begin of itinerary items loop

            auto is_back{false};
            for (int i = 0; i < (int)Data::get_payment_methods().size(); i++)
            {
                if(payment_company== Data::get_payment_methods()[i])
                {
                    if(customer.get_payments()[i].is_empty()) 
                    {
                        // the user didn't put the payment info for the company
                        // Ask the user about the payment info
                        payment_info= ask_payment_info();
                        if(payment_info.is_empty())
                                is_back=true;// begin of itinerary items loop (because the user cancel in payment info asking       
                    }
                    else
                        payment_info= customer.get_payments()[i];
                        
                    break;
                }
            }
            if(is_back)
                continue;
            

            itinerary.pay(payment_company, payment_info);
            itinerary.print();
        }

    }// End itineary items loop
    customer.add_itinerary(itinerary);
}

// if return true will execute again else will back to main menu
bool customer_view(Customer& customer)
{
    std::cout<<"\033[2J\033[1;1H";
    std::cout<<"Hello "<<customer.get_name()<<" |*| Customer View\n";
    OptionsMenu menu;
    menu.add_option("Create new itinerary");
    menu.add_option("List my itineraries");
    menu.add_option("Remove itinerary");
    menu.add_option("Modify itinerary");
    menu.add_option("Log out", pre_menu);

    if(!menu.run(false))
        return false; //Back to main menu
    
    if(menu.get_choosed_option()=="Create new itinerary")
    {
        create_new_itinerary(customer);
        //execute this function from beggining.
        return true;
    }
    else if(menu.get_choosed_option()=="List my itineraries")
    {
        customer.print_itineraries();
    }

    //////////////////////
    return true;
}

bool admin_view(Admin admin)
{
    return false;
}
