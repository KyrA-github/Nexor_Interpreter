#pragma once
#include "globals.hpp"
#include <unordered_map>
#include <functional>

class Interpreter
{
public:
    using FunctionBlock = function<void()>;

    unordered_map<string, string> functionBlocks;
    void InterpreterMainFunc(string main_source_file_directory, string sourse_file_name);
private:
    void ReadTokensFromLine();
    void ReadingFileLineByLine(string main_source_file_directory, string sourse_file_name);
    void defineFunction(const std::string& name, const std::string& content);
    void callFunction(const string& name);
    string LineBetweenTokens(string token_1, string token_2);

    string line_file;
    size_t posed_token; 

    char lastCharline;

    bool writing_content_func = false;

    string left_part_line;
    string right_part_line;

    string temp;
    string temp_func;

    string currentFunction;
    string functionContent;

    string tokens[10] =
    {
        "#", ";", "(", ")","$func "
    };
    
};


