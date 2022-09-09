#include "Flight.h"


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
                                        std::string from, std::string to) {
    
};

//Set the passengers count
void flight_::AirCanada::set_passengers_info(int infants, int children, int adults){

};

//After setting all the search info you can get the available flights
std::vector<Flight> flight_::AirCanada::get_available_flights() const {

};

//Reserve a flight and return true if succesfully reserved
bool flight_::AirCanada::reserve(const Flight& flight){

}
//Cancel a reservation and return true if succesfully reserved (if the flight didn't reserve will return true)
bool flight_::AirCanada::cancel_reserve(const Flight& flight){

}
//Get the payment info for a flight (to reserve and pay it)
std::vector<std::string> flight_::AirCanada::get_pay_info(const Flight& flight) {

};
flight_::AirCanada::~AirCanada(){}

//////////////////
//AirCanada Class
//////////////////
//Initilize all the members with the default values
flight_::AirTurkish::AirTurkish(std::string from="", std::string to="", std::string datetime_from="",
            std::string datetime_to="", int infants=0,
            int children=0, int adults=0):from(from),to(to),datetime_from(datetime_from),
                                        datetime_to(datetime_to),infants(infants),
                                        children(children),adults(adults){}
bool flight_::AirTurkish::reserve(const Flight& flight){}
bool flight_::AirTurkish::cancel_reserve(const Flight& flight){}
void flight_::AirTurkish::set_from_to_info(std::string datetime_from, std::string datetime_to, std::string from, std::string to) {};
void flight_::AirTurkish::set_passengers_info(int infants, int children, int adults){};
std::vector<Flight> flight_::AirTurkish::get_available_flights() const {};
std::vector<std::string> flight_::AirTurkish::get_pay_info(const Flight& flight) {};
flight_::AirTurkish::~AirTurkish(){}

std::string FlightFactory::airlines[2] = {"",""};