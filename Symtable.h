#include <vector>
#include <string>
using namespace std;
struct Symtable
{
    vector<string> name;
    vector<int> func_value; //0 represents function,1 represents normal value,2represents const value,3 represents array
    vector<string> kind;    //void or int or char
    vector<int> feature;    //if is array,store its size;if is const,store value;if is function,store the number of formal parameters
    vector<int> formal_or_actual;   //0 represents actual parameter,1 represents formal parameter
    vector<int> address;
};



