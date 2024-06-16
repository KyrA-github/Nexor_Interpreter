#include "variables_int.hpp"

//задать переменную
void Variables_int::setVariablesInteger(const string& name, int value) {
    variablesInteger[name] = value;
}

//воспользоваться переменной
int Variables_int::getVariableInteger(const string& name) {
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