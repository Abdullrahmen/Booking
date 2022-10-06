#include "InputsMenu.h"
#include <algorithm>
#include <limits>

//////////////////
//InputsMenu Class
//////////////////

InputsMenu::InputsMenu(const std::string& header_str):
                    header_str(header_str){}

void InputsMenu::add_input(const std::string& input, bool multiword, char end_char, int max_char)
{
    inputs.push_back(input);
    max_char_.push_back(max_char);
    multiword_.push_back(multiword);
    end_char_.push_back(end_char);
}

void InputsMenu::remove_input(const std::string& input)
{
    auto it{std::find(inputs.begin(),inputs.end(),input)};

    if(it!= inputs.end())
    {
        int i= it - inputs.begin();
        inputs.erase(it);
        max_char_.erase(max_char_.begin()+i);
        multiword_.erase(multiword_.begin()+i);
        end_char_.erase(end_char_.begin()+i);
    }
    else
    {
        auto e{std::string{"Didn't find input (\""}};
        e+= input;
        e+= "\") to remove it.\n";
        e+= "The menu has the following inputs: \n{";
        for (auto &i : inputs)
        {
            e+= i;
            e+= ",  ";
        }
        e= e.substr(0, e.size()-3);
        e+= "}";
        
        throw std::invalid_argument(e);
    }
}

void InputsMenu::run(bool clear_cmd)
{
    if(inputs.size()<1)
        throw std::invalid_argument("Must add at least one input before run the menu.");

    if(clear_cmd)
        std::cout << "\033[2J\033[1;1H";

    std::cout<< header_str;

    char symbols[]{'\n','\t'};
    std::string symbols_names[]{"Enter", "Tab"};

    for (int i = 0; i < (int)inputs.size(); i++)
    {
        char answer[max_char_[i]]{""};
        std::cout<< inputs[i]<<": ";

        if(multiword_[i])
        {
            std::cout<<"(Press \"";
            
            auto is_symbol{false};
            for (int s = 0; s < (int)std::size(symbols); s++)
            {
                if(end_char_[i]==symbols[s])
                {
                    std::cout<<symbols_names[s];
                    is_symbol=true;
                    break;
                }
            }
            if(!is_symbol)
                std::cout<<end_char_[i];

            std::cout<<"\" then Enter to finish)\n";
            
            std::cin.getline(answer, max_char_[i], end_char_[i]);
        }
        else
            std::cin>>answer;

        //clear flags and buffer stored.
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        answers.push_back(answer);
    }
    is_run=true;
}

const std::vector<std::string>& InputsMenu::get_inputs() const {return inputs;}

const std::vector<std::string>& InputsMenu::get_answers() const 
{
    if(!is_run)
        throw std::invalid_argument("Must run the menu before call get_answers method.");

    return answers;
}

InputsMenu::~InputsMenu(){}
