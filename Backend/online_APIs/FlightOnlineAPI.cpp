#include "FlightOnlineAPI.h"
using namespace online_airlines_api;
/*
================
Canada Airlines
================
*/
//////////////////
//AirCanadaOnlineAPI Class
//////////////////

std::vector<AirCanadaFlight> AirCanadaOnlineAPI::GetFLights(std::string from, std::string to,
                                                std::string from_date, std::string to_date,
                                                int adults, int children)
{
    std::vector<AirCanadaFlight> flights{};
    //temp data
    flights.push_back(AirCanadaFlight{250.0, "2/2/2023 3:45", "3/2/2023 4:30", from, to});
    flights.push_back(AirCanadaFlight{350.0, "5/2/2023 3:45", "6/2/2023 6:30", from, to});
    flights.push_back(AirCanadaFlight{550.0, "1/2/2023 3:45", "2/2/2023 2:30", from, to});
    flights.push_back(AirCanadaFlight{150.0, "20/1/2023 3:45", "22/1/2023 1:30", from, to});

    return flights;
}

bool AirCanadaOnlineAPI::ReserveFlight(const online_airlines_api::AirCanadaFlight& flight)
{return true;}

bool AirCanadaOnlineAPI::CancelReserveFlight(const online_airlines_api::AirCanadaFlight& flight)
{return true;}

std::vector<std::string> AirCanadaOnlineAPI::GetPayInfo(const online_airlines_api::AirCanadaFlight& flight)
{return std::vector<std::string> {std::to_string(flight.get_price()),"more info"};}

//////////////////
//AirCanadaFlight Class
//////////////////

AirCanadaFlight::AirCanadaFlight(double price, std::string date_time_from, std::string date_time_to,
                                std::string from, std::string to):
    price(price),date_time_from(date_time_from),date_time_to(date_time_to),from(from),to(to){}
//Getters
const double& AirCanadaFlight::get_price()const {return this->price;}
const std::string& AirCanadaFlight::get_date_time_from()const {return this->date_time_from;}
const std::string& AirCanadaFlight::get_date_time_to()const {return this->date_time_to;}
const std::string& AirCanadaFlight::get_from()const {return this->from;}
const std::string& AirCanadaFlight::get_to()const {return this->to;}
AirCanadaFlight::~AirCanadaFlight(){}


/*
================
Turkish Airlines
================
*/
//////////////////
//TurkishFlight Class
//////////////////

TurkishFlight::TurkishFlight(double cost, std::string datetime_from, std::string datetime_to,
                        std::string from, std::string to):
                        cost(cost),datetime_from(datetime_from),datetime_to(datetime_to),from(from),to(to){}
//Getters
const double& TurkishFlight::get_cost()const {return this->cost;}
const std::string& TurkishFlight::get_datetime_from()const {return this->datetime_from;}
const std::string& TurkishFlight::get_datetime_to()const {return this->datetime_to;}
const std::string& TurkishFlight::get_from()const {return this->from;}
const std::string& TurkishFlight::get_to()const {return this->to;}
TurkishFlight::~TurkishFlight(){}

//////////////////
//TurkishAirlinesOnlineAPI Class
//////////////////

TurkishAirlinesOnlineAPI::TurkishAirlinesOnlineAPI():from(""),to(""),datetime_from(""),
                                            datetime_to(""),infants(0),
                                            children(0),adults(0){}
//Set from date/location and to date/location
void TurkishAirlinesOnlineAPI::SetFromToInfo(std::string datetime_from, std::string datetime_to,
                                        std::string from, std::string to)
{
    this->datetime_from= datetime_from;
    this->datetime_to= datetime_to;
    this->from= from;
    this->to= to;
}
//Set passengers information (number of adults and children and infants)
void TurkishAirlinesOnlineAPI::SetPassengersInfo(int infants, int children, int adults)
{
    this->children= children;
    this->adults= adults;
    this->infants= infants;
}

std::vector<TurkishFlight> TurkishAirlinesOnlineAPI::GetAvailableFlights() const
{
    std::vector<TurkishFlight> flights{};
    //temp flights
    flights.push_back(TurkishFlight{600.0, "2/2/2023 3:45", "3/2/2023 4:30", this->from, this->to}); 
    flights.push_back(TurkishFlight{200.0, "5/2/2023 3:45", "6/2/2023 6:30", this->from, this->to}); 
    flights.push_back(TurkishFlight{800.0, "1/2/2023 3:45", "2/2/2023 2:30", this->from, this->to}); 
    flights.push_back(TurkishFlight{300.0, "20/1/2023 3:45", "22/1/2023 1:30", this->from, this->to});

    return flights;
}

bool TurkishAirlinesOnlineAPI::ReserveFlight(const TurkishCustomerInfo& info, const TurkishFlight& flight)
{return true;}

bool TurkishAirlinesOnlineAPI::CancelReserveFlight(const TurkishCustomerInfo& info, const TurkishFlight& flight)
{return true;}

std::vector<std::string> TurkishAirlinesOnlineAPI::GetPaymentInfo(const TurkishCustomerInfo& info, const TurkishFlight& flight)
{return std::vector<std::string> {std::to_string(flight.get_cost()),"more info"};}

TurkishAirlinesOnlineAPI::~TurkishAirlinesOnlineAPI(){}