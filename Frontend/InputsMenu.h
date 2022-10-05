#ifndef InputsMenu_H_
#define InputsMenu_H_
#include <iostream>
#include <vector>

/// @brief Create a string inputs menu in cmd.
class InputsMenu
{
private:
    std::vector<std::string> inputs;
    std::vector<std::string> answers;//same index as inputs.
    std::string header_str;
    bool is_run;

public:
    InputsMenu(const std::string& header_str="Menu: ");

    /// @brief Add an input to the menu.
    /// @param input Input string
    /// @param multiword Multiword input
    /// @param multiline Multiline input (override multiword) (end the input with end_char)
    /// @param end_char If multiline is true this will end the input
    void add_input(const std::string& input, bool multiword=false, bool multiline=false, char end_char='$');

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