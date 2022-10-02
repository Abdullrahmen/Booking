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
    static void add_customer(const LoginInfo& customer, const std::vector<PaymentInfo>& payments);
    static void add_admin(const LoginInfo& admin);
    friend class User;
};

class User
{
private:
    /// I need to seprate the users data type here
    /// Because I won't convert itineraries to json or string for now (see line 18)
    
    /// @brief Login User Data(name, password).
    LoginInfo user_data;
     
    /// @brief Customer special data.  
    /// (if itineraries and payments converted to string or json I won't need a specific user type data here (maybe in the future updates))
    std::vector<Itinerary> itineraries;
    /// @brief (PayPal, Stripe)
    std::vector<PaymentInfo> payments;

protected:
    /// @brief If succesfully logined (for customers) you can access the data by get_user_data,
    /// get_itineraries, get_payments.
    /// @param info
    /// @param user_type Admin or Customer
    /// @return True if succesfully login.
    bool verify_login(const LoginInfo& info, std::string user_type);

    const std::vector<std::string>& get_user_data() const;
    std::vector<Itinerary>& get_itineraries(); //change able (without const)
    const std::vector<PaymentInfo>& get_payments() const;
};

class Admin: public User
{
public:
    Admin();
    
    void login(std::string id, std::string password);
    
    /// @brief Register a new Admin
    /// @param admin {name, password}
    void register_(std::vector<std::string> admin);

    ~Admin();
};

class Customer: public User
{
private:
    bool is_login;
public:
    Customer();
    
    void login(std::string id, std::string password);
    
    /// @brief Register a new customer
    /// @param customer {id, password, name}
    /// @param payments {PayPal, Stripe}
    void register_(std::vector<std::string> customer, std::vector<PaymentInfo> payments);
    
    /* Access after login */

    void add_itinerary(const Itinerary& itinerary);
    Itinerary& get_itinerary(int idx); //change able (without const)
    void remove_itinerary(int idx);

    void print_itineraries() const;

    ~Customer();
};

#endif // User_H_