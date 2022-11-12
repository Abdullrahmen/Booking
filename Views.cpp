/*
Contains:
* Customer view
* Admin view
* Utils
*/

#include "Backend//User.h"
#include "Frontend//InputsMenu.h"
#include "Frontend//OptionsMenu.h"
#include "Frontend//Utils.cpp"

/**************** Views Utils ****************/

/// @return False
bool pre_menu() {return false;}

/// @brief Convert flight to printing string
std::string flight2print_string(const Flight& flight)
{
    std::string str{};
    str+= "Airlines: " + flight.get_airlines();
    str+= " | ";
    str+= "From date/time: " + flight.get_datetime_from();
    str+= " | ";
    str+= "To date/time: " + flight.get_datetime_to();
    str+= " | ";
    auto s{std::to_string(flight.get_cost())};
    str+= "Cost: " + s.erase(s.length()-5);

    return str;
}

/// @brief Convert room to printing string
std::string room2print_string(const Room& room)
{
    std::string str{};
    str+= "Hotel: " + room.get_hotel();
    str+= " | ";
    str+= "From date/time: " + room.get_date_from();
    str+= " | ";
    str+= "To date/time: " + room.get_date_to();
    str+= " | ";
    str+= "Room type: " + room.get_room_type();
    str+= " | ";
    auto s{std::to_string(room.get_cost_per_night())};
    str+= "Cost per night: " + s.erase(s.length()-5);

    return str;
}

/// @brief Ask the user for payment info
/// @return empty PaymentInfo if there is a problem.
PaymentInfo ask_payment_info()
{
    try
    {
        //auto error_msg{std::string{""}};

        //clear_cmd_();//clear cmd
        //std::cout<<error_msg;
        //error_msg="";//reset error message

        InputsMenu menu;
        menu.add_input("Name", '\n');
        menu.add_input("Address", '\n');
        menu.add_input("Id", ' ');
        menu.add_input("Expire date", ' ');
        menu.add_input("ccv", ' ', 0, 1);

        menu.run(true);

        auto &a{menu.get_answers()};
        return PaymentInfo{a[0], a[1], a[2], a[3], std::stoi(a[4])};
    }
    catch(const std::exception& e)
    {
        return PaymentInfo{};
    }
}

/// @brief List the itineraries (in cmd) and ask the user to choose one
/// @param itineraries 
/// @return Choosed itinerary index (zero based) or -1 if cancel
int choose_itinerary(const std::vector<Itinerary>& itineraries)
{
    OptionsMenu menu{"Your itineraries: \n"};
    
    for (int i = 0; i < (int)itineraries.size(); i++)
        menu.add_option("\n"+itineraries[i].print());
    
    menu.add_option("Cancel", pre_menu);
    if(!menu.run())
        return -1;

    return menu.get_choosed_number()-1; // to make it zero based index
}

/// @brief List supported payment companies (in cmd) and ask the user to choose one.
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
Room find_room()
{
    while (true)
    {
        InputsMenu menu{"Room details: \n\n"};
        menu.add_input("Country", '\n', 0, 0, false);
        menu.add_input("City", '\n', 0, 0, false);
        menu.add_input("From date/time", '\n', 0, 0, false);
        menu.add_input("To date/time", '\n', 0, 0, false);
        menu.run();
        InputsMenu num_menu{""};
        num_menu.add_input("Number of adults", '\n', 0, 1, false);
        num_menu.add_input("Number of children", '\n', 0, 1, false);
        num_menu.run(false);

        const auto &answers{menu.get_answers()};
        std::vector<int> answers_int{};

        for (auto &i : num_menu.get_answers())
            answers_int.push_back(std::stoi(i));
        
        std::vector<Room> available_rooms{};

        //Get all available rooms from all hotels
        for (auto &i : HotelFactory::get_hotels())
        {
            auto hotel{HotelFactory::create_hotel_helper(i)};
            const auto &rooms{hotel->find_rooms(answers[0], answers[1], answers[2],
                                                answers[3], answers_int[0], answers_int[1])};
            available_rooms.insert(available_rooms.end(), rooms.begin(), rooms.end());
        }

        OptionsMenu av_menu{"Available rooms:\n\n"};

        for (auto &i : available_rooms)
            av_menu.add_option(room2print_string(i));

        av_menu.add_option("Change room details");
        av_menu.add_option("Cancel", pre_menu);

        if(!av_menu.run())
            return Room{};

        if(av_menu.get_choosed_option()=="Change room details")
            continue;

        return available_rooms[av_menu.get_choosed_number()-1];
    }
    
}

