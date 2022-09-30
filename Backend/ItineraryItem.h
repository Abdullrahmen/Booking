/*
Including items classes
*/

#ifndef ItineraryItem_H_
#define ItineraryItem_H_

#include "Flight.h"
#include "Hotel.h"

//General info for Itinerary item(item_type, item_company, printing_info)
class ItineraryItemInfo
{
private:
    //type like (Hotel, Flight, ...)
    std::string item_type;
    //comapany like (Canada(Airlines), Hilton(Hotel), ...)
    std::string item_company;
    //printing string
    std::string printing_info;
public:
    ItineraryItemInfo(const std::string& item_type="", const std::string& item_company="",
                        const std::string& printing_info="");

    //Getters
    const std::string& get_item_type()const;
    const std::string& get_item_company()const;
    const std::string& get_printing_info()const;

    ~ItineraryItemInfo();
};

//An Interface for Itinerary items
class ItineraryItem
{
private:
    ItineraryItemInfo info;
    //Supported item types
    static std::string item_types[2];
protected:
    void set_info(const ItineraryItemInfo& info);
public:
    //General info for Itinerary item(item_type, item_company, printing_info)
    const ItineraryItemInfo& get_info() const;

    //Supported item types
    static const std::string* get_item_types();

    /*pure virtual methods*/

    //company name, money, service_info(details of the product).
    virtual std::vector<std::string> get_pay_info()=0;
    //Reserve the item from the company API.
    virtual bool reserve()=0;
    //Cancel the reservation from the company API. 
    virtual bool cancel_reserve()=0;

    //Don't forget virtual (to call childrens' destructors when the interface deleted)
    virtual ~ItineraryItem();
};

namespace items_
{
    //Use HotelFactory to create Hotel interface
    class HotelItem: public ItineraryItem
    {
    private:
        //hotel interface - Polymorphism (using HotelFactory)
        hotel_::IHotel* hotel;
        //number of nights
        int number_of_nights;
        //General Room 
        Room room;
    public:
        //create the hotel interface from the HotelFactory
        HotelItem(const Room& room, int number_of_nights, const std::string& printing_info="");
        
        std::vector<std::string> get_pay_info() final;
        bool reserve() final;
        bool cancel_reserve() final;

        //delete hotel
        ~HotelItem();
    };

    //Use FlightFactory to create Flight interface
    class FlightItem: public ItineraryItem
    {
    private:
        //Flight interface - Polymorphism (using FlightFactory)
        flight_::IFlight* airlines;
        //General Flight 
        Flight flight;
    public:
        //create the flight interface from the FlightFactory
        FlightItem(const Flight& flight, const std::string& printing_info="");
        
        //company name, money, service_info(details of the product)
        std::vector<std::string> get_pay_info() final;

        bool reserve() final;
        bool cancel_reserve() final;

        //delete flight
        ~FlightItem();
    };   
}
#endif //ItineraryItem_H_