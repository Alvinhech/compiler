#include <vector>
#include <string>
using namespace std;
struct Symtable
{
    vector<string> name;
    vector<int> func_value; //0 represents function,1 represents normal value,2represents const value,3 represents array
    vector<string> kind;    //void or int or char
    vector<int> feature;    //if is array,store its size;if is const,store value;if is function,store the number of formal parameters
    vector<int> formal_or_actual;   //0 represents actual parameter,1 represents formal parameter;if is function ,represents the numbers of QuaterInstr
    vector<int> address;
};


struct function_term
{
    string name;
    int formal_parameters;  //formal
    int var_space;          //formal+actual
    int quater_space;
    int function_call_space;
};
