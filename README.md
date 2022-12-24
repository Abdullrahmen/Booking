# Multitype Booking System
> Multitype booking system (like expedia.com and booking.com) core.

-   [About Project](https://github.com/Abdullrahmen/Booking#about-project)
    -   [Backend](https://github.com/Abdullrahmen/Booking#backend)
    -   [Frontend](https://github.com/Abdullrahmen/Booking#frontend)
    -   [Class diagram](https://github.com/Abdullrahmen/Booking#class-diagram)
-   [Future updates](https://github.com/Abdullrahmen/Booking#future-updates)
-   [License](https://github.com/Abdullrahmen/Booking#license)

**Latest release**: 
> Confirmed in Windows 10 64 bit, compiled by g++

[Booking.v1.0.exe](https://github.com/Abdullrahmen/Booking/releases/download/v1.0/Booking.v1.0.exe)

# About Project
Hi, I'm Abdullrahmen, and I'm happy to introduce you to my project -Multitype booking system-.
> From calling APIs through making interfaces to creating factory methods, this project is a simulation of the process in the real world.

But before we get started, what is a booking system?

A booking system is an interface that allows people to easily choose, reserve, and pay for items(e.g. flights, hotel rooms) from different companies,
and stores different items in a container called an itinerary that can be paid for, reserved, modified, etc...

The main difference between my project and a real one is that the real one has real online APIs (I will convert mine to real ones in a future update -I hope).
### Backend
We can say that there are five primary steps here:
1. **interface to all items**
    1. Create interfaces for every company
        > If any company's API changes, the type's interface doesn't need to be changed
    2. Create interfaces + factory classes for every type
        * interfaces
            > To generalize companies' interfaces to one interface
        * factory classes
            > The programmer (in this project's frontend or any other project) doesn't need to recompile his code every time a company's API changed/added
    3. Create an interface for all items
        > To generalize types' interfaces to one global item interface to use it in itinerary or any other class that needs a general item
2. **interface for payment companies**
    > same as step one but for payment companies
3. **Create an itinerary to store items**
    * Containing factory methods to add items, and delete them in the destructor, so the programmer doesn't need to worry about items' memory management.
    * Use the payment interface to pay for items.
4. **Create a user class that stores itineraries**
    > Actually, it has to be in frontend, but because I put it in the Backend folder, I'll write it here.

### Frontend
> I made the basic process of any other project, even though I didn't focus on amazing frontend part.
* User login/sign up
* List available items according to filters
* Create/modify/remove itineraries
* I made two classes for cmd menus and will move them to another cmd tools repository soon
### Class diagram

**Before I started the project, I made my first class diagram to put my main ideas in, and it had many return types and parameters mistakes, but at least it'll give you an idea of how the interfaces and classes link to each other:**

> **For every type and payment companies**
![image](https://user-images.githubusercontent.com/87922232/202315263-1acb84f5-7f9c-4087-a326-a339516cfdf1.png)

> **The relation between itinerary class and other classes** (Here, the factory methods are in the wrong class, I moved them to the Itinerary class, so the user doesn't need to know anything about ItineraryItem class and doesn't need to worry about deleting heap stored items)
![image](https://user-images.githubusercontent.com/87922232/202315093-73ab1a63-5a78-4784-8303-18cb39ae21f4.png)

# Future updates
**These are some future updates I hope to make (any contributions would be appreciated)**

-   Convert online_api folder to real APIs
-   Sign up payment info check (in payments APIs, payment interface, Itinerary::pay, and frontend sign up)
-   Add more functionalities in payments
-   Separate login info and create a user profile
-   Convert itineraries and payment info to string to store them in one table
-   Store data in a separate file (database)
-   Remove_item in Itinerary class and customer view
-   If a reservation fail after the payment is successful, refund the money and cancel the payment
-   Refund the money after cancel a reservation
-   Add answer pattern option in InputsMenu
-   Convert itineraries vector(in User) to pointers (to prevent lots of deep copies) -Important
-   Operator = in Itinerary class
-   In OptionsMenu add the ability to disable an option (but still visible) (Used in cases like upcoming features)
-   Convert cli to gui
-   Make the admin part
-   Convert raw pointers to smart.
-   etc...



# License
**CC0 (Do whatever you want with the code) :)**
