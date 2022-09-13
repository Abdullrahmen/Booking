#include "Flight.h"
int main()
{    
    auto flight_pointer{FlightFactory::create_airlines_helper("Turkish")};
    flight_pointer->set_passengers_info(0,0,0);
    flight_pointer->set_from_to_info("10/5/2020","11/6/2020","Egypt","Eraq");
    for (auto &flight : flight_pointer->get_available_flights())
    {
        std::cout<<flight.airline<<"  "<<flight.cost<<"  "<<flight.datetime_from<<"  "<<flight.datetime_to<<"  "<<flight.from<<"  "<<flight.to<<"\n";
    }
    
    delete flight_pointer;
    flight_pointer = nullptr;
    return 0;
}