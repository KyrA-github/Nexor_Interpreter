#include "Interpreter.hpp"
void Interpreter::InterpreterMainFunc(string main_source_file_directory, string sourse_file_name)
{
    ReadingFileLineByLine(main_source_file_directory, '/'+ sourse_file_name);
}

string Interpreter::LineBetweenTokens(string token_1, string line) {
    size_t start_pos = line.find(token_1);
    if (start_pos == string::npos)
        return ""; 

    return token_1;
}


void Interpreter::ReadTokensFromLineFromFunction(string line)
{
    for (const auto& token : tokens) 
    {
        posed_token = line.find(token); 
        //cout << "ffffff:"<< token << endl;
        if (posed_token != string::npos)
        {
            cout << "GGGGGG:"<< token << endl;
            cout << line << endl;
            
            temp_func = LineBetweenTokens(token, line);
            if (temp_func == "int")
            {
                cout << "YYYYYY:"<< token << endl;
                cout << line << endl;
                cout << token << endl;
                temp = LineBetweenTokens("int ", " = ", line);
                cout << temp << endl;
                setVariablesInteger(LineBetweenTokens("int", "=", line), 16);
            }
            else if (temp_func == "print")
            {
                temp = LineBetweenTokens("(", ")", line);
                cout << temp << endl;
                cout << getVariableInteger(temp) << endl;
            }
        }    
    }
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

void Interpreter::ExecutionOfFunction(string function_content)
{
    istringstream iss(function_content);
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

string Interpreter::LineBetweenTokens(string token_1, string token_2, string line)
{
    size_t start_pos = line.find(token_1);
    size_t end_pos = line.find(token_2, start_pos);

    if (start_pos != string::npos && end_pos != string::npos) {
        string result = line.substr(start_pos + 1, end_pos - (start_pos + 1));
        return result;
    } else {
        return "";
    }
}

void Interpreter::callFunction(const string& name)
{
    auto it = functionBlocks.find(name);
    if (it != functionBlocks.end()) 
    {
        // Вывод содержимого функции (для демонстрации)
        cout << "Content of function " << name << ":\n" << it->second << endl;
        // Теперь здесь вы можете интерпретировать содержимое функции
        ExecutionOfFunction(it->second);
    } 
    else
    {
        cerr << "Error: Function " << name << " is not defined!" << endl;
    }
}

void Interpreter::defineFunction(const string& name, const string& content)
{
    functionBlocks[name] = content;
}

void Interpreter::setVariablesInteger(const string& name, int value) {
    variablesInteger[name] = value;
}

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