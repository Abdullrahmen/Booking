
#ifndef FLIIGHTONLINEAPI_H_
#define FLIIGHTONLINEAPI_H_

#include <iostream>
#include <vector>
//Online airlines APIs (like) 
namespace online_airlines_api
{
    //AirCanada airlines online API
    class AirCanadaFlight
    {
    private:
        double price;
        std::string date_time_from;
        std::string date_time_to;
        std::string from;
        std::string to;
    public:
        AirCanadaFlight(double price, std::string date_time_from, std::string date_time_to,
                        std::string from, std::string to);
        const double& get_price() const;
        const std::string& get_date_time_from() const;
        const std::string& get_date_time_to() const;
        const std::string& get_from() const;
        const std::string& get_to() const;
        ~AirCanadaFlight();
    };

    class AirCanadaOnlineAPI
    {
    public:

        static std::vector<AirCanadaFlight> GetFLights(std::string from, std::string to,
                                                std::string from_date, std::string to_date,
                                                 int adults, int children);
        static bool ReserveFlight(const AirCanadaFlight& flight);
        static bool CancelReserveFlight(const AirCanadaFlight& flight);
        static std::vector<std::string> GetPayInfo(const AirCanadaFlight& flight);
    };

    //Turkish airlines online API
    class TurkishFlight
    {
    private:
        double cost;
        std::string datetime_from;
        std::string datetime_to;
        std::string from;
        std::string to;
    public:
        TurkishFlight(double cost, std::string datetime_from, std::string datetime_to,
                        std::string from, std::string to);
        const double& get_cost() const;
        const std::string& get_datetime_from() const;
        const std::string& get_datetime_to() const;
        const std::string& get_from() const;
        const std::string& get_to() const;
        ~TurkishFlight();
    };
    class TurkishCustomerInfo{
    public:
        TurkishCustomerInfo(){};
    };
    class TurkishAirlinesOnlineAPI
    {
    private:
        std::string from;
        std::string to;
        std::string datetime_from;
        std::string datetime_to;
        int infants;
        int children;
        int adults;
    public:
        TurkishAirlinesOnlineAPI();
        void SetFromToInfo(std::string datetime_from, std::string datetime_to, std::string from, std::string to);
        void SetPassengersInfo(int infants, int children, int adults);

        std::vector<TurkishFlight> GetAvailableFlights() const;
        static bool ReserveFlight(const TurkishCustomerInfo& info, const TurkishFlight& flight);
        static bool CancelReserveFlight(const TurkishCustomerInfo& info, const TurkishFlight& flight);
        static std::vector<std::string> GetPaymentInfo(const TurkishCustomerInfo& info, const TurkishFlight& flight);
        ~TurkishAirlinesOnlineAPI();
    };
}
#endif