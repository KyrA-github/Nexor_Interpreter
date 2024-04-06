#pragma once
#include "globals.hpp"
#include <unordered_map>
#include <functional>
#include <sstream>

class Interpreter
{
public:
    using FunctionBlock = function<void()>;

    unordered_map<string, string> functionBlocks;
    unordered_map<string, int> variablesInteger;

    void InterpreterMainFunc(string main_source_file_directory, string sourse_file_name);
private:
    void ReadingFileLineByLine(string main_source_file_directory, string sourse_file_name);
    void ReadTokensFromLineFromFunction(string line);

    void ReadTokensFromLine();
    void ExecutionOfFunction(string function_content);

    int getVariableInteger(const string& name);
    void setVariablesInteger(const string& name, int value);

    void defineFunction(const std::string& name, const std::string& content);
    void callFunction(const string& name);

    string LineBetweenTokens(string token_1, string token_2, string line);
    bool LineContainsWord(const std::string& word, const std::string& line);

    string SearchVariablesByNameINT(unordered_map<string, int> value);

    //operators + - * /
    void PerformingMathematicalOperations(string Variable1value, string Variable2value, string Variable3sum, char operation);

    string line_file;
    string previous_line;
    size_t posed_token; 

    char lastCharline;

    bool writing_content_func = false;

    string left_part_line;
    string right_part_line;

    string temp;
    string temp_list[10];
    int temp_int;
    int temp_int_list[10];
    float temp_float;
    string temp_func;

    string currentFunction;
    string functionContent;
    string error;

    string tokens[10] =
    {
        "$func ", "$start", "int ","print"
    };
    
};


