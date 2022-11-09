#include "InputsMenu.h"
#include <algorithm>

//////////////////
//InputsMenu Class
//////////////////

InputsMenu::InputsMenu(const std::string& header_str):
                    header_str(header_str){}

void InputsMenu::add_input(const std::string& input, char end_char, int max_char, int answer_type, bool allow_empty)
{
    inputs.push_back(input);
    max_char_.push_back(max_char);
    end_char_.push_back(end_char);
    answer_type_.push_back(answer_type);
    allow_empty_.push_back(allow_empty);
}

void InputsMenu::remove_input(const std::string& input)
{
    auto it{std::find(inputs.begin(),inputs.end(),input)};

    if(it!= inputs.end())
    {
        int i= it - inputs.begin();
        inputs.erase(it);
        max_char_.erase(max_char_.begin()+i);
        end_char_.erase(end_char_.begin()+i);
        answer_type_.erase(answer_type_.begin()+i);
        allow_empty_.erase(allow_empty_.begin()+i);
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
        /*
        Will get the input until end_char then get first word if multiword==false or split it if max_char==0
        */

        auto answer{std::string{}};
        //char answer[max_char_[i]]{""}; // converted to string to use getline(string) to get unlimited characters
        auto end_char{end_char_[i]};
        auto answer_type{answer_type_[i]};
        auto allow_empty{allow_empty_[i]};

        //Fix if the user print one word then press enter without press space before it
        auto one_word{false};
        if(end_char==' ')
        {
            one_word=true;
            end_char='\n';
        }

        std::cout<< inputs[i]<<": ";
        if (end_char!='\n')
        {
            std::cout<<"(Press ";

            auto is_symbol{false};
            for (int s = 0; s < (int)std::size(symbols); s++)
            {
                if(end_char==symbols[s])
                {
                    std::cout<<symbols_names[s];
                    is_symbol=true;
                    break;
                }
            }
            if(!is_symbol)
                std::cout<<end_char_[i];

            std::cout<<" then Enter to finish)\n";
        }
        
        // Check for:
        // answer_type
        // empty answer
        while (true)
        {
            //converted to getline(string) to get unlimited characters + prevent minor problems
            std::getline(std::cin, answer, end_char);
            //std::cin.getline(answer, max_char_[i], end_char);

            try
            {
                if(!allow_empty && answer.length()<=0)
                    throw std::invalid_argument("Not allow empty");

                if(allow_empty && answer.length()==0)
                    break;

                if(answer_type==0) //string
                    break;
                else if(answer_type==1) //check for int convert validation
                    std::stoi(answer);
                else if(answer_type==2) //double
                    std::stod(answer);
            }
            catch(const std::exception& e)
            {
                std::cout<<"Please enter a valid answer: ";
                if (end_char!='\n')
                    std::cout<<"\n";
                continue;
            }

            break;
        }
        
        // if end_char != '\n' then the user need to press enter after end_char to apply it 
        // so we need to ignore characters between end_char and enter
        if(end_char!='\n')
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }


        if(one_word)
            answer= answer.substr(0, answer.find(' '));//First word only.
        
        if(max_char_[i]!=0)
            answer= answer.substr(0, max_char_[i]);//Limited char        
        
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
