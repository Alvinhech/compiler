#pragma once
#include<iostream>
#include <string>
#include<fstream>
#include <map>
#include<vector>
#include<ctype.h>
#include <string.h>

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
public:
	Parser(string filename);
	~Parser();
	void Init();
	void GetCh();
	void GetWord();
	void Error();
	string GetSym();
	int Get_int_Id();
	string Get_str_Id();
};
