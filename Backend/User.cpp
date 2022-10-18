#include "User.h"

/*temp customer data*/
std::vector<LoginInfo> Data::customers_ {{"Reem","123"},{"Mohammed","123"}};
std::vector<std::vector<Itinerary>> Data::itineraries_{{},{}};
std::vector<std::vector<PaymentInfo>> Data::payments_{{{PaymentInfo{},PaymentInfo{}}},
                                                        {{PaymentInfo{},PaymentInfo{}}}};

/*temp admin data*/
std::vector<LoginInfo> Data::admins_{{"Abdo","123"}};

//////////////////
//LoginInfo Class
//////////////////

LoginInfo::LoginInfo(std::string name, std::string password):
    name(name), password(password){}
LoginInfo::~LoginInfo(){}

//////////////////
//Data Class
//////////////////

const std::vector<std::string>& Data::get_payment_methods()
{
    return PaymentFactory::get_payment_methods();
}

bool Data::add_customer(const LoginInfo& customer, const std::vector<PaymentInfo>& payments)
{
    if(payments.size()!=PaymentFactory::get_payment_methods().size())
        throw std::invalid_argument("payments must be with the same order and size as get_payment_methods method in PaymentFactory class");
    for (auto &i : customers_)
    {
        if(i.name==customer.name)
            return false;
    }
    
    customers_.push_back(customer);
    payments_.push_back(payments);
    itineraries_.push_back({});
    return true;
}

bool Data::add_admin(const LoginInfo& admin)
{
    for (auto &i : admins_)
    {
        if(i.name==admin.name)
            return false;
    }

    admins_.push_back(admin);
    return true;
}

//////////////////
//User Class
//////////////////

User::User():
    user_data(LoginInfo{}),
    itineraries({}),
    payments({}),
    is_login_(false) {}

bool User::verify_login(const LoginInfo& info, const std::string& user_type)
{
    if(is_login_)
        throw std::invalid_argument("Can't login twice. (login called twice in the same object.)");

    std::vector<LoginInfo>& users_logins {Data::customers_};
    if (user_type=="Admin")
        users_logins= Data::admins_;
    else if (user_type=="Customer");
    else 
        throw std::invalid_argument("user_type must be \"Admin\" or \"Customer\".");
    
    for (int i = 0; i < (int)users_logins.size(); i++)
    {
        if(users_logins[i].name == info.name)
        {
            if(users_logins[i].password == info.password)
            {
                user_data= info;
                if(user_type=="Customer")
                {
                    itineraries= Data::itineraries_[i]; //same index
                    payments= Data::payments_[i];
                }
                is_login_= true;
                return true;
            }
            else
                return false;
        }
    }
    return false;
}

const std::string& User::get_name() const
{
    if(!is_login_)
        throw std::invalid_argument("You can't get user's data before login.");
    
    return user_data.name;

}
std::vector<Itinerary>& User::get_itineraries()
{
    if(!is_login_)
        throw std::invalid_argument("You can't get itineraries before login.");

    return itineraries;
}
const std::vector<Itinerary>& User::get_const_itineraries() const
{
    if(!is_login_)
        throw std::invalid_argument("You can't get const itineraries before login.");

    return itineraries;
}


const std::vector<PaymentInfo>& User::get_payments() const
{
    if(!is_login_)
        throw std::invalid_argument("You can't get user's payments data before login.");
    
    return payments;
}

bool User::is_login() const {return is_login_;}

User::~User(){}

//////////////////
//Admin Class
//////////////////

bool Admin::register_(const LoginInfo& admin)
{
    return Data::add_admin(admin);
}

bool Admin::login(const LoginInfo& admin)
{
    return verify_login(admin, "Admin");
}

//////////////////
//Customer Class
//////////////////

bool Customer::register_(const LoginInfo& customer, std::vector<PaymentInfo>& payments)
{
    //difference between the size of payments vector and the size of supported paymect methods.
    auto difference{(int)payments.size() < (int)PaymentFactory::get_payment_methods().size()};

    if(difference<0)
        return false;
    else if(difference>0)
        for (int i = 0; i < difference; i++)
            payments.push_back(PaymentInfo{});

    return Data::add_customer(customer, payments);
}

bool Customer::login(const LoginInfo& customer)
{
    return verify_login(customer, "Customer");
}

void Customer::add_itinerary(const Itinerary& itinerary)
{
    if(!is_login())
        throw std::invalid_argument("You can't add itinerary before login.");

    get_itineraries().push_back(itinerary);
}

Itinerary& Customer::get_itinerary(unsigned int idx)
{
    if(!is_login())
        throw std::invalid_argument("You can't get itinerary before login.");

    if(idx > get_itineraries().size()-1)
        throw std::invalid_argument("Invalid index");
        
    return get_itineraries()[idx];
}

void Customer::remove_itinerary(unsigned int idx)
{
    if(!is_login())
        throw std::invalid_argument("You can't remove itinerary before login.");

    auto &v {get_itineraries()};
    if(idx > v.size()-1)
        throw std::invalid_argument("Invalid index");

    v.erase(v.begin()+idx);
}

void Customer::print_itineraries() const
{
    if(!is_login())
        throw std::invalid_argument("You can't print itineraries before login.");

    for (auto &i : get_const_itineraries())
    {
        i.print();
    }
}