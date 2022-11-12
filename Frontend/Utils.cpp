#ifndef Utils_CPP_
#define Utils_CPP_
#include <windows.h>
#include <iostream>

inline void clear_cmd_() 
{ 
    //Windows
    #if defined(_WIN32) || defined(_WIN64)
    /// @brief Clear cmd from console API (system("CLS") isn't safe) 
    /// https://stackoverflow.com/questions/6486289/how-can-i-clear-console
    /// https://stackoverflow.com/questions/5866529/how-do-we-clear-the-console-in-assembly

    CONSOLE_SCREEN_BUFFER_INFO scr_buffer;
    HANDLE console= GetStdHandle(STD_OUTPUT_HANDLE);   
    GetConsoleScreenBufferInfo(console, &scr_buffer);
    DWORD written, cells= scr_buffer.dwSize.X * scr_buffer.dwSize.Y;
    
    char fill= ' ';
    COORD topleft {0,0};
    
    FillConsoleOutputCharacter(console, fill, cells, topleft, &written);
    FillConsoleOutputAttribute(console, scr_buffer.wAttributes, cells, topleft, &written);
    SetConsoleCursorPosition(console, topleft);

    //*inexes
    #elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    std::cout<<"\033[2J\033[1;1H";

    #endif // Clear cmd in different systems
}

#endif //Utils_CPP_