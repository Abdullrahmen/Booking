#include "Hotel.h"
using namespace hotel_;
using namespace online_hotel_api;
//////////////////
//Room Class
//////////////////

Room::Room(const std::string& hotel, const std::string& room_type, const std::string& date_from,
            const std::string& date_to, const double& cost):
            hotel(hotel),room_type(room_type),date_from(date_from),date_to(date_to),cost_per_night(cost){}

Room::Room(const HiltonRoom& room):
    hotel("Hilton"), room_type(room.get_room_type()), date_from(room.get_date_from()),
    date_to(room.get_date_to()), cost_per_night(room.get_cost_per_night()){}

Room::Room(const MarriottFoundRoom& room):
    hotel("Marriott"), room_type(room.get_room_type()), date_from(room.get_date_from()),
    date_to(room.get_date_to()), cost_per_night(room.get_cost_per_night()){}

HiltonRoom Room::to_HiltonRoom() const
{return HiltonRoom{room_type, date_from, date_to, cost_per_night};}

MarriottFoundRoom Room::to_MarriottFoundRoom() const
{return MarriottFoundRoom{room_type, date_from, date_to, cost_per_night};}

const std::string& Room::get_hotel() const{return hotel;}
const std::string& Room::get_room_type() const{return room_type;}
const std::string& Room::get_date_from() const{return date_from;}
const std::string& Room::get_date_to() const{return date_to;}
const double& Room::get_cost_per_night() const{return cost_per_night;}
Room::~Room(){}


//////////////////
//HiltonHotel Class
//////////////////

std::vector<Room> HiltonHotel::find_rooms(const std::string& country,
                                            const std::string& city,
                                            const std::string& date_from,
                                            const std::string& date_to,
                                            const int& adults,
                                            const int& children)
{
    std::vector<Room> rooms{};
    for (auto &hilton_room : HiltonHotelAPI::SearchRooms(country,city,date_from,date_to,adults,children))
    {
        rooms.push_back(Room(hilton_room));
    }
    return rooms;
}
std::vector<std::string> HiltonHotel::get_pay_info(const Room& room, int number_of_nights)
{
    std::vector<std::string> pay_info {"Hilton"};

    for (auto &i : HiltonHotelAPI::GetPaymentInfo(room.to_HiltonRoom(),number_of_nights))
        pay_info.push_back(i);
    
    return pay_info;
}

bool HiltonHotel::reserve(const Room& room)
{return HiltonHotelAPI::Reserve(room.to_HiltonRoom());}

bool HiltonHotel::cancel_reserve(const Room& room)
{return HiltonHotelAPI::CancelReserve(room.to_HiltonRoom());}


//////////////////
//MarriottHotel Class
//////////////////

std::vector<Room> MarriottHotel::find_rooms(const std::string& country,
                                            const std::string& city,
                                            const std::string& date_from,
                                            const std::string& date_to,
                                            const int& adults,
                                            const int& children)
{
    std::vector<Room> rooms{};
    for (auto &marriott_room : MarriottHotelAPI::FindRooms(country,city,date_from,date_to,adults,children))
    {
        rooms.push_back(Room(marriott_room));
    }
    return rooms;
}
std::vector<std::string> MarriottHotel::get_pay_info(const Room& room, int number_of_nights)
{
    std::vector<std::string> pay_info {"Marriott"};

    for (auto &i : MarriottHotelAPI::GetPayInfo(room.to_MarriottFoundRoom(), number_of_nights))
        pay_info.push_back(i);
    
    return pay_info;
}

bool MarriottHotel::reserve(const Room& room)
{return MarriottHotelAPI::Reserve(room.to_MarriottFoundRoom());}

bool MarriottHotel::cancel_reserve(const Room& room)
{return MarriottHotelAPI::CancelReserve(room.to_MarriottFoundRoom());}


//////////////////
//HotelFactory Class
//////////////////

std::vector<std::string> HotelFactory::hotels{"Hilton","Marriott"};
IHotel* HotelFactory::create_hotel_helper(const std::string& hotel)
{
    try
    {
        if(hotel=="Hilton")
            return new HiltonHotel{};
        else if(hotel=="Marriott")
            return new MarriottHotel{};
        else
            {
                std::string error_msg{"HotelFactory class doesn't support \""};
                error_msg+= hotel;
                error_msg+= "\" hotel\nPlease make sure to choose one of the following supported hotels: \n{";
                for (auto &hotel : hotels)
                {error_msg+= hotel;
                error_msg+= ",  ";}
                error_msg+= "}";
                throw std::invalid_argument(error_msg);
            }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    } 
}
const std::vector<std::string>& HotelFactory::get_hotels()
{
    return hotels;
}