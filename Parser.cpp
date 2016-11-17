#include "Parser.h"

using namespace std;
vector<string> kind;
vector<string> value;
int correct_flag=0;
void Parser::Error(string expected_string,int error_number=0) //to do
{
    correct_flag=1;
    int n=0,i=0;
    while(i<=cc)
    {
        if(line_count.at(n)<i)
            n++;
        i++;
    }
    if(i==line_count.at(n-1)+1+1)
        n--;
    if(error_number==0)
    {
        printf("Error: Expected a \"%s\" in line %d.\n",expected_string.c_str(),n+1);
    }
}


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
    cc=0;
    my_count=0;
}

void Parser::GetCh()	//read
{

	if(fc<filecontent.length())
    {
        if((ch=filecontent.at(fc++))=='\n')
        {
            int temp=value.size()-1;
            line_count.push_back(temp);
            ln++;
        }
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
        {
            Error("=",0);
            name="!=";
            sym=Symbol[27];
        }

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
        //char_stack.push_back(ch);
        GetCh();
        if(isalnum(ch) || ch == '_'||ch == '*'||ch == '+'||ch == '-'||ch == '/')
        {
            char_stack.push_back(ch);
            GetCh();
            if(ch=='\'')
            {
                //char_stack.push_back(ch);
                GetCh();
                name = string(char_stack.begin(), char_stack.end());
                sym = Symbol[3];
                char_stack.clear();
            }
            else
            {
                Error("\'",0);
                name = string(char_stack.begin(), char_stack.end());
                sym = Symbol[3];
                char_stack.clear();
            }

        }
        else
        {
            Error("CHAR",0);
        }
    }
    else if(ch=='\"')
    {
        //char_stack.push_back(ch);
        GetCh();
        while(ch==32||ch==33||(ch<=126&&ch>=35))
        {
            char_stack.push_back(ch);
            GetCh();
        }
        if(ch=='\"')
        {
            //char_stack.push_back(ch);
			name = string(char_stack.begin(), char_stack.end());
			sym = Symbol[4];
			char_stack.clear();
			GetCh();
        }
        else
        {
            Error("\"",0);
        }
    }
    else if(ch==EOF)	//读到了文件结尾
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
/*＜程序＞    ::= ［＜常量说明＞］［＜变量说明＞］{＜有返回值函数定义＞|＜无返回值函数定义＞}＜主函数＞*/
void Parser::Grammatical_analysis()
{
    setlocale(LC_ALL, "Chinese-simplified");
    table_count.push_back(my_count);
    if(value.at(cc)=="const")
        const_explain();
        string c=value.at(cc);
    if((value.at(cc)=="int"||value.at(cc)=="char")&&kind.at(cc+1)=="IDENT"&&value.at(cc+2)!="(")
        var_explain();

    while((value.at(cc)=="int"||value.at(cc)=="void"||value.at(cc)=="char")&&kind.at(cc+1)=="IDENT"&&value.at(cc+2)=="(")
        func_define();
    if(value.at(cc)=="void"||value.at(cc+1)=="main")
        main_define();

}

/*＜常量说明＞ ::=  const＜常量定义＞;{ const＜常量定义＞;}*/
void Parser::const_explain()
{

    do
    {
        if(value.at(cc)=="const")
            cc++;
        else
        {
            Error("CONSTsym",0);
        }
        const_define();
        if(value.at(cc)==";")
            cc++;
        else
        {
            Error(";",0);
        }

        //wprintf(L"这是常量声明语句\n");

    }while(value.at(cc)=="const");
}
/*＜变量说明＞  ::= ＜变量定义＞;{＜变量定义＞;}*/
void Parser::var_explain()
{
    while((value.at(cc)=="int"||value.at(cc)=="char")&&kind.at(cc+1)=="IDENT"&&value.at(cc+2)!="(")
    {
        var_define();
        if(value.at(cc)==";")
            cc++;
        else
            Error(";",0);
        //wprintf(L"这是变量声明语句\n");
    }

}
/*＜变量定义＞  ::= ＜类型标识符＞(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’){,(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’) }*/
void Parser::var_define()
{
    string var_name;
    string var_kind;

    if(value.at(cc)=="int"||value.at(cc)=="char")
    {
        var_kind=value.at(cc);
        do
        {
            cc++;
            if(kind.at(cc)=="IDENT")
            {
                var_name=value.at(cc);
                cc++;
                if(value.at(cc)=="[")
                {
                    cc++;
                    int array_num=number();
                    cc++;
                    if(value.at(cc)=="]")
                        cc++;
                    else
                        Error("]",0);

                    symtable.name.push_back(var_name);
                    symtable.func_value.push_back(3);
                    symtable.kind.push_back(var_kind);
                    symtable.feature.push_back(array_num);
                    symtable.formal_or_actual.push_back(0);
                    push_address();
                    my_count++;

                }
                else
                {
                    symtable.name.push_back(var_name);
                    symtable.func_value.push_back(1);
                    symtable.kind.push_back(var_kind);
                    symtable.feature.push_back(NULL);
                    symtable.formal_or_actual.push_back(0);
                    push_address();
                    my_count++;
                }
            }

            else
            {
                Error("IDENT",0);
                while(value.at(cc)!=","&&value.at(cc)!=";")
                    cc++;
            }

        }while(value.at(cc)==",");

    }

}

void Parser::func_define()
{
    if(value.at(cc)=="void")
    {
        cc++;
        func_noreturn();
    }
    else if(value.at(cc)=="char"||value.at(cc)=="int")
    {
        cc++;
        func_return();
    }
}
/*＜无返回值函数定义＞  ::= void＜标识符＞‘(’＜参数＞‘)’‘{’＜复合语句＞‘}’*/
void Parser::func_noreturn()
{
    table_count.push_back(my_count);
    string func_name;
    if(kind.at(cc)=="IDENT")
    {
        func_name=value.at(cc);
        cc++;
    }
    else
        return;
    if(value.at(cc)=="(")
        cc++;
    else
    {
        Error("(",0);
    }
    int parnum=parameter_number();
    symtable.name.push_back(func_name);
    symtable.func_value.push_back(0);
    symtable.kind.push_back("void");
    symtable.feature.push_back(parnum);
    symtable.formal_or_actual.push_back(NULL);
    push_address();
    my_count++;
    if(value.at(cc)==")")
    {
        cc++;
    }
    /*形参插入符号表*/
    else if(value.at(cc)=="char"||value.at(cc)=="int")
    {
        cc--;
        do
        {
            cc++;
            string formal_name;
            string formal_kind;
            if(value.at(cc)=="char"||value.at(cc)=="int")
            {
                formal_kind=value.at(cc);
                cc++;
            }
            else
            {
                Error("CHARsym or INTsym",0);
                while(value.at(cc)!=","&&value.at(cc)!=";"&&value.at(cc)!=")")
                    cc++;
            }
            if(kind.at(cc)=="IDENT")
            {
                formal_name=value.at(cc);
                cc++;
            }
            else
            {
                Error("IDENT",0);
                while(value.at(cc)!=","&&value.at(cc)!=";"&&value.at(cc)!=")")
                    cc++;
            }
            symtable.name.push_back(formal_name);
            symtable.func_value.push_back(1);
            symtable.kind.push_back(formal_kind);
            symtable.feature.push_back(NULL);
            symtable.formal_or_actual.push_back(1);
            push_address();
            my_count++;
        }while(value.at(cc)==",");
    }
    else
    {
        Error(")",0);
    }
    if(value.at(cc)==")")
    {
        cc++;
    }
    else
    {
        Error(")",0);
    }
    if(value.at(cc)=="{")
        cc++;
    else
    {
        Error("{",0);
    }
    //wprintf(L"这是无返回值函数声明语句\n");
    Compound_statement();
    if(value.at(cc)=="}")
        cc++;
    else
        Error("}",0);
}
/*＜有返回值函数定义＞  ::=  ＜声明头部＞‘(’＜参数＞‘)’ ‘{’＜复合语句＞‘}’*/
void Parser::func_return()
{
    table_count.push_back(my_count);
    //to do
    string func_name;
    string func_kind;
    func_kind=value.at(cc-1);
    if(kind.at(cc)=="IDENT")
    {
        func_name=value.at(cc);
        cc++;
    }
    else
        return;
    if(value.at(cc)=="(")
        cc++;
    else
        Error("(",0);
    int parnum=parameter_number();
    symtable.name.push_back(func_name);
    symtable.func_value.push_back(0);
    symtable.kind.push_back(func_kind);
    symtable.feature.push_back(parnum);
    symtable.formal_or_actual.push_back(NULL);
    push_address();
    my_count++;
    if(value.at(cc)==")")
    {
        cc++;
    }
    /*形参插入符号表*/
    else if(value.at(cc)=="char"||value.at(cc)=="int")
    {
        cc--;
        do
        {
            cc++;
            string formal_name;
            string formal_kind;
            if(value.at(cc)=="char"||value.at(cc)=="int")
            {
                formal_kind=value.at(cc);
                cc++;
            }
            else
            {
                Error("CHARsym or INTsym",0);
                while(value.at(cc)!=","&&value.at(cc)!=";"&&value.at(cc)!=")")
                    cc++;
            }
            if(kind.at(cc)=="IDENT")
            {
                formal_name=value.at(cc);
                cc++;
            }
            else
            {
                Error("IDENT",0);
                while(value.at(cc)!=","&&value.at(cc)!=";"&&value.at(cc)!=")")
                    cc++;
            }
            symtable.name.push_back(formal_name);
            symtable.func_value.push_back(1);
            symtable.kind.push_back(formal_kind);
            symtable.feature.push_back(NULL);
            symtable.formal_or_actual.push_back(1);
            push_address();
            my_count++;
        }while(value.at(cc)==",");
    }
    else
        Error(")",0);
    if(value.at(cc)==")")
    {
        cc++;
    }
    else
        Error(")",0);
    if(value.at(cc)=="{")
        cc++;
    else
        Error("{",0);
    //wprintf(L"这是有返回值函数声明语句\n");
    Compound_statement();
    if(value.at(cc)=="}")
        cc++;
    else
        Error("}",0);
}
/*＜常量定义＞   ::=   int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}
                            | char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞}
*/
void Parser::const_define()
{
    string const_name;
    string const_kind;

    if(value.at(cc)=="int")
    {
        int const_value;

        const_kind="int";
        do
        {
            cc++;
            if(kind.at(cc)=="IDENT")
                const_name=value.at(cc);
            else
            {
                Error("IDENT",0);
                while(value.at(cc)!=","&&value.at(cc)!=";")
                    cc++;
                continue;
            }
            cc++;
            if(value.at(cc)=="=")
            {
                cc++;
                const_value=number();

                symtable.name.push_back(const_name);
                symtable.func_value.push_back(2);
                symtable.kind.push_back("int");
                symtable.feature.push_back(const_value);
                symtable.formal_or_actual.push_back(0);
                push_address();
                my_count++;
                cc++;
            }
            else
                Error("=",0);
        }while(value.at(cc)==",");

    }
    else if(value.at(cc)=="char")
    {
        char const_value;

        const_kind="char";
        do
        {
            cc++;
            if(kind.at(cc)=="IDENT")
                const_name=value.at(cc);
            else
            {
                Error("IDENT",0);
                while(value.at(cc)!=","&&value.at(cc)!=";")
                    cc++;
                continue;
            }
            cc++;
            if(value.at(cc)=="=")
            {
                cc++;
                const_value=value.at(cc).c_str()[0];

                symtable.name.push_back(const_name);
                symtable.func_value.push_back(2);
                symtable.kind.push_back("char");
                symtable.feature.push_back(const_value);
                symtable.formal_or_actual.push_back(0);
                push_address();
                my_count++;
                cc++;
            }
            else
                Error("=",0);
        }while(value.at(cc)==",");

    }
    else
        return;
}
/*  ＜整数＞        ::= ［＋｜－］＜无符号整数＞｜０ */
int Parser::number()
{
    int n;
    if(value.at(cc)=="+")
    {
        cc++;
        if(kind.at(cc)=="NUMBER")
        {
            sscanf(value.at(cc).data(),"%d",&n);
            return n;
        }
        else
        {
            Error("NUMBER",0);
            return 0;
        }
    }
    else if(value.at(cc)=="-")
    {
        cc++;
        if(kind.at(cc)=="NUMBER")
        {
            sscanf(value.at(cc).data(),"%d",&n);
            return -n;
        }
        else
        {
            Error("NUMBER",0);
            return 0;
        }
    }
    else if(kind.at(cc)=="NUMBER")
    {
        sscanf(value.at(cc).data(),"%d",&n);
        return n;
    }
    else if(value.at(cc)=="0")
    {
        return 0;
    }
    else
    {
        Error("NUMBER",0);
        return 0;
    }
}

/*＜复合语句＞   ::=  ［＜常量说明＞］［＜变量说明＞］＜语句列＞*/
void Parser::Compound_statement()
{
    if(value.at(cc)=="const")
        const_explain();
        string c=value.at(cc);
    if((value.at(cc)=="int"||value.at(cc)=="char")&&kind.at(cc+1)=="IDENT"&&value.at(cc+2)!="(")
        var_explain();
    Statement_column();
}
/*＜语句列＞   ::=｛＜语句＞｝*/
void Parser::Statement_column()
{
    while(value.at(cc)!="}")
        Statement();
}
/*
＜语句＞    ::= ＜条件语句＞
｜＜循环语句＞
｜‘{’＜语句列＞‘}’
｜＜有返回值函数调用语句＞;
｜＜无返回值函数调用语句＞;
｜＜赋值语句＞;
｜＜读语句＞;
｜＜写语句＞;
｜＜空＞;
｜＜返回语句＞;
 */
void Parser::Statement()
{
    if(value.at(cc)=="if")
        Conditional_Statement();
    else if(value.at(cc)=="do")
        Dowhile_Statement();
    else if(value.at(cc)=="for")
        For_Statement();
    else if(value.at(cc)==";")
    {
        Empty_Statement();
        cc++;
    }
    else if(value.at(cc)=="{")
        Nested_Statement();
    else if(value.at(cc)=="return")
    {
        Return_Statement();
        if(value.at(cc)==";")
            cc++;
        else
            Error(";",0);
    }
    else if(value.at(cc)=="printf")
    {
        Write_Statement();
        if(value.at(cc)==";")
            cc++;
        else
            Error(";",0);
    }
    else if(value.at(cc)=="scanf")
    {
        Read_Statement();
        if(value.at(cc)==";")
            cc++;
        else
            Error(";",0);
    }
    else if(kind.at(cc)=="IDENT")    //赋值语句或者是函数调用
    {
        if(value.at(cc+1)=="["||value.at(cc+1)=="=")
            Assignment();
        else if(value.at(cc+1)=="(")
            Func_call();
        else
            Error("sym error");
        if(value.at(cc)==";")
            cc++;
        else
            Error(";",0);
    }
    else
        Error("error",0);
}
/*＜条件语句＞  ::=  if ‘(’＜条件＞‘)’＜语句＞［else＜语句＞］*/
void Parser::Conditional_Statement()   //条件语句
{
    if(value.at(cc)=="if")
        cc++;
    else
        return;
    if(value.at(cc)=="(")
        cc++;
    else
        Error("(",0);
    Condition();
    if(value.at(cc)==")")
        cc++;
    else
        Error(")",0);
    //wprintf(L"这是if语句\n");
    Statement();
    if(value.at(cc)=="else")
    {
        cc++;
        //wprintf(L"这是else语句\n");
        Statement();
    }
}
/*＜条件＞    ::=  ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞*/
void Parser::Condition()
{
    Expression();
    if(value.at(cc)=="=="||value.at(cc)=="<="||value.at(cc)==">="||value.at(cc)==">"||value.at(cc)=="<"||value.at(cc)=="!=")
    {
        cc++;
        Expression();
    }
}
/*do＜语句＞while ‘(’＜条件＞‘)’*/
void Parser::Dowhile_Statement()       //do while 循环
{
    if(value.at(cc)=="do")
        cc++;
    else
        return;
    //wprintf(L"这是do_while语句\n");
    Statement();
    if(value.at(cc)=="while")
        cc++;
    else
        Error("WHILEsym",0);
    if(value.at(cc)=="(")
        cc++;
    else
        Error("(",0);
    Condition();
    if(value.at(cc)==")")
        cc++;
    else
        Error(")",0);
}
/*for‘(’＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞‘)’＜语句＞*/
void Parser::For_Statement()           //for 循环
{
    if(value.at(cc)=="for")
        cc++;
    else
        return;
    if(value.at(cc)=="(")
        cc++;
    else
        Error("(");
    if(kind.at(cc)=="IDENT")
    {
        //to do
        cc++;
    }
    else
    {
        Error("IDENT",0);
        while(value.at(cc)!=";")
            cc++;
    }
    if(value.at(cc)=="=")
        cc++;
    else
        Error("=",0);
    Expression();
    if(value.at(cc)==";")
        cc++;
    else
        Error(";",0);
    Condition();
    if(value.at(cc)==";")
        cc++;
    else
        Error(";",0);
    if(kind.at(cc)=="IDENT")
    {
        //to do
        cc++;
    }
    else
    {
        Error("IDENT",0);
        while(value.at(cc)!=")")
            cc++;
    }
    if(value.at(cc)=="=")
        cc++;
    else
        Error("=",0);
    if(kind.at(cc)=="IDENT")
    {
        //to do
        cc++;
    }
    else
    {
        Error("IDENT",0);
        while(value.at(cc)!=")")
            cc++;
    }
    if(value.at(cc)=="+"||value.at(cc)=="-")
    {
        //do something
        cc++;
    }
    else
        Error("+ or -");
    if(kind.at(cc)=="NUMBER")
    {
        //TO DO
        cc++;
    }
    else
    {
        Error("NUMBER",0);
    }
    if(value.at(cc)==")")
        cc++;
    else
        Error(")");
    //wprintf(L"这是for语句\n");
    Statement();
}
/*＜空＞;*/
void Parser::Empty_Statement()         //空语句
{
    ;
    //wprintf(L"这是空语句\n");
}
/*‘{’＜语句列＞‘}’*/
void Parser::Nested_Statement()        //{嵌套}
{
    if(value.at(cc)=="{")
        cc++;
    else
        return;
    Statement_column();
    if(value.at(cc)=="}")
        cc++;
    else
        Error("}");
}
/*
＜有返回值函数调用语句＞ ::= ＜标识符＞‘(’＜值参数表＞‘)’
＜无返回值函数调用语句＞ ::= ＜标识符＞‘(’＜值参数表＞‘)’
*/
void Parser::Func_call()               //函数调用
{
    if(kind.at(cc)=="IDENT")
    {
        //to do
        cc++;
    }
    else
        return;
    if(value.at(cc)=="(")
        cc++;
    else
        Error("(");
    {
        cc--;
        do {
            cc++;
            //to do
            Expression();
        } while(value.at(cc)==",");
    }
    if(value.at(cc)==")")
        cc++;
    else
        Error(")",0);
    //wprintf(L"这是函数调用语句\n");
}
/*＜赋值语句＞   ::=  ＜标识符＞＝＜表达式＞|＜标识符＞‘[’＜表达式＞‘]’=＜表达式＞*/
void Parser::Assignment()              //赋值语句
{
    cc++;
    if(value.at(cc)=="=")
    {
        cc++;
        Expression();
    }
    else if(value.at(cc)=="[")
    {
        cc++;
        Expression();
        if(value.at(cc)=="]")
            cc++;
        else
            Error("]",0);
        if(value.at(cc)=="=")
            cc++;
        else
            Error("=",0);
        Expression();
    }
    //wprintf(L"这是赋值语句\n");
}
/*＜表达式＞    ::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}*/
void Parser::Expression()              //表达式
{
    if(value.at(cc)=="+"||value.at(cc)=="-")
    {
        cc++;
        //to do
    }
    cc--;
    do
    {
        cc++;
        Term();
    }while(value.at(cc)=="+"||value.at(cc)=="-");
}
/*＜项＞     ::= ＜因子＞{＜乘法运算符＞＜因子＞}*/
void Parser::Term()                    //项
{
    cc--;
    do
    {
        cc++;
        Factor();
    }while(value.at(cc)=="*"||value.at(cc)=="/");
}
/*＜因子＞    ::= ＜标识符＞｜＜标识符＞‘[’＜表达式＞‘]’｜＜整数＞|＜字符＞｜＜有返回值函数调用语句＞|‘(’＜表达式＞‘)’*/
void Parser::Factor()                  //因子
{
    if(value.at(cc)=="(")
    {
        Expression();
        if(value.at(cc)==")")
            cc++;
        else
            Error(")");
    }
    else if(kind.at(cc)=="IDENT")
    {
        cc++;
        if(value.at(cc)=="[")
        {
            Expression();
            if(value.at(cc)=="]")
                cc++;
            else
                Error("]");
        }
        else if(value.at(cc)=="(")
        {
            cc--;
            Func_call();
        }
        else
            ;
    }
    else if(kind.at(cc)=="CHAR")
    {
        cc++;
        //to do
    }
    else if(value.at(cc)=="+"||value.at(cc)=="-")
    {
        //to do
        cc++;
        if(kind.at(cc)=="NUMBER"||kind.at(cc)=="ZERO")
        {
            cc++;
            //to do
        }
        else
        {
            Error("NUMBER",0);
            return;
        }
    }
    else if(kind.at(cc)=="NUMBER"||kind.at(cc)=="ZERO")
    {
        cc++;
        //to do
    }
    else
        Error("expressn error",0);

}
/*＜写语句＞    ::=  printf‘(’＜字符串＞,＜表达式＞‘)’|printf ‘(’＜字符串＞‘)’|printf ‘(’＜表达式＞‘)’*/
void Parser::Write_Statement()         //写语句
{
    if(value.at(cc)=="printf")
        cc++;
    else
        return;
    if(value.at(cc)=="(")
        cc++;
    else
        Error("(");
    if(kind.at(cc)=="STRING")
    {
        //to do
        cc++;
        if(value.at(cc)==",")
        {
            cc++;
            Expression();
        }
    }
    else
        Expression();
    if(value.at(cc)==")")
        cc++;
    else
        Error(")");
    //wprintf(L"这是printf写语句\n");
}
/*＜读语句＞    ::=  scanf ‘(’＜标识符＞{,＜标识符＞}‘)’*/
void Parser::Read_Statement()          //读语句
{
    if(value.at(cc)=="scanf")
        cc++;
    else
        return;
    if(value.at(cc)=="(")
        cc++;
    else
        Error("(");
    cc--;
    do
    {
        cc++;
        if(kind.at(cc)=="IDENT")
        {
            //to do
            cc++;
        }
        else
        {
            Error("IDENT",0);
            while(value.at(cc)!=","&&value.at(cc)!=")")
                cc++;
        }
    }while(value.at(cc)==",");
    if(value.at(cc)==")")
        cc++;
    else
        Error(")",0);
    //wprintf(L"这是scanf写语句\n");
}
/*＜返回语句＞   ::=  return[‘(’＜表达式＞‘)’]*/
void Parser::Return_Statement()        //返回语句
{
    if(value.at(cc)=="return")
        cc++;
    else
        return;
    if(value.at(cc)=="(")
    {
        cc++;
        Expression();
        if(value.at(cc)==")")
            cc++;
        else
            Error(")",0);
    }
    //wprintf(L"这是return语句\n");
}
/*＜主函数＞    ::= void main‘(’‘)’ ‘{’＜复合语句＞‘}’*/
void Parser::main_define()
{
    if(value.at(cc)=="void")
        cc++;
    else
        return;
    if(value.at(cc)=="main")
        cc++;
    else
        return;
    if(value.at(cc)=="(")
        cc++;
    else
        Error("(",0);
    if(value.at(cc)==")")
        cc++;
    else
        Error(")",0);
    if(value.at(cc)=="{")
        cc++;
    else
        Error("{");
    //wprintf(L"这是main函数声明语句\n");
    Compound_statement();
    if(value.at(cc)=="}")
        cc++;
    else
        Error("}");
}


int Parser::parameter_number()
{
    int par_num=0;
    int temp=cc;
    while(value.at(temp)!=")")
    {
        if(kind.at(temp)=="IDENT")
            par_num++;
        temp++;
    }
    return par_num;
}

void Parser::push_address()
{

}
