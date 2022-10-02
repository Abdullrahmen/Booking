#include "User.h"

/*temp customer data*/
std::vector<LoginInfo> Data::customers_ {{"Reem",""},{"Mohammed",""}};
std::vector<std::vector<Itinerary>> Data::itineraries_{{},{}};
std::vector<std::vector<PaymentInfo>> Data::payments_{{{PaymentInfo{},PaymentInfo{}}},
                                                        {{PaymentInfo{},PaymentInfo{}}}};

/*temp admin data*/
std::vector<LoginInfo> Data::admins_{{"Abdo",""}};

//////////////////
//LoginInfo Class
//////////////////

LoginInfo::LoginInfo(std::string name, std::string password):
    name(name), password(password){}
LoginInfo::~LoginInfo(){}

//////////////////
//Data Class
//////////////////

void Data::add_customer(const LoginInfo& customer, const std::vector<PaymentInfo>& payments)
{
    customers_.push_back(customer);
    payments_.push_back(payments);
    itineraries_.push_back({});
}

void Data::add_admin(const LoginInfo& admin)
{
    admins_.push_back(admin);
}

//////////////////
//User Class
//////////////////

bool User::verify_login(const LoginInfo& info, std::string user_type)
{
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
                return true;
            }
            else
                return false;
        }
    }
    return false;
}

const std::vector<std::string>& User::get_user_data() const
{
    
}
std::vector<Itinerary>& User::get_itineraries()
{

}
const std::vector<PaymentInfo>& User::get_payments() const
{
    
}