/// @brief Ask the user about the flight details and list available flights and airlines.
/// @return Choosed flight or an empty flight if cancel
Flight find_flight()
{
    while (true)
    {
        InputsMenu menu{"Flight details: \n\n"};
        menu.add_input("From date/time", '\n', 0, 0, false);
        menu.add_input("To date/time", '\n', 0, 0, false);
        menu.add_input("From", '\n', 0, 0, false);
        menu.add_input("To", '\n', 0, 0, false);
        menu.run();
        InputsMenu num_menu{""};
        num_menu.add_input("Number of infants", '\n', 0, 1, false);
        num_menu.add_input("Number of children", '\n', 0, 1, false);
        num_menu.add_input("Number of adults", '\n', 0, 1, false);
        num_menu.run(false);

        const auto &answers{menu.get_answers()};
        std::vector<int> answers_int{};

        for (auto &i : num_menu.get_answers())
            answers_int.push_back(std::stoi(i));
        
        std::vector<Flight> available_flights{};

        //Get all available flights from all airlines
        for (auto &i : FlightFactory::get_airlines())
        {
            auto airlines{FlightFactory::create_airlines_helper(i)};
            airlines->set_from_to_info(answers[0], answers[1], answers[2], answers[3]);
            airlines->set_passengers_info(answers_int[0], answers_int[1], answers_int[2]);
            const auto &flights{airlines->get_available_flights()};
            available_flights.insert(available_flights.end(), flights.begin(), flights.end());
        }

        OptionsMenu av_menu{"Available flights:\n\n"};

        for (auto &i : available_flights)
            av_menu.add_option(flight2print_string(i));

        av_menu.add_option("Change flight details");
        av_menu.add_option("Cancel", pre_menu);

        if(!av_menu.run())
            return Flight{};

        if(av_menu.get_choosed_option()=="Change flight details")
            continue;

        return available_flights[av_menu.get_choosed_number()-1];
    }
}

/**************** Finished Utils ****************/

/// @brief Modify itinerary (from user)
/// @param itinerary A pointer to the itinerary
/// @param payments {PayPal, Stripe} with same order and size 
/// (if size != number of supported payment methods -> will do nothing)
void modify_itinerary(Itinerary* itinerary, const std::vector<PaymentInfo>& payments)
{
    auto payment_company{std::string{""}};
    auto payment_info{PaymentInfo{}};

    //difference between the size of payments vector and the size of supported paymect methods.
    auto difference{(int)payments.size() < (int)Data::get_payment_methods().size()};
    if(difference!=0)
        return;

    // Itineary items loop.
    while (true)
    {
        OptionsMenu menu{"Itinerary options: \n"};
        menu.add_option("Add flight");
        menu.add_option("Add room");
        if(itinerary->get_number_of_items()!=0)
        {
            menu.add_option("Remove item /Soon");
            if(!itinerary->is_paid())
            {
                menu.add_option("Pay");
                menu.add_option("Finish (without paying)");
            }
            else
            {
                for (auto i : itinerary->get_items_paid())
                    if(!i)
                    {
                        menu.add_option("Pay the rest");
                        break;
                    }
                    
                menu.add_option("Finish");
            }
        }
        else
            menu.add_option("Cancel",pre_menu);
        
        if(!menu.run())
            return;

        if(menu.get_choosed_option()=="Add flight")
        {
            //Get choosed flight from user
            auto choosed_flight{find_flight()};

            //choosed flight is empty (cancel in find_flight func)
            if(choosed_flight.get_airlines()=="")
                continue; // begin of itinerary items loop

            itinerary->add_flight(choosed_flight);
        }
        else if(menu.get_choosed_option()=="Add room")
        {
            auto number_of_nights{int{0}};

            //Get choosed room from user
            auto choosed_room{find_room()};

            //if choosed room is empty (cancel in find_room)
            if(choosed_room.get_hotel()=="")
                continue; // begin of itinerary items loop

            /*Get number of nights*/
            InputsMenu menu{};
            menu.add_input("Number of nights",' ',3,1,false);
        
            while (true)
            {
                try
                {
                    menu.run(false);
                    number_of_nights= std::stoi(menu.get_answers()[0]);
                    if(number_of_nights<1)
                        throw std::invalid_argument("Please set a valid number");
                }
                catch(const std::exception& e)
                {
                    continue;
                }
                break;
            }
            
            itinerary->add_room(choosed_room, number_of_nights);
        }
        else if(menu.get_choosed_option()=="Remove item /Soon")
        {continue;}
        else if(menu.get_choosed_option()=="Pay" || menu.get_choosed_option()=="Pay the rest")
        {
            if(payment_company!="")
            {
                OptionsMenu menu{"Do you want to use the same payment method? ("+payment_company+")\n"};
                menu.add_option("Yes");
                menu.add_option("No", pre_menu);
                if(!menu.run())
                    payment_company= "";
                else
                {
                    itinerary->pay(payment_company, payment_info);
                    clear_cmd_();
                    std::cout<<itinerary->print();
                    OptionsMenu finish_m{"\n"};
                    finish_m.add_option("Done");
                    finish_m.run(false);
                    continue;
                }
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
                    if(payments[i].is_empty()) 
                    {
                        // the user didn't put the payment info for the company
                        // Ask the user about the payment info
                        payment_info= ask_payment_info();
                        if(payment_info.is_empty())
                                is_back=true;// begin of itinerary items loop (because the user cancel in payment info asking       
                    }
                    else
                        payment_info= payments[i];
                        
                    break;
                }
            }
            if(is_back)
                continue;
            
            itinerary->pay(payment_company, payment_info);
            clear_cmd_();
            std::cout<<itinerary->print();
            OptionsMenu finish_m{"\n"};
            finish_m.add_option("Done");
            finish_m.run(false);
        }
        else if(menu.get_choosed_option()=="Finish (without paying)" || menu.get_choosed_option()=="Finish")
            {break;}
    }// End itineary items loop
}

