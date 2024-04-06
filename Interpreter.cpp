#include "Interpreter.hpp"

//основная функция
void Interpreter::InterpreterMainFunc(string main_source_file_directory, string sourse_file_name)
{
    ReadingFileLineByLine(main_source_file_directory, '/'+ sourse_file_name);
}

// чтение файла
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
            previous_line = line_file;
        }
        callFunction("$start");
    }
    else
    {
        cerr << "Error: File not found" << endl;
    }
}


//
string Interpreter::SearchVariablesByNameINT(unordered_map<string, int> value)
{
    for (const auto& pair : variablesInteger) {

    }
    return "";
}

void Interpreter::PerformingMathematicalOperations(string Variable1value, string Variable2value, string Variable3sum, char operation)
{
    bool value1 = false;
    bool value2 = false;
    int value1Int = 0;
    int value2Int = 0;
    int result = 0;
    try
    {
        temp_int_list[0] = stoi(Variable1value);
        value1 = true;
    }
    catch(...)
    {
    }
    try
    {
        temp_int_list[1] = stoi(Variable2value);
        value2 = true;
    }
    catch(...)
    {
    }
    
    if (value1) 
    {
        value1Int = temp_int_list[0]; 
    }
    else 
    {
        value1Int = getVariableInteger(Variable1value);
    }

    if (value2) 
    {
        value2Int = temp_int_list[1];
    } 
    else 
    {
        value2Int = getVariableInteger(Variable2value); 
    }

    switch (operation) {
    case '+':
        result = value1Int + value2Int;
        break;
    case '-':
        result = value1Int - value2Int;
        break;
    case '*':
        result = value1Int * value2Int;
        break;
    case '/':
        result = value1Int / value2Int;
        break;
    default:
        break;
    }

    setVariablesInteger(Variable3sum, result);

}

//выполнение токенов в функции
void Interpreter::ReadTokensFromLineFromFunction(string line)
{
    if (LineContainsWord("int", line))
    {
        setVariablesInteger(LineBetweenTokens("int ", " =", line), stoi(LineBetweenTokens(" = ", ";", line)));
    }
    else if (LineContainsWord("print", line))
    {
        temp = LineBetweenTokens("(", ")", line);
        cout << getVariableInteger(temp) << endl;
    }
    else if (LineContainsWord("+",line))
    {
        PerformingMathematicalOperations(LineBetweenTokens("= ", " + ", line), LineBetweenTokens(" + ", ";", line), LineBetweenTokens("    ", " =", line), '+');
    }           
    else if (LineContainsWord("-",line))
    {
        PerformingMathematicalOperations(LineBetweenTokens("= ", " - ", line), LineBetweenTokens(" - ", ";", line), LineBetweenTokens("    ", " =", line), '-');
    }           
    else if (LineContainsWord("*",line))
    {
        PerformingMathematicalOperations(LineBetweenTokens("= ", " * ", line), LineBetweenTokens(" * ", ";", line), LineBetweenTokens("    ", " =", line), '*');
    }           
    else if (LineContainsWord("/",line))
    {
        PerformingMathematicalOperations(LineBetweenTokens("= ", " / ", line), LineBetweenTokens(" / ", ";", line), LineBetweenTokens("    ", " =", line), '/');
    }           

    
    // for (const auto& token : tokens) 
    // {
    //     posed_token = line.find(token); 
    //     if (posed_token != string::npos)
    //     {            
            
    //     }    
    // }
}

//создание функций
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
                    currentFunction = LineBetweenTokens(" ", "(", line_file);
                    if (line_file.back() == '{')
                    {
                        writing_content_func = true;
                    }
                }
                else if (token == "$start")
                {
                    if (!currentFunction.empty())
                    {
                        defineFunction(currentFunction, functionContent);
                        functionContent.clear();
                    }
                    currentFunction = "$start";
                    if (line_file.back() == '{')
                    {
                        writing_content_func = true;
                    }
                }
            }    
        }
    }
    else
    {   
        posed_token = line_file.find("}"); 
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

//чтение функции и выполнение
void Interpreter::ExecutionOfFunction(string function_content)
{
    std::istringstream iss(function_content);
    string line;
    while (getline(iss, line))
    {
        if (!line.empty())
        {
            ReadTokensFromLineFromFunction(line);
        }
        previous_line = line;
    }
}




// поиск строки межру символами
string Interpreter::LineBetweenTokens(string token_1, string token_2, string line)
{
    size_t startPos = line.find(token_1);
    if (startPos == std::string::npos)
        return ""; // Не найден начальный токен

    startPos += token_1.length();
    size_t endPos = line.find(token_2, startPos);
    if (endPos == std::string::npos)
        return ""; // Не найден конечный токен

    return line.substr(startPos, endPos - startPos);
}

//поиск симавола/слова в строке
bool Interpreter::LineContainsWord(const std::string& word, const std::string& line) 
{
        size_t pos = line.find(word);

        while (pos != std::string::npos) 
        {
            if ((pos == 0 || !isalnum(line[pos - 1])) && (pos + word.length() == line.length() || !isalnum(line[pos + word.length()]))) 
            { 
                return true;
            }
            pos = line.find(word, pos + 1); 
        }

        return false;
}

//чтение функции
void Interpreter::callFunction(const string& name)
{
    auto it = functionBlocks.find(name);
    if (it != functionBlocks.end()) 
    {
        //cout << "Content of function " << name << ":\n" << it->second << endl << "||" << endl;
        ExecutionOfFunction(it->second);
    } 
    else
    {
        cerr << "Error: Function " << name << " is not defined!" << endl;
    }
}

// создание функции
void Interpreter::defineFunction(const string& name, const string& content)
{
    functionBlocks[name] = content;
}

//задать переменную
void Interpreter::setVariablesInteger(const string& name, int value) {
    variablesInteger[name] = value;
}

//воспользоваться переменной
int Interpreter::getVariableInteger(const string& name) {
    try
    {
        if (variablesInteger.find(name) != variablesInteger.end()) 
        {
            return variablesInteger[name];
        } 
        else 
        {
            cerr << "Error: Variable " << name << " is not defined!" << endl;
        return 0; 
        }
    }
    catch (const exception& error)
    {
        cerr << "Error: " << error.what() << endl;
        return 0;
    }
}