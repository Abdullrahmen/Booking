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

    //for every customer there is a vector of itineraries (same customer index as customers vector).
    //in general, itineraries and payments must converted to string or json type to store them in the tables
    //but for simplicity I won't do that now (maybe in a future update).
    static std::vector<std::vector<Itinerary>> itineraries_;
    /// @brief (PayPal, Stripe) (same customer index as customers vector).
    static std::vector<std::vector<PaymentInfo>> payments_;

    /*temp admin data*/
    /// @brief Login admin data(name, password).
    static std::vector<LoginInfo> admins_;
public:
    /// @brief Supported payment methods (linked to PaymentFactory class).
    /// @return payment methods with same order as add_customer payments vector.
    static const std::vector<std::string>& get_payment_methods();
    /// @brief Sign up a new customer
    /// @param customer Login customer data(name, password)
    /// @param payments Payments methods info(must be with the same order and size as get_payment_methods method)
    /// @return True if successfully added
    static bool add_customer(const LoginInfo& customer, const std::vector<PaymentInfo>& payments);
    /// @brief Sign up a new admin.
    /// @param admin Login admin data(name, password)
    /// @return True if successfully added
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
    //std::vector<Itinerary> itineraries; //Future update

    /// @brief {PayPal, Stripe} with same order and size (unavailable will be empty PaymentInfo)
    std::vector<PaymentInfo> payments;

    bool is_login_;

protected:
    /// @brief If succesfully logined (for customers) you can access the data by get_name,
    /// get_itineraries, get_payments.
    /// @param info
    /// @param user_type Admin or Customer
    /// @return True if succesfully login.
    bool verify_login(const LoginInfo& info, const std::string& user_type);

    bool is_login() const;

public:
    User();

    const std::string& get_name() const;

    /* Access after login */

    //Warning: changeable (with reference).
    std::vector<Itinerary>& get_itineraries();

    const std::vector<Itinerary>& get_const_itineraries() const;

    /// @return {PayPal, Stripe} with same order and size (unavailable will be empty payment info)
    const std::vector<PaymentInfo>& get_payments() const;

    ~User();
};

class Admin: public User
{
public:
    bool login(const LoginInfo& admin);
    
    /// @brief Register a new Admin
    /// @param admin {name, password}
    /// @return True if successfully signed up
    static bool register_(const LoginInfo& admin);
};

class Customer: public User
{
public:
    bool login(const LoginInfo& customer);
    
    /// @brief Register a new customer
    /// @param customer {id, password, name}
    /// @param payments {PayPal, Stripe} with same order and size 
    /// (if size < number of supported payment methods will fill the rest with empty payment info)
    /// @return True if successfully signed up
    static bool register_(const LoginInfo& customer, std::vector<PaymentInfo>& payments);
    
    /* Access after login */

    /// @brief Add a new itinerary to the user.
    /// Please use remove_itinerary if you want to delete the itinerary (don't delete it manually)
    /// @return A pointer to the itinerary
    Itinerary* new_itinerary();

    /// @brief Warning: changeable (with reference).
    /// Please use remove_itinerary if you want to delete the itinerary (don't delete it manually)
    /// @param idx index of the itinerary.
    /// @return A pointer to the itinerary
    Itinerary* get_itinerary(unsigned int idx);
    
    /// @brief Delete itinerary from the user.
    void remove_itinerary(unsigned int idx);
    void remove_itinerary(Itinerary* p_itinerary);

    void print_itineraries() ;
};

#endif // User_H_