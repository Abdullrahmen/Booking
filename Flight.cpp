#include "Flight.h"
using namespace online_airlines_api;
//////////////////
//Flight Class
//////////////////
Flight::Flight(std::string airline, double cost, std::string datetime_from,
            std::string datetime_to, std::string from, std::string to):
            airline(airline),cost(cost),datetime_from(datetime_from),
            datetime_to(datetime_to),from(from),to(to){}
Flight::Flight(const AirCanadaFlight &canada_flight)
{
    this->airline= "Canada";
    this->cost= canada_flight.get_price();
    this->datetime_from= canada_flight.get_date_time_from();
    this->datetime_to= canada_flight.get_date_time_to();
    this->from= canada_flight.get_from();
    this->to= canada_flight.get_to();
}
Flight::Flight(const TurkishFlight &turkish_flight)
{
    this->airline= "Turkish";
    this->cost= turkish_flight.get_cost();
    this->datetime_from= turkish_flight.get_datetime_from();
    this->datetime_to= turkish_flight.get_datetime_to();
    this->from= turkish_flight.get_from();
    this->to= turkish_flight.get_to();
}
Flight::~Flight(){}


//////////////////
//AirCanada Class
//////////////////
//Initilize all the members with the default values
flight_::AirCanada::AirCanada(std::string from, std::string to, std::string datetime_from,
            std::string datetime_to, int infants,
            int children, int adults):from(from),to(to),datetime_from(datetime_from),
                                        datetime_to(datetime_to),infants(infants),
                                        children(children),adults(adults){}
