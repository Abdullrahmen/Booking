#include "Flight.h"
int main()
{    
    auto flight_pointer{FlightFactory::create_airlines_helper("Canada")};
    delete flight_pointer;
    flight_pointer = nullptr;
    return 0;
}