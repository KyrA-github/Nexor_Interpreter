#pragma once
#include "globals.hpp"


class Interpreter
{
public:
    using FunctionBlock = function<void()>;

    //блок функций
    unordered_map<string, string> functionBlocks;
    //блок метода
    unordered_map<string, string> metodlocks;
    //переменая инт
    unordered_map<string, int> variablesInteger;
    vector<string> list_function;

    // основная функция
    void InterpreterMainFunc(string main_source_file_directory, string sourse_file_name);
private:
    
    /*работа с функциями*/   
    //созданание функции
    void defineFunction(const string& name, const string& content);
    //получение из функчии
    void callFunction(const string& name);
    //выполнение функции
    void ExecutionOfFunction(string function_content);
    //поиск функции
    void ReadTokensFromLine();

    /*работа с перемеными*/
    //поиск переменой по названию типа инт
    string SearchVariablesByNameINT(unordered_map<string, int> value);
    //создание/изменение переменой
    void setVariablesInteger(const string& name, int value);
    //получение значение из переменой
    int getVariableInteger(const string& name);

    //операторы + - * /
    void PerformingMathematicalOperations(string Variable1value, string Variable2value, string Variable3sum, char operation);

    /*методы*/
    //вывод текста
    void print(string *line);
    
    /*работа со строками*/
    //удаление пробелов
    string removeSpaces(const string& str);
    //нахожнение слова в строке
    bool LineContainsWord(const string& word, const string& line);
    //нахождение строку между строк
    string LineBetweenTokens(string token_1, string token_2, string line);
    //разбор строки на методы и методы
    void DivisionIntoMethodsAndTokens(string line);
    // чтение токенов в функции
    void ReadTokensFunction(string line);
    //чтение по строчно
    void ReadingFileLineByLine(string main_source_file_directory, string sourse_file_name);

    string variablesName(string line);


    int evaluateExpression(string expression);
    vector<string> tokenize(const string& expression);
    bool isVariable(const string& token, const unordered_map<string, int>& variables);
    bool isLetter(char c);
    bool isOperator(char c);
    bool isDelimiter(char c);
    int performOperation(int a, int b, char op);


    string IterateOverStringCharacterByCharacter(string line);
    string line_file;
    string previous_line;
    size_t posed_token; 

    char lastCharline;

    bool writing_content_func = false;

    string left_part_line;
    string right_part_line;


    //временные переменные
    string temp;
    string temp_list[10];
    int temp_int;
    int temp_int_list[10];
    float temp_float;
    string temp_func;

    string currentFunction;
    string functionContent;

    string tokens[10] =
    {
        "$func ", "$start", "int ","print"
    };
    
    char tokens_char[10] =
    {
        '(', ')', '=', '+', '-', '*', '/'
    };
};


