#ifndef HotelOnlineAPI_H_
#define HotelOnlineAPI_H_
#include <iostream>
#include <vector>

namespace online_hotel_api
{
    //HiltonHotelAPI + room
    class HiltonRoom
    {
    private:
        std::string room_type;
        std::string date_from;
        std::string date_to;
        double cost_per_night;
    public:
        HiltonRoom(std::string room_type, std::string date_from, std::string date_to, double cost);
        //Getters
        const std::string& get_room_type() const;
        const std::string& get_date_from() const;
        const std::string& get_date_to() const;
        const double& get_cost_per_night() const;
        ~HiltonRoom();
    };
    class HiltonHotelAPI
    {
    public:
        static std::vector<HiltonRoom> SearchRooms(const std::string& country,
                                            const std::string& city,
                                            const std::string& date_from,
                                            const std::string& date_to,
                                            const int& adults,
                                            const int& children);
        static std::vector<std::string> GetPaymentInfo(const HiltonRoom& room, int number_of_nights);
        static bool Reserve(const HiltonRoom& room);
        static bool CancelReserve(const HiltonRoom& room);
    };

    //MarriottHotelAPI + room
    class MarriottFoundRoom
    {
    private:
        std::string room_type;
        std::string date_from;
        std::string date_to;
        double cost_per_night;
    public:
        MarriottFoundRoom(std::string room_type, std::string date_from, std::string date_to, double cost);
        //Getters
        const std::string& get_room_type() const;
        const std::string& get_date_from() const;
        const std::string& get_date_to() const;
        const double& get_cost_per_night() const;
        ~MarriottFoundRoom();
    };
    class MarriottHotelAPI
    {
    public:
        static std::vector<MarriottFoundRoom> FindRooms(const std::string& country,
                                            const std::string& city,
                                            const std::string& date_from,
                                            const std::string& date_to,
                                            const int& adults,
                                            const int& children);
        static std::vector<std::string> GetPayInfo(const MarriottFoundRoom& room, int number_of_nights);
        static bool Reserve(const MarriottFoundRoom& room);
        static bool CancelReserve(const MarriottFoundRoom& room);
    };
}
#endif //HotelOnlineAPI_H_