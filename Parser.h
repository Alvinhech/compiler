#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <ctype.h>
#include <string.h>
#include "Symtable.h"
#include "quaterinstr.h"

#define MAXLENGTH 256

using namespace std;



class Parser
{
public:
	string Symbol[41]
	{
		"IDENT",	//标识符
		"NUMBER",	//非零数字
		"ZERO",	    //数字零
		"CHAR",	    //字符
		"STRING",	//字符串
		"INTsym",	//int
		"CHARsym"   ,//char
		"CONSTsym",	//const
		"VOIDsym",	//void
		"RETURNsym",//return
		"MAINsym",	//main
		"FORsym",	//for
		"DOsym",	//do
		"WHILEsym",	//while
		"IFsym",	//if
		"ELSEsym",	//else
		"SCANFsym",	//scanf
		"PRINTFsym",//printf
		"PLUS",	    //'+'
		"MINUS",	//'-'
		"MUL",	    //'*'
		"DIV",	    //'/'
		"BECOMES",	//'='
		"LESS",	    //'<'
		"LES",	    //'<='
		"GT",	    //'>'
		"BEQ",	    //'>='
		"NEQ",	    //'!='
		"EQL",	    //'=='
		"Lpar", 	//'('
		"Rpar",	    //')'
		"Lbra", 	//'['
		"Rbra",	    //']'
		"Lbrc",	    //'{'
		"Rbrc",	    //'}'
		"COMMA",	//','
		"SEMICOLON", 	//';'
		"Single quotes",	    //'''
		"Double quotes",		//'"'
		"NULL",	    //无类型
		"EOF"	    //文件结尾
	};

	map<string, string> Ssym;	//保留字、运算符表
	string sym;	    //词法分析得到的单词类型
	string name;	//若是标识符、字符或字符串，name存放他们的名字或值
	int num;	    //若是数字，num存放他的值
	char ch;	    //ch存放当前读到的一个字符
	int ln;	        //当前读到第几行
	int fc;
	string filecontent;
	vector<char> char_stack;	//当前读到的单词
	int cc;
	struct Symtable symtable;
	vector<int> line_count;     //错误处理输出行号
	vector<int> table_count;    //符号表
	vector<struct function_term*>  func_table;
	int my_count;
	int max_quaterinstr;
	vector<QuaterInstr> quaterline;
	int quaternum;
	string label1;	//for (if-else, for , dowhile)
	string label2;	//for (if-else, for , dowhile)
	int labelnum;
	struct function_term* func_term;
	int address_num;
	int call_number;
public:
	Parser(string filename);
	~Parser();
	void Init();
	void GetCh();
	void GetWord();
	void Error(string expected_string,int error_number);
	string GetSym();
	int Get_int_Id();
	string Get_str_Id();
	void Grammatical_analysis();
	void const_explain();
	void var_explain();
	void var_define();
	void func_define();
	void func_noreturn();
	void func_return();
	void const_define();
	void push_address();
	int number();
	int parameter_number();
	void Compound_statement();
	void Statement_column();
	void Statement();
	void Conditional_Statement();   //条件语句
	void Dowhile_Statement();       //do while 语句
	void For_Statement();           //for 语句
	void Empty_Statement();         //空语句
	void Nested_Statement();        //{嵌套}
	struct SymbolItem* Func_call();               //函数调用
	void Assignment();              //赋值语句
	void Write_Statement();         //写语句
	void Read_Statement();          //读语句
	void Return_Statement();        //返回语句
	struct SymbolItem* Expression();              //表达式
	struct SymbolItem* Term();                    //项
	struct SymbolItem* Factor();                  //因子
	void Condition();
	void main_define();				//main函数
	void print_symtable();
	void print_all_quater();
	string new_label(int *n);
	void print_all_func_table();
};
