#ifndef Itinerary_H_
#define Itinerary_H_
#include "ItineraryItem.h"
#include "Payment.h"
/// @brief All the items created by the factory methods here will be deleted in the destructor (don't delete them manually) 
/// it contains the factory methods to create itinerary items
class Itinerary
{
private:
    /// @brief The items of the Itinerary
    std::vector<ItineraryItem*> items;

    /// @brief describe if every item in the itinerary succesfully paid. 
    /// size: number of items in the itinerary.
    /// (need to pay the itinerary to use it)
    std::vector<bool> items_paid;

    /// @brief is the itinerary paid (call pay method)
    bool is_paid;

    /// @brief payment company (eg.PayPal)
    std::string company_;
    
    /// @brief user's payment info
    PaymentInfo user_payment_;
public:
    Itinerary();

    /// @return if every item is succesfully paid
    std::vector<bool> get_items_paid() const;

    /// @brief Calculate the total cost of the itinerary
    double get_total_cost() const;

    /// @brief Use PaymentFactory to pay every item in the itinerary.
    /// (Reserve every item then pay it)
    /// You can check if every item is succesfully paid from get_items_paid method. 
    /// @param company payment company (eg.PayPal)
    /// @param user_payment user's payment info
    void pay(const std::string& company, const PaymentInfo& user_payment);

    /// @brief cancel reservations and (in the future) return money :)
    void cancel_pay();

    /// @brief Print the details of every item in the itenerary.
    void print() const;

    /* Factory mehtods to create items */
    /// (all the items will be deleted in the destructor)

    /// @brief Factory method to create hotel item     
    void add_hotel(const Room& room, int number_of_nights, const std::string& printing_info="");

    /// @brief Factory method to create flight item. 
    void add_flight(const Flight& flight, const std::string& printing_info="");


    //delete items vector
    ~Itinerary();
};

#endif //Itinerary_H_