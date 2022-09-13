#include "online_APIs\HotelOnlineAPI.h"
//General Room
class Room
{
private:
    /* data */
public:
    Room(/* args */);
    ~Room();
};

namespace hotel_
{
    //Hotels interface
    class IHotel
    {
    public:
    };

    //convert from HiltonHotelOnlineAPI to general hotel interface(IHotel)
    class HiltonHotel
    {
    public:
    };

    //convert from MarriottHotelOnlineAPI to general hotel interface(IHotel)
    class MarriottHotel
    {
    public:
    };
    
}

//Abstract factory to get hotels companies
class HotelFactory
{
private:
    static std::string hotels[2];
public:
    static hotel_::IHotel* get_hotel_helper(std::string hotel);
    static std::string* get_hotels();
};
