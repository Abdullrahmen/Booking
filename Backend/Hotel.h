#ifndef Hotel_H_
#define Hotel_H_
#include "online_APIs\HotelOnlineAPI.h"
//General Room
class Room
{
private:
    std::string hotel;
    std::string room_type;
    std::string date_from;
    std::string date_to;
    double cost_per_night;
public:
    Room(const std::string& hotel="", const std::string& room_type="", const std::string& date_from="",
        const std::string& date_to="", const double& cost=0.0);
    //Castings
    Room(const online_hotel_api::HiltonRoom& room);
    Room(const online_hotel_api::MarriottFoundRoom& room);

    online_hotel_api::HiltonRoom to_HiltonRoom() const;
    online_hotel_api::MarriottFoundRoom to_MarriottFoundRoom() const;

    //Getters
    const std::string& get_hotel() const;
    const std::string& get_room_type() const;
    const std::string& get_date_from() const;
    const std::string& get_date_to() const;
    const double& get_cost_per_night() const;
    ~Room();
};

namespace hotel_
{
    //Hotels interface
    class IHotel
    {
    public:
        virtual std::vector<Room> find_rooms(const std::string& country,
                                            const std::string& city,
                                            const std::string& date_from,
                                            const std::string& date_to,
                                            const int& adults,
                                            const int& children)= 0;
        /// @return company name, money, service_info -> same as Payment class order
        virtual std::vector<std::string> get_pay_info(const Room& room, int number_of_nights)= 0;
        virtual bool reserve(const Room& room)= 0;
        virtual bool cancel_reserve(const Room& room)= 0;
    };

    //convert from HiltonHotelOnlineAPI to general hotel interface(IHotel)
    class HiltonHotel: public IHotel
    {
    public:
        //Find rooms from HiltonHotel online API
        std::vector<Room> find_rooms(const std::string& country,
                                            const std::string& city,
                                            const std::string& date_from,
                                            const std::string& date_to,
                                            const int& adults,
                                            const int& children) final;
        /// @return company name, money, service_info -> same as Payment class order
        std::vector<std::string> get_pay_info(const Room& room, int number_of_nights) final;
        bool reserve(const Room& room) final;
        bool cancel_reserve(const Room& room) final;
    };

    //convert from MarriottHotelOnlineAPI to general hotel interface(IHotel)
    class MarriottHotel: public IHotel
    {
    public:
        std::vector<Room> find_rooms(const std::string& country,
                                            const std::string& city,
                                            const std::string& date_from,
                                            const std::string& date_to,
                                            const int& adults,
                                            const int& children) final;
        /// @return company name, money, service info(same as Payment interface - payment info)
        std::vector<std::string> get_pay_info(const Room& room, int number_of_nights) final;
        bool reserve(const Room& room) final;
        bool cancel_reserve(const Room& room) final;
    };
    
}

//Abstract factory to get hotels
class HotelFactory
{
private:
    //Supported hotels
    static std::vector<std::string> hotels;
public:
    static hotel_::IHotel* create_hotel_helper(const std::string& hotel);
    //Supported hotels
    static const std::vector<std::string>& get_hotels();
};
#endif //Hotel_H_
