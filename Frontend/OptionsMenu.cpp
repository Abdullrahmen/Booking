#include "OptionsMenu.h"

//////////////////
//OptionsMenu Class
//////////////////

OptionsMenu::OptionsMenu(const std::string& header_str):
    options({}),
    options_funcs({}),
    header_str(header_str),
    choose_str(""), // in run function (to know number of options)
    is_run(false),
    choosed_option(""){}

void OptionsMenu::add_option(const std::string& option, func_ptr func)
{
    
}