///@brief Contains all customer menus
///@return True will execute again else will back to main menu 
bool customer_view(Customer& customer)
{
    clear_cmd_();
    std::cout<<"Hello "<<customer.get_name()<<" |*| Customer View\n";
    OptionsMenu menu;
    menu.add_option("Create new itinerary");
    menu.add_option("List my itineraries");
    menu.add_option("Remove itinerary");
    menu.add_option("Modify itinerary");
    menu.add_option("Log out", pre_menu);

    if(!menu.run(false))
        return false; //Back to main menu (Log out)
    
    if(menu.get_choosed_option()=="Create new itinerary")
    {

        auto itinerary{customer.new_itinerary()};

        modify_itinerary(itinerary, customer.get_payments());

        //If itinerary doesn't have any items
        if(itinerary->get_number_of_items()==0)
            customer.remove_itinerary(itinerary);
    }
    else if(menu.get_choosed_option()=="List my itineraries")
    {
        clear_cmd_();
        if(customer.get_itineraries().size()<=0)
            std::cout<<"You don't have any itineraries yet.";
        else
            customer.print_itineraries();
        
        OptionsMenu finish_m{"\n"};
        finish_m.add_option("Done");
        finish_m.run(false);
    }
    else if(menu.get_choosed_option()=="Remove itinerary")
    {
        clear_cmd_();
        if(customer.get_itineraries().size()<=0)
        {
            std::cout<<"You don't have any itineraries yet.";
            OptionsMenu finish_m{"\n"};
            finish_m.add_option("Done");
            finish_m.run(false);
        }
        else
        {
            auto choosed_itinerary_idx{choose_itinerary(customer.get_const_itineraries())};

            if(choosed_itinerary_idx==-1) //(Cancel)
                return true;//execute this function from beggining.

            customer.remove_itinerary(choosed_itinerary_idx);    
        }
    }
    else if(menu.get_choosed_option()=="Modify itinerary")
    {
        clear_cmd_();
        if(customer.get_itineraries().size()<=0)
        {
            std::cout<<"You don't have any itineraries yet.";
            OptionsMenu finish_m{"\n"};
            finish_m.add_option("Done");
            finish_m.run(false);
        }
        else
        {
            auto choosed_itinerary_idx{choose_itinerary(customer.get_const_itineraries())};

            if(choosed_itinerary_idx==-1) //(Cancel)
                return true;//execute this function from beggining.

            const auto& itinerary{customer.get_itinerary(choosed_itinerary_idx)};
            modify_itinerary(itinerary, customer.get_payments());

            //If itinerary doesn't have any items
            if(itinerary->get_number_of_items()==0)
                customer.remove_itinerary(itinerary);
        }
    }
    return true; //execute this function from beggining.
}

///@brief Contains all admin menus
///@return True will execute again else will back to main menu 
bool admin_view(Admin admin)
{
    clear_cmd_();
    std::cout<<"Hello "<<admin.get_name()<<" |*| Admin View\n";
    std::cout<<"Admin view will be available soon!\n";
    OptionsMenu menu{""};

    menu.add_option("Log out");
    menu.run(false);
    return false;
}
