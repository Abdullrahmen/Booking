#include "Flight.h"
#include "Hotel.h"
int main()
{    
    auto hotel_pointer{HotelFactory::create_hotel_helper("Hilton")};
    auto flight_pointer{FlightFactory::create_airlines_helper("Turkish")};
    flight_pointer->set_passengers_info(0,0,0);
    flight_pointer->set_from_to_info("10/5/2020","11/6/2020","Egypt","Eraq");

    for (auto &flight : flight_pointer->get_available_flights())
    {
        std::cout<<flight.get_airlines()<<"  "<<flight.get_cost()<<"  "<<flight.get_datetime_from()<<"  "<<flight.get_datetime_to()<<"  "<<flight.get_from()<<"  "<<flight.get_to()<<"\n";
    }
    
    for (auto &room : hotel_pointer->find_rooms("","","10/5/2022","15/5/2022",3,2))
    {
        std::cout<<hotel_pointer->get_pay_info(room, 5)[0]<<"  ";
        std::cout<<room.get_hotel()<<"  "<<room.get_room_type()<<"  "<<room.get_date_from()<<"  "<<room.get_date_to()<<"  "<<room.get_cost_per_night()<<"\n";
    }

    delete flight_pointer;
    delete hotel_pointer;
    flight_pointer = nullptr;
    hotel_pointer = nullptr;
    return 0;
}