#include "Flight.h"
using namespace online_airlines_api;
//////////////////
//Flight Class
//////////////////
Flight::Flight(const std::string& airlines, const double& cost,const std::string& datetime_from,
            const std::string &datetime_to, const std::string& from, const std::string& to):
            airlines(airlines),cost(cost),datetime_from(datetime_from),
            datetime_to(datetime_to),from(from),to(to){}

Flight::Flight(const AirCanadaFlight &flight):
    airlines("Canada"), cost(flight.get_price()), datetime_from(flight.get_date_time_from()),
    datetime_to(flight.get_date_time_to()),from(flight.get_from()),to(flight.get_to()){}

Flight::Flight(const TurkishFlight &flight):
    airlines("Turkish"), cost(flight.get_cost()), datetime_from(flight.get_datetime_from()),
    datetime_to(flight.get_datetime_to()),from(flight.get_from()),to(flight.get_to()){}

online_airlines_api::AirCanadaFlight Flight::to_AirCanadaFlight() const
{return AirCanadaFlight{cost, datetime_from, datetime_to, from, to};}

online_airlines_api::TurkishFlight Flight::to_TurkishFlight() const
{return TurkishFlight{cost, datetime_from, datetime_to, from, to};}

const double& Flight::get_cost()const {return cost;}
const std::string& Flight::get_airlines()const {return airlines;}
const std::string& Flight::get_datetime_from()const {return datetime_from;}
const std::string& Flight::get_datetime_to()const {return datetime_to;}
const std::string& Flight::get_from()const {return from;}
const std::string& Flight::get_to()const {return to;}
Flight::~Flight(){}


//////////////////
//AirCanada Class
//////////////////

flight_::AirCanada::AirCanada(std::string from, std::string to, std::string datetime_from,
            std::string datetime_to, int infants,
            int children, int adults):from(from),to(to),datetime_from(datetime_from),
                                        datetime_to(datetime_to),infants(infants),
                                        children(children),adults(adults){}
void flight_::AirCanada::set_from_to_info(std::string datetime_from, std::string datetime_to,
                                        std::string from, std::string to) 
{
    this->datetime_from= datetime_from;
    this->datetime_to= datetime_to;
    this->from= from;
    this->to= to;
}
void flight_::AirCanada::set_passengers_info(int infants, int children, int adults)
{
    this->adults= adults;
    this->children= children;
    this->infants= infants;
}
std::vector<Flight> flight_::AirCanada::get_available_flights() const 
{
    try
    {
        //invalid arguments
        //if(this->adults<=0)
            //throw std::invalid_argument("Adults in a flight can't be <=0");
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
bool flight_::AirCanada::reserve(const Flight& flight)
{
    //reserve from AirCanadaOnlineAPI
    return AirCanadaOnlineAPI::ReserveFlight(flight.to_AirCanadaFlight());
}
bool flight_::AirCanada::cancel_reserve(const Flight& flight)
{
    //cancel reserve from AirCanadaOnlineAPI
    return AirCanadaOnlineAPI::CancelReserveFlight(flight.to_AirCanadaFlight());
}
std::vector<std::string> flight_::AirCanada::get_pay_info(const Flight& flight) 
{
    std::vector<std::string> pay_info {"Canada"};

    for (auto &i : AirCanadaOnlineAPI::GetPayInfo(flight.to_AirCanadaFlight()))
        pay_info.push_back(i);
    
    return pay_info;
}
flight_::AirCanada::~AirCanada(){}



//////////////////
//AirTurkish Class
//////////////////

flight_::AirTurkish::AirTurkish(std::string from="", std::string to="", std::string datetime_from="",
            std::string datetime_to="", int infants=0,
            int children=0, int adults=0):from(from),to(to),datetime_from(datetime_from),
                                        datetime_to(datetime_to),infants(infants),
                                        children(children),adults(adults){}
void flight_::AirTurkish::set_from_to_info(std::string datetime_from, std::string datetime_to,
                                        std::string from, std::string to)
{
    this->datetime_from= datetime_from;
    this->datetime_to= datetime_to;
    this->from= from;
    this->to= to;
}
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
    return TurkishAirlinesOnlineAPI::ReserveFlight(TurkishCustomerInfo{}, flight.to_TurkishFlight());
}
bool flight_::AirTurkish::cancel_reserve(const Flight& flight)
{
    //cancel reserve from AirCanadaOnlineAPI
    return TurkishAirlinesOnlineAPI::CancelReserveFlight(TurkishCustomerInfo{}, flight.to_TurkishFlight());
}
std::vector<std::string> flight_::AirTurkish::get_pay_info(const Flight& flight) 
{
    std::vector<std::string> pay_info {"Turkish"};

    for (auto &i : TurkishAirlinesOnlineAPI::GetPaymentInfo(TurkishCustomerInfo{},
                                                    flight.to_TurkishFlight()))
        pay_info.push_back(i);
    
    return pay_info;
}
flight_::AirTurkish::~AirTurkish(){}


//////////////////
//FlightFactory Class
//////////////////

std::vector<std::string> FlightFactory::airlines{"Canada","Turkish"};
flight_::IFlight* FlightFactory::create_airlines_helper(const std::string& airlines)
{
    try
    {
        if (airlines=="Canada")
            return new flight_::AirCanada{};
        else if (airlines=="Turkish")
            return new flight_::AirTurkish{};
        else
        {
            std::string error_msg{"FlightFactory class doesn't support \""};
            error_msg+= airlines;
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
const std::vector<std::string>& FlightFactory::get_airlines()
{
    return airlines;
}