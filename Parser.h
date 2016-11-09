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
		"IDENT",	//��ʶ��
		"NUMBER",	//��������
		"ZERO",	    //������
		"CHAR",	    //�ַ�
		"STRING",	//�ַ���
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
		"NULL",	    //������
		"EOF"	    //�ļ���β
	};

	map<string, string> Ssym;	//�����֡��������
	string sym;	    //�ʷ������õ��ĵ�������
	string name;	//���Ǳ�ʶ�����ַ����ַ�����name������ǵ����ֻ�ֵ
	int num;	    //�������֣�num�������ֵ
	char ch;	    //ch��ŵ�ǰ������һ���ַ�
	int ln;	        //��ǰ�����ڼ���
	int fc;
	string filecontent;
	vector<char> char_stack;	//��ǰ�����ĵ���
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
