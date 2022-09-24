/*
Including items classes
*/

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

//An Interface+Factory for Itinerary items
class ItineraryItem
{
private:
    ItineraryItemInfo info;
    //Supported item types
    static std::string item_types[2];
protected:
    void set_info(const ItineraryItemInfo& info);
public:
    const ItineraryItemInfo& get_info() const;

    //Supported item types
    static const std::string* get_item_types();

    //Factory method to create hotel item
    static ItineraryItem* create_hotel(const std::string& hotel, const Room& room,
                                        int number_of_nights, const std::string& printing_info="");

    //Factory method to create flight item
    static ItineraryItem* create_flight(const std::string& airlines, const Flight& flight,
                                        const std::string& printing_info="");

    //pure virtual methods
    virtual std::vector<std::string> get_pay_info()=0;
    virtual bool reserve()=0;
    virtual bool cancel_reserve()=0;
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
        HotelItem(const std::string& hotel, const Room& room, int number_of_nights,
                    const std::string& printing_info="");
        
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
        FlightItem(const std::string& airlines, const Flight& flight,
                    const std::string& printing_info="");
        
        std::vector<std::string> get_pay_info() final;
        bool reserve() final;
        bool cancel_reserve() final;

        //delete flight
        ~FlightItem();
    };
    
}