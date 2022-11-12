/*
Including items classes
*/

#ifndef ItineraryItem_H_
#define ItineraryItem_H_

#include "Flight.h"
#include "Hotel.h"

//info for Itinerary item(item_type, item_company, printing_info)
class ItineraryItemInfo
{
private:
    //type like (Hotel, Flight, ...)
    std::string item_type;
    //comapany like (Canada(Flight), Hilton(Hotel), ...)
    std::string item_company;
    //printing string
    std::string printing_info;
public:
    /// @param item_type type like (Hotel, Flight, ...)
    /// @param item_company comapany like (Canada(Flight), Hilton(Hotel), ...)
    /// @param printing_info printing string
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
    static std::vector<std::string> item_types;
protected:
    void set_info(ItineraryItemInfo info);
public:
    ItineraryItem();
    ItineraryItem(const ItineraryItem&)= delete;
    ItineraryItem& operator=(const ItineraryItem&) = delete;

    //General info for Itinerary item(item_type, item_company, printing_info)
    const ItineraryItemInfo& get_info() const;

    //Supported item types
    static const std::vector<std::string>& get_item_types();

    /*pure virtual methods*/

    //company name, money, service_info(details of the product).
    virtual std::vector<std::string> get_pay_info()=0;
    //Reserve the item from the company API.
    virtual bool reserve()=0;
    //Cancel the reservation from the company API. 
    virtual bool cancel_reserve()=0;
    /// @brief Clone the item 
    /// @return Cloned item (heap allocation)
    virtual ItineraryItem* clone()=0;


    //Don't forget virtual (to call childrens' destructors when the interface deleted)
    virtual ~ItineraryItem();
};

namespace items_
{
    //Use HotelFactory to create Hotel interface
    class HotelItem: public ItineraryItem
    {
    private:
        //Hotel interface
        hotel_::IHotel* hotel;
        //number of nights
        int number_of_nights;
        //General Room 
        Room room;
    public:
        //Use HotelFactory to create Hotel interface
        HotelItem(const Room& room, int number_of_nights, const std::string& printing_info="");
        
        //company name, money, service_info(details of the product)
        std::vector<std::string> get_pay_info() final;
        
        bool reserve() final;
        bool cancel_reserve() final;
        /// @brief Clone the item 
        /// @return Cloned item (heap allocation)
        ItineraryItem* clone() final;

        //delete hotel
        ~HotelItem();
    };

    //Use FlightFactory to create Flight interface
    class FlightItem: public ItineraryItem
    {
    private:
        //Flight interface
        flight_::IFlight* airlines;
        //General Flight 
        Flight flight;
    public:
        //Use FlightFactory to create Flight interface
        FlightItem(const Flight& flight, const std::string& printing_info="");
        
        //company name, money, service_info(details of the product)
        std::vector<std::string> get_pay_info() final;

        bool reserve() final;
        bool cancel_reserve() final;
        ItineraryItem* clone() final;

        //delete flight
        ~FlightItem();
    };   
}
#endif //ItineraryItem_H_