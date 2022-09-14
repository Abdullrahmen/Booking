#include "Flight.h"
#include "Hotel.h"
int main()
{    
    auto hotel_pointer{HotelFactory::create_hotel_helper("Hilton")};
    
    for (auto &room : hotel_pointer->find_rooms("","","10/5/2022","15/5/2022",3,2))
    {
        std::cout<<hotel_pointer->get_pay_info(room, 5)[0]<<"  ";
        std::cout<<room.get_hotel()<<"  "<<room.get_room_type()<<"  "<<room.get_date_from()<<"  "<<room.get_date_to()<<"  "<<room.get_cost_per_night()<<"\n";
    }

    delete hotel_pointer;
    hotel_pointer = nullptr;
    return 0;
}