/*
Contains:
* Base loop
* Sign up
* Login
*/

#include "Views.cpp"

bool login()
{
    clear_cmd_();//clear cmd

    //Options menu to get logined user type menu.
    OptionsMenu user_type_menu;

    user_type_menu.add_option("Customer");
    user_type_menu.add_option("Admin");
    user_type_menu.add_option("Back to main menu", pre_menu);

    if(!user_type_menu.run(false))
        return true; //Back to main menu
    auto user_type{user_type_menu.get_choosed_option()};

    auto error_msg{std::string{""}};
    while (true)
    {
        clear_cmd_();//clear cmd
        std::cout<<error_msg;
        error_msg="";

        //Inputs menu to get login info.
        InputsMenu menu;

        menu.add_input("Name");
        menu.add_input("Password", '$');
        menu.run(false);

        if(user_type=="Customer")
        {
            Customer customer;
            LoginInfo login_info{menu.get_answers()[0], menu.get_answers()[1]};

            if(customer.login(login_info))
                while(customer_view(customer));//Customer view loop.
            else
            {
                error_msg+= "Wrong username or password\n\n";
                continue;//relogin
            }
        }
        else if(user_type=="Admin")
        {
            Admin admin;
            LoginInfo login_info{menu.get_answers()[0], menu.get_answers()[1]};

            if(admin.login(login_info))
                while(admin_view(admin));//Admin view loop.
            else
            {
                //return true;//return to base loop (base menu).
                error_msg+= "Wrong username or password\n\n";
                continue;//relogin
            }
        }
        return true;//when the user's view loop end return to base loop (base menu).
    }
}

bool sign_up()
{
    clear_cmd_();//clear cmd
    /*Options menu to get logined user type menu.*/
    OptionsMenu user_type_menu;

    user_type_menu.add_option("Customer");
    user_type_menu.add_option("Admin");
    user_type_menu.add_option("Back to main menu", pre_menu);


    if(!user_type_menu.run(false))
        return true; //Back to main menu
    auto user_type{user_type_menu.get_choosed_option()};
    
    auto error_msg{std::string{""}};   
    //Sign up loop
    while (true)
    {
        clear_cmd_();//clear cmd
        std::cout<<error_msg;
        error_msg="";//reset error message

        
        /*Inputs menu to get login info.*/
        InputsMenu menu;

        menu.add_input("Name", '\n');
        menu.add_input("Password", '$');
        menu.run(false);
        //InputsMenu already check for empty.
        /*if(menu.get_answers()[1]=="")
        {
            error_msg+= "Password can't be empty.\n\n";
            continue;
        }*/
        LoginInfo login_info{menu.get_answers()[0], menu.get_answers()[1]};

        if(user_type=="Customer")
        {
            /*Get payment methods info from customer (at least one payment to sign up)*/

            auto payment_methods{Data::get_payment_methods()};
            int methods_signed{0};

            ///Create empty methods info with same order as payment_methods
            std::vector<PaymentInfo> methods_info;
            for (int i = 0; i < (int)payment_methods.size(); i++)
                methods_info.push_back(PaymentInfo{});
            
            //Payments info loop.(break then continue when finish with error_msg)
            //(break only when successfully finished)
            //(else will return false)
            bool is_error{false};
            while (true)
            {
                OptionsMenu menu{"\n Add payment info :\n"};

                for (int i = 0; i < (int)payment_methods.size(); i++)
                    menu.add_option(payment_methods[i]);
                
                if(methods_signed>0)
                    menu.add_option("Finish");
                
                menu.add_option("Back to main menu", pre_menu);
                
                if(!menu.run())
                    return true; // Back to base(main) menu.

                if(menu.get_choosed_option()=="Finish")
                    break; //Successfully signed up
                
                /*ask payment info*/

                int idx{menu.get_choosed_number()-1}; //-1 to make it zero based.
                methods_info[idx]= ask_payment_info(); //get info from user
                methods_signed+=1;

                // Future update:
                /// Add check payment info methods in the payments APIs and interface then check it here.
                if(methods_info[idx].is_empty())
                {
                    //back to the beginning of sign up
                    error_msg+="Invalid Payment Info\n\n";
                    is_error=true;
                    break;
                }
            }
            if(is_error)
                continue;

            if(!Customer::register_(login_info, methods_info))
            {
                error_msg+= "Name already taken\n\n";
                continue;
            }
        }
        else if(user_type=="Admin")
        {
            if(!Admin::register_(login_info))
            {
                error_msg+= "Name already taken\n\n";
                continue;
            }
        }

        return true;//Pass all checks :)
    }
}

int main()
{
    //Base menu.
    OptionsMenu menu;

    menu.add_option("Login", login);
    menu.add_option("Sign up", sign_up);
    menu.add_option("Exit", pre_menu);

    while(menu.run());//Base app loop.
    return 0;

}