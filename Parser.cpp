#include "Parser.h"

using namespace std;

Parser::Parser(string instr)
{
    filecontent=instr;
    Init();
}

Parser::~Parser()
{
    ;
}


void Parser::Init()
{

    Ssym["int"] = Symbol[5];
	Ssym["char"] = Symbol[6];
	Ssym["const"] = Symbol[7];
	Ssym["void"] = Symbol[8];
	Ssym["return"] = Symbol[9];
	Ssym["main"] = Symbol[10];
	Ssym["for"] = Symbol[11];
	Ssym["do"] = Symbol[12];
	Ssym["while"] = Symbol[13];
	Ssym["if"] = Symbol[14];
	Ssym["else"] = Symbol[15];
	Ssym["scanf"] = Symbol[16];
	Ssym["printf"] = Symbol[17];
	Ssym["+"] = Symbol[18];
	Ssym["-"] = Symbol[19];
	Ssym["*"] = Symbol[20];
	Ssym["/"] = Symbol[21];
	Ssym["("] = Symbol[29];
	Ssym[")"] = Symbol[30];
	Ssym["["] = Symbol[31];
	Ssym["]"] = Symbol[32];
	Ssym["{"] = Symbol[33];
	Ssym["}"] = Symbol[34];
	Ssym[","] = Symbol[35];
	Ssym[";"] = Symbol[36];
	Ssym["'"] = Symbol[37];
	Ssym["\""] = Symbol[38];
	num=0;
    ln=1;
    fc=0;
    sym="";

}

void Parser::GetCh()	//read
{

	if(fc<filecontent.length())
    {
        if((ch=filecontent.at(fc++))=='\n')
            ln++;
    }
    else
        ch=EOF;
}

string Parser::GetSym()
{
	return sym;
}

int Parser::Get_int_Id()
{
	return num;
}

string Parser::Get_str_Id()
{
	return name;
}

void Parser::GetWord()
{
    while(ch==' '||ch=='\t'||ch==0||ch=='\r'||ch=='\n')
        GetCh();
    if(ch=='0')
    {
        num=0;
        name="0";
        sym=Symbol[2];
        GetCh();
    }
    else if(ch>='1'&&ch<='9')
    {
        num=0;
        do
        {
            num=10*num+ch-'0';
            GetCh();
        }while(ch>='0'&&ch<='9');
        sym=Symbol[1];
        name=num;

    }
    else if(ch=='_'||(ch<='z'&&ch>='a')||(ch<='Z'&&ch>='A'))
    {
        do
        {
            char_stack.push_back(ch);
			GetCh();
        }while(isalnum(ch) || ch == '_');
        name = string(char_stack.begin(), char_stack.end());
		map<string, string>::iterator it = Ssym.find(name);
		if(it==Ssym.end())
        {
            sym=Symbol[0];
            char_stack.clear();
        }
        else
        {
            sym = Ssym[name];
			char_stack.clear();
        }
    }
    else if(ch=='!')
    {
        GetCh();
        if(ch=='=')
        {
            name="!=";
            sym=Symbol[27];
            GetCh();
        }
        else
            Error();
    }
    else if(ch=='=')
    {
        GetCh();
		if (ch == '=')
		{
			name = "==";
			sym = Symbol[28];
			GetCh();
		}
		else
		{
			name = "=";
			sym = Symbol[22];
		}
    }
    else if (ch == '>')
	{
		GetCh();
		if (ch == '=')
		{
			name = ">=";
			sym = Symbol[26];
			GetCh();
		}
		else
		{
			name = ">";
			sym = Symbol[25];
		}
	}
	else if (ch == '<')
	{
		GetCh();
		if (ch == '=')
		{
			name = "<=";
			sym = Symbol[24];
			GetCh();

		}
		else
		{
			name = "<";
			sym = Symbol[23];
		}
	}
	else if(ch=='\'')
    {
        char_stack.push_back(ch);
        GetCh();
        if(isalnum(ch) || ch == '_'||ch == '*'||ch == '+'||ch == '-'||ch == '/')
        {
            char_stack.push_back(ch);
            GetCh();
            if(ch=='\'')
            {
                char_stack.push_back(ch);
                GetCh();
                name = string(char_stack.begin(), char_stack.end());
                sym = Symbol[3];
                char_stack.clear();
            }
            else
                Error();
        }
        else
            Error();
    }
    else if(ch=='\"')
    {
        char_stack.push_back(ch);
        GetCh();
        while(ch==32||ch==33||(ch<=126&&ch>=35))
        {
            char_stack.push_back(ch);
            GetCh();
        }
        if(ch=='\"')
        {
            char_stack.push_back(ch);
			name = string(char_stack.begin(), char_stack.end());
			sym = Symbol[4];
			char_stack.clear();
			GetCh();
        }
        else
            Error();
    }
    else if(ch==EOF)	//如果读到文件结尾
	{
		sym=Symbol[40];
		name="";
	}
	else if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
    {
        name=ch;
        sym=Ssym[name];
        GetCh();
    }
	else
	{
		name = ch;
		map<string, string>::iterator it = Ssym.find(name);
		if (it != Ssym.end())
		{
			sym = Ssym[name];
			GetCh();
		}
		else
		{
			sym = Symbol[39];

			GetCh();
		}
	}
}


void Parser::Error() //to do
{

}
