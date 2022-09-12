#include "Flight.h"
int main()
{    
    auto flight_pointer{FlightFactory::create_airlines_helper("Turkish")};
    for (auto &flight : flight_pointer->get_available_flights())
    {
        std::cout<<flight.airline<<"  "<<flight.cost<<"   ";
    }
    
    delete flight_pointer;
    flight_pointer = nullptr;
    return 0;
}