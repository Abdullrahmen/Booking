#ifndef FLIGHT_H_
#define FLIGHT_H_

#include "online_APIs\\FlightOnlineAPI.h"

//A flight details
class Flight
{
private:
    std::string airline;
    double cost;
    std::string datetime_from;
    std::string datetime_to;
    std::string from;
    std::string to;
public:
    Flight(const std::string& airline="", const double& cost=0.0,const std::string& datetime_from="",
            const std::string &datetime_to="", const std::string& from="", const std::string& to="");
    Flight(const online_airlines_api::AirCanadaFlight &canada_flight);
    Flight(const online_airlines_api::TurkishFlight &turkish_flight);

    //to AirCanadaFlight class
    online_airlines_api::AirCanadaFlight to_AirCanadaFlight() const;
    //to TurkishFlight class
    online_airlines_api::TurkishFlight to_TurkishFlight() const;

    //Getters
    const double& get_cost() const;
    const std::string& get_datetime_from() const;
    const std::string& get_datetime_to() const;
    const std::string& get_from() const;
    const std::string& get_to() const;
    ~Flight();
};

//Flight classes details (user doesn't need it)
namespace flight_
{
    //Airlines interface
    class IFlight
    {
    public:
        //Constructor
        IFlight(){};
        
        //Set the flight's date and location
        virtual void set_from_to_info(std::string datetime_from, std::string datetime_to, std::string from, std::string to) = 0;
    
        //Set the passengers count
        virtual void set_passengers_info(int infants, int children, int adults) = 0;

        //After setting all the search info you can get the available flights
        virtual std::vector<Flight> get_available_flights() const = 0;
    
        //Reserve a flight and return true if succesfully reserved
        virtual bool reserve(const Flight& flight) = 0;
        
        //Cancel a reservation and return true if succesfully reserved (if the flight didn't reserve will return true)
        virtual bool cancel_reserve(const Flight& flight) = 0;

        //Get the payment info for a flight (to reserve and pay it)
        virtual std::vector<std::string> get_pay_info(const Flight& flight) = 0;
    
        //Destructor
        virtual ~IFlight(){};
    };

    //AirCanada airflights: converts from AirCanada online api to IFlight interface
    class AirCanada: public IFlight
    {
    private:
        //The flight details
        std::string from;
        std::string to;
        std::string datetime_from;
        std::string datetime_to;
        int infants;
        int children;
        int adults;
    public:
        //Default constructor (with default values)
        AirCanada(std::string from="", std::string to="", std::string datetime_from="",
            std::string datetime_to="", int infants=0,
            int children=0, int adults=0);

        //Set the flight's date and location
        void set_from_to_info(std::string datetime_from, std::string datetime_to, std::string from, std::string to) final;
    
        //Set the passengers number
        void set_passengers_info(int infants, int children, int adults) final;

        //After setting all the search info you can get the available flights
        std::vector<Flight> get_available_flights() const final;
    
        //Reserve a flight and return true if succesfully reserved
        bool reserve(const Flight& flight) final;
        
        //Cancel a reservation and return true if succesfully reserved (if the flight didn't reserve will return true)
        bool cancel_reserve(const Flight& flight) final;

        //Get the payment info for a flight (to reserve and pay it)
        std::vector<std::string> get_pay_info(const Flight& flight) final;

        ~AirCanada() final;
    };

    //AirTurkish airflights: converts from AirTurkish online api to IFlight interface
    class AirTurkish: public IFlight
    {
    private:
        //The flight details
        std::string from;
        std::string to;
        std::string datetime_from;
        std::string datetime_to;
        int infants;
        int children;
        int adults;
    public:
        //Default constructor (with default values)
        AirTurkish(std::string from, std::string to, std::string datetime_from,
                std::string datetime_to, int infants,
                int children, int adults);

        //Set the flight's date and location
        void set_from_to_info(std::string datetime_from, std::string datetime_to, std::string from, std::string to) final;
    
        //Set the passengers number
        void set_passengers_info(int infants, int children, int adults) final;

        //After setting all the search info you can get the available flights
        std::vector<Flight> get_available_flights() const final;
    
        //Reserve a flight and return true if succesfully reserved
        bool reserve(const Flight& flight) final;
        
        //Cancel a reservation and return true if succesfully reserved (if the flight didn't reserve will return true)
        bool cancel_reserve(const Flight& flight) final;

        //Get the payment info for a flight (to reserve and pay it)
        std::vector<std::string> get_pay_info(const Flight& flight) final;

        ~AirTurkish();
    };
}

//Airlines abstract factory
class FlightFactory
{
private:
    //Supported airlines
    static std::string airlines[2];
public:
    //Airlines factory method
    static flight_::IFlight* create_airlines_helper(const std::string& airline);
    //Supported airlines
    static const std::string* get_airlines();
};
#endif