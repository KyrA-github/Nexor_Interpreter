#include "globals.hpp"
#include "interpreter.hpp"

int main(int argc, char *argv[])
{
    string for_argv;
    string list_argv[3] = {"_", "_", "_"};

    for (int i = 0; i < argc; i++)
    {
        for_argv = argv[i];
        list_argv[i] = for_argv;
    }

    if (list_argv[1] == "--version")
    {
        cout << "Nexor version 0.03" << endl;
        return 0;
    }
    else if (list_argv[1] == "help")
    {
        cout << "commands:\n[Nexore --version, Nexor make, Nexor make -e, Nexor help]" << endl;
    }
    else
    {
        Interpreter inte; 
        char buffer[100];
        wchar_t wbuffer[100];

        if (GetCurrentDirectoryW(100, wbuffer) != 0) 
        {
            wcstombs(buffer, wbuffer, 100);
            string currentDir(buffer);
            inte.InterpreterMainFunc(currentDir, list_argv[1]);
        }
        else
        {
            cerr << "Error getting current working directory" << endl;
            return 1;
        }  
        
    }

    return 0;
}
