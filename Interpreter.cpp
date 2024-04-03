#include "Interpreter.hpp"
void Interpreter::InterpreterMainFunc(string main_source_file_directory, string sourse_file_name)
{
    ReadingFileLineByLine(main_source_file_directory, '/'+ sourse_file_name);
}

void Interpreter::ReadTokensFromLine()
{    
    /*
    // Определение функции goga
    defineFunction("goga", [](){
        cout << "Hello from goga function!" << endl;
    });

    // Вызов функции goga
    callFunction("goga");
    */
    // temp = LineBetweenTokens(tokens[0], tokens[1]);

    // cout << temp << endl;
    if (!writing_content_func)
    {
        for (const auto& token : tokens) 
        {
            posed_token = line_file.find(token); 

            if (posed_token != string::npos)
            {
                left_part_line = line_file.substr(0, posed_token);
                right_part_line = line_file.substr(posed_token + 1);
                
                if (token == "$func ")
                {
                    if (!currentFunction.empty())
                    {
                        defineFunction(currentFunction, functionContent);
                        functionContent.clear();
                    }
                    currentFunction = LineBetweenTokens(" ", "(");
                    writing_content_func = true;
                }
            }    
        }
    }
    else
    {   
        posed_token = line_file.find("}!"); 
        if (posed_token != string::npos)
        {
            defineFunction(currentFunction, functionContent);
            functionContent.clear();
            currentFunction.clear();
            writing_content_func = false;
        }
        else{
            functionContent += line_file + "\n";
        }
    }
}


void Interpreter::ReadingFileLineByLine(string main_source_file_directory, string sourse_file_name)
{
    ifstream main_source_file(main_source_file_directory + sourse_file_name);

    if (main_source_file.is_open())
    {
        while (getline(main_source_file, line_file))
        {
            if (!line_file.empty()) 
            {
                lastCharline = line_file.back();
                ReadTokensFromLine();
            } 
        }
        callFunction("main");
    }
    else
    {
        cerr << "Error: File not found" << endl;
    }
}

string Interpreter::LineBetweenTokens(string token_1, string token_2)
{
    size_t start_pos = line_file.find(token_1);
    size_t end_pos = line_file.find(token_2, start_pos);

    if (start_pos != std::string::npos && end_pos != std::string::npos) {
        std::string result = line_file.substr(start_pos + 1, end_pos - (start_pos + 1));
        return result;
    } else {
        return "";
    }
}

void Interpreter::callFunction(const string& name)
{
    auto it = functionBlocks.find(name);
    if (it != functionBlocks.end()) {
        // Вывод содержимого функции (для демонстрации)
        std::cout << "Content of function " << name << ":\n" << it->second << std::endl;
        // Теперь здесь вы можете интерпретировать содержимое функции
    } else {
        std::cerr << "Error: Function " << name << " is not defined!" << std::endl;
    }
}

void Interpreter::defineFunction(const std::string& name, const std::string& content)
{
    functionBlocks[name] = content;
}
