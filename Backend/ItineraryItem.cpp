#include "ItineraryItem.h"
using namespace items_;

//////////////////
//ItineraryItemInfo Class
//////////////////

ItineraryItemInfo::ItineraryItemInfo(const std::string& item_type, const std::string& item_company,
                        const std::string& printing_info):
                        item_type(item_type),item_company(item_company),printing_info(printing_info){}

const std::string& ItineraryItemInfo::get_item_type()const{return item_type;}
const std::string& ItineraryItemInfo::get_item_company()const{return item_company;}
const std::string& ItineraryItemInfo::get_printing_info()const{return printing_info;}

ItineraryItemInfo::~ItineraryItemInfo(){}

//////////////////
//ItineraryItem Class
//////////////////

std::string ItineraryItem::item_types[2]{"Hotel","Flight"};

const std::string* ItineraryItem::get_item_types(){return &item_types[0];}
const ItineraryItemInfo& ItineraryItem::get_info() const {return info;}
void ItineraryItem::set_info(const ItineraryItemInfo& info) {this->info=info;}

ItineraryItem::~ItineraryItem(){}

//////////////////
//HotelItem Class
//////////////////

HotelItem::HotelItem(const Room& room, int number_of_nights, const std::string& printing_info):
                                            hotel(HotelFactory::create_hotel_helper(room.get_hotel())),
                                            number_of_nights(number_of_nights),
                                            room(room)
{
    set_info(ItineraryItemInfo{"Hotel", room.get_hotel(), printing_info});
}

bool HotelItem::reserve(){return hotel->reserve(room);}
bool HotelItem::cancel_reserve(){return hotel->cancel_reserve(room);}
std::vector<std::string> HotelItem::get_pay_info(){return hotel->get_pay_info(room,number_of_nights);}

HotelItem::~HotelItem()
{
    delete hotel;
    hotel= nullptr;
}

//////////////////
//FlightItem Class
//////////////////

FlightItem::FlightItem(const Flight& flight, const std::string& printing_info):
                                            airlines(FlightFactory::create_airlines_helper(flight.get_airlines())),
                                            flight(flight)
{
    set_info(ItineraryItemInfo{"Flight", flight.get_airlines(), printing_info});
}

bool FlightItem::reserve(){return airlines->reserve(flight);}
bool FlightItem::cancel_reserve(){return airlines->reserve(flight);}
std::vector<std::string> FlightItem::get_pay_info(){return airlines->get_pay_info(flight);}

FlightItem::~FlightItem()
{
    delete airlines;
    airlines= nullptr;
}