//Set the flight's date and location
void flight_::AirCanada::set_from_to_info(std::string datetime_from, std::string datetime_to,
                                        std::string from, std::string to) 
{
    this->datetime_from= datetime_from;
    this->datetime_to= datetime_to;
    this->from= from;
    this->to= to;
}
//Set the passengers count
void flight_::AirCanada::set_passengers_info(int infants, int children, int adults)
{
    this->adults= adults;
    this->children= children;
    this->infants= infants;
}
//After setting all the search info you can get the available flights
std::vector<Flight> flight_::AirCanada::get_available_flights() const 
{
    try
    {
        //invalid arguments
        if(this->adults<=0)
            throw std::invalid_argument("Adults in a flight can't be <=0");
        if(this->datetime_from=="")
            throw std::invalid_argument("Please set from date/time before call get_available_flights");
        if(this->datetime_to=="")
            throw std::invalid_argument("Please set to date/time before call get_available_flights");
        if(this->from=="")
            throw std::invalid_argument("Please set from location before call get_available_flights");
        if(this->to=="")
            throw std::invalid_argument("Please set to location before call get_available_flights");
        

        //Get flights from the CanadaAirlines API
        auto canada_flights= AirCanadaOnlineAPI::GetFLights(this->from, this->to, this->datetime_from,
                                                            this->datetime_to, this->adults, this->children);
        //Convert CanadaFlight to Flight
        std::vector<Flight> flights{};
        for (auto &canada_flight : canada_flights)
        {flights.push_back(Flight{canada_flight});}
        return flights;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
}
//Reserve a flight and return true if succesfully reserved
bool flight_::AirCanada::reserve(const Flight& flight)
{
    //reserve from AirCanadaOnlineAPI
    return AirCanadaOnlineAPI::ReserveFlight(AirCanadaFlight{flight.cost,flight.datetime_from,
                                                                flight.datetime_to,flight.from,flight.to});
}
//Cancel a reservation and return true if succesfully reserved (if the flight wasn't reserved will return true)
bool flight_::AirCanada::cancel_reserve(const Flight& flight)
{
    //cancel reserve from AirCanadaOnlineAPI
    return AirCanadaOnlineAPI::CancelReserveFlight(AirCanadaFlight{flight.cost,flight.datetime_from,
                                                                    flight.datetime_to,flight.from,flight.to});
}
//Get the payment info for a flight (to reserve and pay it)
std::vector<std::string> flight_::AirCanada::get_pay_info(const Flight& flight) 
{
    return AirCanadaOnlineAPI::GetPayInfo(AirCanadaFlight{flight.cost,flight.datetime_from,
                                                            flight.datetime_to,flight.from,flight.to});
}
flight_::AirCanada::~AirCanada(){}



//////////////////
//AirTurkish Class
//////////////////
//Initilize all the members with the default values
flight_::AirTurkish::AirTurkish(std::string from="", std::string to="", std::string datetime_from="",
            std::string datetime_to="", int infants=0,
            int children=0, int adults=0):from(from),to(to),datetime_from(datetime_from),
                                        datetime_to(datetime_to),infants(infants),
                                        children(children),adults(adults){}
//Set the flight's date and location
void flight_::AirTurkish::set_from_to_info(std::string datetime_from, std::string datetime_to,
                                        std::string from, std::string to) 
{
    this->datetime_from= datetime_from;
    this->datetime_to= datetime_to;
    this->from= from;
    this->to= to;
}
//Set the passengers count
void flight_::AirTurkish::set_passengers_info(int infants, int children, int adults)
{
    this->adults= adults;
    this->children= children;
    this->infants= infants;
}
std::vector<Flight> flight_::AirTurkish::get_available_flights() const 
{
    TurkishAirlinesOnlineAPI turkish_api{};
    turkish_api.SetFromToInfo(this->datetime_from,this->datetime_to,this->from,this->to);
    turkish_api.SetPassengersInfo(this->infants,this->children,this->adults);

    auto turkish_flights {turkish_api.GetAvailableFlights()};
    std::vector<Flight> flights{};

    for (auto &turkish_flight : turkish_flights)
    {
        flights.push_back(Flight{turkish_flight});
    }
    return flights;
}
bool flight_::AirTurkish::reserve(const Flight& flight)
{
    //reserve from AirCanadaOnlineAPI
    return TurkishAirlinesOnlineAPI::ReserveFlight(TurkishCustomerInfo{}, TurkishFlight{flight.cost,flight.datetime_from,
                                                                flight.datetime_to,flight.from,flight.to});
}
bool flight_::AirTurkish::cancel_reserve(const Flight& flight)
{
    //cancel reserve from AirCanadaOnlineAPI
    return TurkishAirlinesOnlineAPI::CancelReserveFlight(TurkishCustomerInfo{}, TurkishFlight{flight.cost,flight.datetime_from,
                                                                flight.datetime_to,flight.from,flight.to});
}
std::vector<std::string> flight_::AirTurkish::get_pay_info(const Flight& flight) 
{
    return TurkishAirlinesOnlineAPI::GetPaymentInfo(TurkishCustomerInfo{},
                                                    TurkishFlight{flight.cost,flight.datetime_from,
                                                    flight.datetime_to,flight.from,flight.to});    
}
flight_::AirTurkish::~AirTurkish(){}


//////////////////
//FlightFactory Class
//////////////////
std::string FlightFactory::airlines[2] = {"Canada","Turkish"};

//Airlines factory
flight_::IFlight* FlightFactory::create_airlines_helper(const std::string& airline)
{
    try
    {
        if (airline=="Canada")
        {return new flight_::AirCanada;}
        else if (airline=="Turkish")
        {return new flight_::AirTurkish;}
        else
        {
            std::string error_msg{"FlightFactory class doesn't support \""};
            error_msg+= airline;
            error_msg+= "\" airlines\nPlease make sure to choose one of the following supported airlines: \n{";
            for (auto &airline : FlightFactory::airlines)
            {error_msg+= airline;
            error_msg+= ",  ";}
            error_msg+= "}";
            throw std::invalid_argument(error_msg);
        }
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
}
const std::string* FlightFactory::get_airlines()
{
    return &airlines[0];
}