#ifndef Itinerary_H_
#define Itinerary_H_
#include "ItineraryItem.h"
#include "Payment.h"
/// @brief All the items created by the factory methods here will be deleted in the destructor (don't delete them manually) 
/// it contains the factory methods to create itinerary items.
class Itinerary
{
private:
    /// @brief The items of the Itinerary
    std::vector<ItineraryItem*> items;

    /// @brief Describe if every item in the itinerary succesfully paid. 
    /// size: number of items in the itinerary.
    std::vector<bool> items_paid;

    /* Changed to be in ItineraryItem info
    /// @brief For deep copy method (if store_copy_info==false then it's empty):
    /// vector 1 size: number of items.
    /// vector 2 size depends on item type.
    std::vector<std::vector<std::string>> copy_info;
    */

    /// @brief If the itinerary paid (pay method called)
    bool is_paid_;

    /// @brief Payment company (eg.PayPal)
    std::string company_;
    
    /// @brief User's payment info
    PaymentInfo user_payment_;

    /// @brief Allow copy constuctor
    bool allow_copy_;

    /// @brief Like copy constructor.
    /// @param itinerary The itinerary which will get deep copy from.
    void get_deep_copy_(const Itinerary& itinerary);
public:
    /// @brief Constructor for Itinerary
    /// @param allow_copy Allow copy constuctor (get_deep_copy method is always available) (Itinerary is a heavy object so it isn't recommended to copy it)
    Itinerary(bool allow_copy= true);

    /// @brief Copy constructor (Need allow_copy)
    Itinerary(const Itinerary& itienrary);
/*
    bool operator == (const Itinerary& itinerary)
    {
        //if(!itinerary.allow_copy_)
            //throw std::invalid_argument("Copy constructor called and allow_copy==false\nPlease use get_deep_copy method or change allow_copy to true.");
    
        //get_deep_copy_(itinerary);

        if(this==&itinerary)
            return true;
        return false;
    }
*/
    /// @brief Like copy constructor (this itinerary must be empty).
    /// @param itinerary The itinerary which will get deep copy from.
    void get_deep_copy(const Itinerary& itinerary);
    void get_deep_copy(const Itinerary* itinerary);

    /// @return Number of items in the itinerary
    int get_number_of_items() const;

    /// @return If the itinerary paid (call pay method)
    bool is_paid() const;

    /// @return If every item is succesfully paid
    const std::vector<bool>& get_items_paid() const;

    /// @brief Calculate the total cost of the itinerary
    double get_total_cost() const;

    /// @brief Use PaymentFactory to pay every item in the itinerary.
    /// (Reserve every item then pay it)
    /// You can check if every item is succesfully paid from get_items_paid method. 
    /// @param company payment company (eg.PayPal)
    /// @param user_payment user's payment info
    void pay(const std::string& company, const PaymentInfo& user_payment);

    /// @brief Cancel reservations and (Future update) return money :)
    void cancel_pay();

    /// @return Printing string shows the details of every item in the itenerary.
    std::string print() const;

    /* Factory mehtods to create items */
    /// (all the items will be deleted in the destructor)

    /// @brief Factory method to create room item
    void add_room(const Room& room, int number_of_nights, const std::string& printing_info="");

    /// @brief Factory method to create flight item. 
    void add_flight(const Flight& flight, const std::string& printing_info="");

    /// @brief Remove item from the itinerary and cancel resevation (if paid)
    /// @param idx index of the item.
    void remove_item(unsigned int idx);

    //Delete items vector
    ~Itinerary();
};

#endif //Itinerary_H_