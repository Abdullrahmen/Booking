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
    //to HiltonRoom class
    online_hotel_api::HiltonRoom to_HiltonRoom() const;
    //to MarriottFoundRoom class
    online_hotel_api::MarriottFoundRoom to_MarriottFoundRoom() const;
    //Getters
    const std::string& get_hotel();
    const std::string& get_room_type();
    const std::string& get_date_from();
    const std::string& get_date_to();
    const double& get_cost_per_night();
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
    static std::string hotels[2];
public:
    static hotel_::IHotel* create_hotel_helper(const std::string& hotel);
    //Supported hotels
    static const std::string* get_hotels();
};
