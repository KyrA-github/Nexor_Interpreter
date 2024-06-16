#include "globals.hpp"

class Variables_int
{
public:
    //переменая инт
    unordered_map<string, int> variablesInteger;
    //создание/изменение переменой
    void setVariablesInteger(const string& name, int value);
    //получение значение из переменой
    int getVariableInteger(const string& name);


};