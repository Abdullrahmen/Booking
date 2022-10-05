#include "InputsMenu.h"

//////////////////
//InputsMenu Class
//////////////////

InputsMenu::InputsMenu(const std::string& header_str):
                    header_str(header_str){}

void InputsMenu::add_input(const std::string& input, bool multiword=false, bool multiline=false, char end_char='$')
{

}

void InputsMenu::remove_input(const std::string& input)
{

}

void InputsMenu::run(bool clear_cmd)
{
    
}

const std::vector<std::string>& InputsMenu::get_inputs() const {return inputs;}

const std::vector<std::string>& InputsMenu::get_answers() const {return answers;}

InputsMenu::~InputsMenu(){}
