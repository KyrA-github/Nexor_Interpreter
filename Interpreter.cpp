#include "Interpreter.hpp"

//основная функция
void Interpreter::InterpreterMainFunc(const string& main_source_file_directory, const string& sourse_file_name)
{

    
    size_t pos = sourse_file_name.find('.'); 
    if (pos != string::npos)
    {
        if (sourse_file_name.substr(pos + 1) == "nxr")
        {
            ReadingFileLineByLine(main_source_file_directory, '/'+ sourse_file_name);
        }  
    }
    else
    {
        cerr << "Error: File extension is not supported" << endl;
    }
}
// чтение файла
void Interpreter::ReadingFileLineByLine(const string& main_source_file_directory, const string& sourse_file_name)
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
        callFunction("start");
    }
    else
    {
        cerr << "Error: File not found" << endl;
    }
}

//чтение функции и выполнение
void Interpreter::ExecutionOfFunction(const string& function_content)
{
    std::istringstream iss(function_content);
    string line;
    while (getline(iss, line))
    {
        if (!line.empty())
        {
            ReadTokensFunction(line);
        }
        previous_line = line;
    }
}

void Interpreter::print(string *line)
{
    cout << line << endl;
}

// Функция для проверки, является ли символ разделителем
bool Interpreter::isDelimiter(char c) {
    return c == ' ' || c == '=' || c == '\t' || c == '\n' || c == '\r' || c == ';';
}

// Функция для проверки, является ли символ оператором
bool Interpreter::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Функция для проверки, является ли символ буквой (для имён переменных и функций)
bool Interpreter::isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Функция для проверки, является ли строка именем переменной
bool Interpreter::isVariable(const string& token, const unordered_map<string, int>& variables) {
    for (const auto& var : variables) {
        if (token == var.first)
            return true;
    }
    return false;
}

// Функция для разделения строки на токены
vector<string> Interpreter::tokenize(const string& expression) {
    vector<string> tokens;
    string token;
    for (char c : expression) {
        if (isDelimiter(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            if (c == ';') {
                    tokens.push_back(std::string(1, c));
                }
        } else if (isOperator(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, c));
        } else if (isLetter(c)) {
            token += c;
        } else {
            token += c;
        }
    }
    if (!token.empty())
        tokens.push_back(token);
    return tokens;
}

// Функция для вычисления значения выражения
int Interpreter::evaluateExpression(string& expression) {
    string expressionWithoutSpaces = removeSpaces(expression);
    vector<string> expressions = tokenize(expressionWithoutSpaces);

    int result = 0;
    char operation = '+';
    string variableName;
    for (const auto& expr : expressions) {
            if (expr == ";") {
                continue; 
            }
            vector<string> tokens = tokenize(expr);
            for (const auto& token : tokens) {
                if (isVariable(token, variablesInteger)) {
                    variableName = token;
                    result = getVariableInteger(variableName);
                } else if (isOperator(token[0])) {
                    operation = token[0];
                } else {
                    int value = stoi(token);
                    if (operation == '+') {
                        result += value;
                    } else if (operation == '-') {
                        result -= value;
                    } else if (operation == '*') {
                        result *= value;
                    } else if (operation == '/') {
                        if (value != 0) {
                            result /= value;
                        } else {
                            throw runtime_error("Division by zero");
                        }
                    }
                    //setVariablesInteger(variableName, result);
                }

            }
        }
    return result;
}



void Interpreter::DivisionIntoMethodsAndTokens(string line)
{
    line = removeSpaces(line);
    size_t pos = line.find('='); 

    string resultViariableName;
    string Method;
    if (pos != string::npos)
    {
        resultViariableName = line.substr(0, pos);
        Method = line.substr(pos + 1);
        setVariablesInteger(resultViariableName, evaluateExpression(Method));
    }

}
string Interpreter::variablesName(string& line)
{
    line = removeSpaces(line);
    size_t pos = line.find('='); 
    string resultViariableName;
    if (pos != string::npos)
    {
        resultViariableName = line.substr(0, pos);
    }
    return resultViariableName;
}
string Interpreter::removeSpaces(const string& line) 
{
  string result;
  result.reserve(line.size()); 

  for (char c : line) {
    if (c != ' ') {
      result += c; 
    }
  }
  return result;
}


//выполнение токенов в функции
void Interpreter::ReadTokensFunction(string line)
{
    for(string value_function : list_function)
    {
        if (LineContainsWord(value_function, line))
        {
            callFunction(value_function);
        }
    }
    if (LineContainsWord("int", line))
    {
        setVariablesInteger(LineBetweenTokens("int ", " =", line), stoi(LineBetweenTokens(" = ", ";", line)));
    }
    else if (LineContainsWord("print", line))
    {
        temp = LineBetweenTokens("(", ")", line);
        cout << getVariableInteger(temp) << endl;
    }
    else if (LineContainsWord("+", line) || LineContainsWord("-", line)  || LineContainsWord("*", line) || LineContainsWord("/", line))
    {
        DivisionIntoMethodsAndTokens(line);
    }
}

//создание функций
void Interpreter::ReadTokensFromLine()
{    
    if (!writing_content_func)
    {
        for (const auto& token : tokens) 
        {
            posed_token = line_file.find(token); 

            if (posed_token != string::npos)
            {
                left_part_line = line_file.substr(0, posed_token);
                right_part_line = line_file.substr(posed_token + 1);
                
                if (token == "func ")
                {
                    if (!currentFunction.empty())
                    {
                        defineFunction(currentFunction, functionContent);
                        functionContent.clear();
                    }
                    currentFunction = LineBetweenTokens(" ", "(", line_file);
                    list_function.push_back(currentFunction);
                    if (line_file.back() == '{')
                    {
                        writing_content_func = true;
                    }
                }
                else if (token == "start ")
                {
                    if (!currentFunction.empty())
                    {
                        defineFunction(currentFunction, functionContent);
                        functionContent.clear();
                    }
                    currentFunction = "start";
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


// поиск строки межру символами
string Interpreter::LineBetweenTokens(const string& token_1, const string& token_2, const string& line)
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



/*
string Interpreter::IterateOverStringCharacterByCharacter(string line)
{
    string result;
    for (char c : line)
    {
        for (int i = 0; i < 10; i++)
        {
            if (c == tokens_char[i])
            {
                size_t pos = line.find(tokens_char[i]); 
                string resultViariableName;
                int resultViariableValue;
                if (pos != string::npos)
                {
                    resultViariableName = line.substr(0, pos);

                }     
            }
        }
    }
    return result;
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

int Interpreter::performOperation(int a, int b, char op) {
        switch (op) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                if (b != 0)
                    return a / b;
                else
                    throw runtime_error("Division by zero");
            default:
                throw runtime_error("Invalid operator");
        }
    }
    

    
    // Определение функции goga
    defineFunction("goga", [](){
        cout << "Hello from goga function!" << endl;
    });

    // Вызов функции goga
    callFunction("goga");
    // temp = LineBetweenTokens(tokens[0], tokens[1]);

    // cout << temp << endl;

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
    
    
    
    for (const auto& token : tokens) 
    {
        posed_token = line.find(token); 
        if (posed_token != string::npos)
        {            
            
        }    
    }
*/
    