#include <vector>
#include <string>
#include "Symtable.h"
#include "quaterinstr.h"

struct globaldata_term
{
    string name;
    int type;   //1代表普通变量 ，2代表const ，3代表array，0代表string
    string kind;   //int  char
    int value;  //constant--value,array--space
    string str_value;
};

class MIPS
{
public:
    struct Symtable symtable;   //符号表
    vector<int> table_count;
    vector<struct function_term*>  func_table; //分程序表
    vector<QuaterInstr> quaterline; //四元式
    vector<struct globaldata_term*> globaldata;
    vector<string> mips_code;
    int func_count;
    int cur_call;
    int cur_quater;
    int cur_var;
    int cur_formal;
    int cur_space;
public:
    MIPS(struct Symtable _symtable,vector<int> _table_count,vector<struct function_term*>  _func_table,vector<QuaterInstr> _quaterline)
    {
        symtable=_symtable;
        table_count=_table_count;
        func_table=_func_table;
        quaterline=_quaterline;
    }
    void Init();
    void generate_mips();
    int find_quater(string n);
    void generate_src(SymbolItem* temp,int n);
    void generate_des(SymbolItem* temp);
    void print_asm();
};
