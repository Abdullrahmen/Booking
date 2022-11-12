#ifndef InputsMenu_H_
#define InputsMenu_H_
#include <iostream>
#include <vector>
#include <limits>

/// @brief Create a string inputs menu in cmd.
class InputsMenu
{
private:
    /// All vectors have same index and size.
    std::vector<std::string> inputs;
    std::vector<int> max_char_;
    std::vector<char> end_char_;
    std::vector<int> answer_type_;
    std::vector<bool> allow_empty_;
    std::vector<std::string> answers;//same index as inputs.
    
    std::string header_str;
    bool is_run;

public:
    InputsMenu(const std::string& header_str="");

    /*Answer pattern -> Future update*/

    /// @brief Add an input to the menu.
    /// @param input Input string
    /// @param end_char This char will end the input (the exceed will be ignored)\n
    /// (eg. if it's '\\n' then the stream will read until the user press enter)\n
    /// (if you want one word input change end_char to ' ')\n
    /// (if you want multiline input change end_char to something else eg. '$')
    /// @param max_char Max number of chars (the exceed will be ignored) (if it's 0 then it's unlimited)
    /// @param answer_type 0:string, 1:int, 2:double (check for convert validation only)
    /// @param allow_empty 
    void add_input(const std::string& input, char end_char=' ', int max_char=0, int answer_type=0, bool allow_empty=true);

    /// Later feature.
    //void add_multi_input() // eg. string is 'Ahmed,John,Sama' and return vector of string 

    /// @brief Remove an input from the menu.
    /// @param input Input string
    void remove_input(const std::string& input);

    /// @brief Run the string inputs menu and print it in the cmd.
    /// After running the menu you can access the answers by get_answers method.
    /// @param clear_cmd Clear cmd before run the menu 
    void run(bool clear_cmd=true);

    /// @return inputs strings
    const std::vector<std::string>& get_inputs() const;
    /// @brief Must run the menu before call it.
    /// @return vector of answers from cmd (has same index as inputs)
    const std::vector<std::string>& get_answers() const;

    ~InputsMenu();
};


#endif //InputsMenu_H_