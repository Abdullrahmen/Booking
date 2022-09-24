#include "HotelOnlineAPI.h"
using namespace online_hotel_api;
/*
================
Hilton Hotel
================
*/
//////////////////
//HiltonRoom Class
//////////////////

HiltonRoom::HiltonRoom(std::string room_type, std::string date_from, std::string date_to, double cost_per_night):
                        room_type(room_type),date_from(date_from),date_to(date_to),cost_per_night(cost_per_night){}
const std::string& HiltonRoom::get_room_type() const{return room_type;}
const std::string& HiltonRoom::get_date_from() const{return date_from;}
const std::string& HiltonRoom::get_date_to() const{return date_to;}
const double& HiltonRoom::get_cost_per_night() const{return cost_per_night;}
HiltonRoom::~HiltonRoom(){}

//////////////////
//HiltonHotelAPI Class
//////////////////
std::vector<HiltonRoom> HiltonHotelAPI::SearchRooms(const std::string& country,
                                            const std::string& city,
                                            const std::string& date_from,
                                            const std::string& date_to,
                                            const int& adults,
                                            const int& children)
{
    std::vector<HiltonRoom> rooms{};
    //temp data
    rooms.push_back(HiltonRoom{"Lexuary", date_from, date_to, 1550.0});
    rooms.push_back(HiltonRoom{"Studio", date_from, date_to, 1000.0});
    rooms.push_back(HiltonRoom{"Junior Suite", date_from, date_to, 550.0});
    rooms.push_back(HiltonRoom{"Presidential Suite", date_from, date_to, 6250.0});
    rooms.push_back(HiltonRoom{"Cabana", date_from, date_to, 4000.0});
    rooms.push_back(HiltonRoom{"Studio", date_from, date_to, 875.0});

    return rooms;
}
std::vector<std::string> HiltonHotelAPI::GetPaymentInfo(const HiltonRoom& room, int number_of_nights)
{return std::vector<std::string> {std::to_string(room.get_cost_per_night()*number_of_nights),"Room Reservation"};}

bool HiltonHotelAPI::Reserve(const HiltonRoom& room)
{return true;}

bool HiltonHotelAPI::CancelReserve(const HiltonRoom& room)
{return true;}

/*
================
Marriott Hotel
================
*/
//////////////////
//MarriottFoundRoom Class
//////////////////

MarriottFoundRoom::MarriottFoundRoom(std::string room_type, std::string date_from, std::string date_to, double cost):
                        room_type(room_type),date_from(date_from),date_to(date_to),cost_per_night(cost){}
const std::string& MarriottFoundRoom::get_room_type() const{return room_type;}
const std::string& MarriottFoundRoom::get_date_from() const{return date_from;}
const std::string& MarriottFoundRoom::get_date_to() const{return date_to;}
const double& MarriottFoundRoom::get_cost_per_night() const{return cost_per_night;}
MarriottFoundRoom::~MarriottFoundRoom(){}

//////////////////
//MarriottHotelAPI Class
//////////////////
std::vector<MarriottFoundRoom> MarriottHotelAPI::FindRooms(const std::string& country,
                                            const std::string& city,
                                            const std::string& date_from,
                                            const std::string& date_to,
                                            const int& adults,
                                            const int& children)
{
    std::vector<MarriottFoundRoom> rooms{};
    //temp data
    rooms.push_back(MarriottFoundRoom{"Lexuary", date_from, date_to, 1550.0});
    rooms.push_back(MarriottFoundRoom{"Studio", date_from, date_to, 1000.0});
    rooms.push_back(MarriottFoundRoom{"Junior Suite", date_from, date_to, 550.0});
    rooms.push_back(MarriottFoundRoom{"Presidential Suite", date_from, date_to, 6250.0});
    rooms.push_back(MarriottFoundRoom{"Cabana", date_from, date_to, 4000.0});
    rooms.push_back(MarriottFoundRoom{"Studio", date_from, date_to, 875.0});


    return rooms;
}
std::vector<std::string> MarriottHotelAPI::GetPayInfo(const MarriottFoundRoom& room, int number_of_nights)
{return std::vector<std::string> {std::to_string(room.get_cost_per_night()*number_of_nights),"Room Reservation"};}

bool MarriottHotelAPI::Reserve(const MarriottFoundRoom& room)
{return true;}

bool MarriottHotelAPI::CancelReserve(const MarriottFoundRoom& room)
{return true;}