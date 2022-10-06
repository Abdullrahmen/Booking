#ifndef InputsMenu_H_
#define InputsMenu_H_
#include <iostream>
#include <vector>

/// @brief Create a string inputs menu in cmd.
class InputsMenu
{
private:
    /// All vectors have same index and size.
    std::vector<std::string> inputs;
    std::vector<bool> multiword_;
    std::vector<int> max_char_;
    std::vector<char> end_char_;
    std::vector<std::string> answers;//same index as inputs.
    
    std::string header_str;
    bool is_run;

public:
    InputsMenu(const std::string& header_str="");

    /// @brief Add an input to the menu.
    /// @param input Input string
    /// @param max_char Max number of chars (the exceed will be ignored)
    /// @param multiword Bool if the input is multiword
    /// @param end_char If multiword is true this char will end the stream 
    /// (eg. if it's \\n then the stream will read until the user press enter)
    /// (if you want multiline answer just change the end_char to eg. "$")
    void add_input(const std::string& input, bool multiword=false, char end_char='\n', int max_char=100);

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