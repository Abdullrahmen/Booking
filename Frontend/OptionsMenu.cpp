#include "OptionsMenu.h"
#include <algorithm>
#include <limits>
#include "Utils.cpp"

//////////////////
//OptionsMenu Class
//////////////////

OptionsMenu::OptionsMenu(const std::string& header_str):
    options({}),
    options_funcs({}),
    header_str(header_str),
    is_run(false),
    choosed_number(0){}

void OptionsMenu::add_option(const std::string& option, func_ptr func)
{
    options.push_back(option);
    options_funcs.push_back(func);
}

void OptionsMenu::remove_option(const std::string& option)
{
    auto it {std::find(options.begin(), options.end(), option)};

    if(it!= options.end())
    {
        int i;
        i= it- options.begin();
        options.erase(it);
        options_funcs.erase(i+options_funcs.begin());//same index as options
    }
    else
    {
        auto e{std::string{"Didn't find option (\""}};
        e+= option;
        e+= "\") to remove it.\n";
        e+= "The menu has the following options: \n{";
        for (auto &i : options)
        {
            e+= i;
            e+= ",  ";
        }
        e= e.substr(0, e.size()-3);
        e+= "}";
        
        throw std::invalid_argument(e);
    }
}

bool OptionsMenu::run(bool clear_cmd, bool func_call)
{
    if(options.size()<1)
        throw std::invalid_argument("Must add at least one option before run the menu.");

    if(clear_cmd)
        clear_cmd_();

    std::cout<< header_str;

    for (int i = 0; i < (int)options.size(); i++)
        std::cout<<"\t"<<i+1<<": "<<options[i]<<"\n";
    
    std::cout<<"\nEnter a number in range 1 - "<<options.size()<<": ";
    
    std::string choosed_number_{""};
    //Check if the input is a number and in the valid range.
    while (true)
    {
        try
        {
            std::getline(std::cin, choosed_number_);

            if(choosed_number_.length()<=0) //the user didn't type anything
                throw std::invalid_argument("Invalid choosed number.");


            choosed_number= std::stoi(choosed_number_)-1;// -1 to make it zero based.
            if(choosed_number<0 || choosed_number>options.size()-1)
                throw std::invalid_argument("Invalid choosed number.");
        }
        catch(const std::exception& e)
        {
            std::cout<<"Please enter a valid number in range 1 - "<<options.size()<<": ";
            continue;
        }
        break;
    }
    is_run=true;

    if(func_call && options_funcs[choosed_number]!=nullptr)
        return options_funcs[choosed_number]();

    return true;
}

const std::string& OptionsMenu::get_choosed_option()const 
{
    if(!is_run)
        throw std::invalid_argument("Must run the menu before call get_choosed_option method.");

    return options[choosed_number];
}

func_ptr OptionsMenu::get_choosed_func()const 
{
    if(!is_run)
        throw std::invalid_argument("Must run the menu before call get_choosed_func method.");

    return options_funcs[choosed_number];
}

int OptionsMenu::get_choosed_number()const
{
    return choosed_number+1;//to return it to 1 based
}

OptionsMenu::~OptionsMenu(){}