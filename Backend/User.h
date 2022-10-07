#ifndef User_H_
#define User_H_
#include "Itinerary.h"
/************
Containing customer and admin users.
Will focus on customer part in this project.
*************/

class LoginInfo
{
public:
    LoginInfo(std::string name="", std::string password="");
    std::string name;
    std::string password;
    ~LoginInfo();
};

//Used by User class to get the data
// (for simplicity I won't make the data branch (maybe in a future update)).
class Data
{
private:

    /*temp customer data*/
    /// @brief Login Customer Data(name, password).
    static std::vector<LoginInfo> customers_;

    //for every customer there is a vector of itineraries (same index as customers vector).
    //in general, itineraries and payments must converted to string or json type to store them in the tables
    //but for simplicity I won't do that now (maybe a future update).
    static std::vector<std::vector<Itinerary>> itineraries_;
    /// @brief (PayPal, Stripe) (same index as customers vector).
    static std::vector<std::vector<PaymentInfo>> payments_;


    /*temp admin data*/
    /// @brief Login Admin Data(name, password).
    static std::vector<LoginInfo> admins_;
public:
    static bool add_customer(const LoginInfo& customer, const std::vector<PaymentInfo>& payments);
    static bool add_admin(const LoginInfo& admin);
    friend class User;
};

class User
{
private:
    /// I need to seprate the users data type here
    /// Because I won't convert itineraries to json or string for now (see line 18)
    
    /// @brief Login User Data(name, password).
    LoginInfo user_data;
     
    /// @brief Customer special data. (this is bad design because there are data for specific child)
    /// (if itineraries and payments converted to string or json I won't need a specific user type data here (maybe in the future updates))
    std::vector<Itinerary> itineraries;
    /// @brief (PayPal, Stripe)
    std::vector<PaymentInfo> payments;

    bool is_login_;

protected:
    /// @brief If succesfully logined (for customers) you can access the data by get_name,
    /// get_itineraries, get_payments.
    /// @param info
    /// @param user_type Admin or Customer
    /// @return True if succesfully login.
    bool verify_login(const LoginInfo& info, const std::string& user_type);

    std::vector<Itinerary>& get_itineraries(); //change able (without const)
    const std::vector<Itinerary>& get_const_itineraries() const;
    const std::vector<PaymentInfo>& get_payments() const;

    bool is_login() const;

public:
    User();
    const std::string& get_name() const;
    ~User();
};

class Admin: public User
{
public:
    bool login(const LoginInfo& admin);
    
    /// @brief Register a new Admin
    /// @param admin {name, password}
    static bool register_(const LoginInfo& admin);
};

class Customer: public User
{
public:
    bool login(const LoginInfo& customer);
    
    /// @brief Register a new customer
    /// @param customer {id, password, name}
    /// @param payments {PayPal, Stripe}
    static bool register_(const LoginInfo& customer, const std::vector<PaymentInfo>& payments);
    
    /* Access after login */

    void add_itinerary(const Itinerary& itinerary);
    //Warning: change able with reference.
    Itinerary& get_itinerary(int idx); //change able (without const)
    void remove_itinerary(int idx);

    void print_itineraries() const;
};

#endif // User_H_