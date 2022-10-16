#ifndef OptionsMenu_H_
#define OptionsMenu_H_
#include <iostream>
#include <vector>

typedef bool (*func_ptr)();
//Create an options menu in cmd.
class OptionsMenu
{
private:
    std::vector<std::string> options;
    std::vector<func_ptr> options_funcs;
    std::string header_str; // eg. Menu: \n
    bool is_run;
    int choosed_number; //= choosed number-1 (to make it zero based)
public:
    OptionsMenu(const std::string& header_str="Menu: \n");

    /// @brief Add an option to the menu.
    /// @param option Option string
    /// @param func Optional bool function pointer that will be called when the option choosed (bool (*)())
    void add_option(const std::string& option, func_ptr func= nullptr);

    /// @brief Remove an option from the menu.
    /// @param option Option string
    void remove_option(const std::string& option);

    /// @brief Run the options menu and print it in the cmd.
    /// After running the menu you can access the choosed option by get_choosed_option method
    /// and its function pointer by get_choosed_func method.
    /// @param clear_cmd Clear cmd before run the menu
    /// @param func_call Whether call the choosed option's function (if it exicts)
    /// @return Always return true except if the choosed option's function return false.
    bool run(bool clear_cmd=true, bool func_call=true);

    /// @brief Must run the menu before call it.
    /// @return Choosed option.
    const std::string& get_choosed_option() const;
    /// @brief Must run the menu before call it.
    /// @return Choosed option's function pointer.
    func_ptr get_choosed_func() const;
    /// @brief Must run the menu call it.
    /// @return The number written by user
    int get_choosed_number() const;

    ~OptionsMenu();
};

#endif //OptionsMenu_H_