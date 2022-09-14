#include "Hotel.h"
using namespace hotel_;
//////////////////
//Room Class
//////////////////

Room::Room(const std::string& hotel, const std::string& room_type, const std::string& date_from,
            const std::string& date_to, const double& cost):
            hotel(hotel),room_type(room_type),date_from(date_from),date_to(date_to),cost_per_night(cost){}
Room::Room(const online_hotel_api::HiltonRoom& room)
{
    this->hotel= "Hilton";
    this->room_type= room.get_room_type();
    this->date_from= room.get_date_from();
    this->date_to= room.get_date_to();
    this->cost_per_night= room.get_cost_per_night();
}
Room::Room(const online_hotel_api::MarriottFoundRoom& room)
{
    this->hotel= "Mariott";
    this->room_type= room.get_room_type();
    this->date_from= room.get_date_from();
    this->date_to= room.get_date_to();
    this->cost_per_night= room.get_cost_per_night();
}

online_hotel_api::HiltonRoom Room::to_HiltonRoom() const
{return online_hotel_api::HiltonRoom{room_type, date_from, date_to, cost_per_night};}
online_hotel_api::MarriottFoundRoom Room::to_MarriottFoundRoom() const
{return online_hotel_api::MarriottFoundRoom{room_type, date_from, date_to, cost_per_night};}

const std::string& Room::get_hotel(){return hotel;}
const std::string& Room::get_room_type(){return room_type;}
const std::string& Room::get_date_from(){return date_from;}
const std::string& Room::get_date_to(){return date_to;}
const double& Room::get_cost_per_night(){return cost_per_night;}
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
    for (auto &hilton_room : online_hotel_api::HiltonHotelAPI::SearchRooms(country,city,date_from,date_to,adults,children))
    {
        rooms.push_back(Room(hilton_room));
    }
    return rooms;
}
std::vector<std::string> HiltonHotel::get_pay_info(const Room& room, int number_of_nights)
{return online_hotel_api::HiltonHotelAPI::GetPaymentInfo(room.to_HiltonRoom(),number_of_nights);}

bool HiltonHotel::reserve(const Room& room)
{return online_hotel_api::HiltonHotelAPI::Reserve(room.to_HiltonRoom());}

bool HiltonHotel::cancel_reserve(const Room& room)
{return online_hotel_api::HiltonHotelAPI::CancelReserve(room.to_HiltonRoom());}


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
    for (auto &mariott_room : online_hotel_api::MarriottHotelAPI::FindRooms(country,city,date_from,date_to,adults,children))
    {
        rooms.push_back(Room(mariott_room));
    }
    return rooms;
}
std::vector<std::string> MarriottHotel::get_pay_info(const Room& room, int number_of_nights)
{return online_hotel_api::MarriottHotelAPI::GetPayInfo(room.to_MarriottFoundRoom(), number_of_nights);}

bool MarriottHotel::reserve(const Room& room)
{return online_hotel_api::MarriottHotelAPI::Reserve(room.to_MarriottFoundRoom());}

bool MarriottHotel::cancel_reserve(const Room& room)
{return online_hotel_api::MarriottHotelAPI::CancelReserve(room.to_MarriottFoundRoom());}


//////////////////
//HotelFactory Class
//////////////////

std::string HotelFactory::hotels[2]{"Hilton","Marriott"};
IHotel* HotelFactory::create_hotel_helper(const std::string& hotel)
{
    try
    {
        if(hotel=="Hilton")
            return new HiltonHotel;
        else if(hotel=="Marriott")
            return new MarriottHotel;
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