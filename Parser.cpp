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
    max_quaterinstr=0;
    quaternum=0;
    labelnum=0;
    address_num=0;
    call_number=0;
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
    //setlocale(LC_ALL, "Chinese-simplified");
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
    table_count.push_back(my_count);

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
                    symtable.address.push_back(address_num);
                    address_num+=array_num;
                    my_count++;

                }
                else
                {
                    symtable.name.push_back(var_name);
                    symtable.func_value.push_back(1);
                    symtable.kind.push_back(var_kind);
                    symtable.feature.push_back(NULL);
                    symtable.formal_or_actual.push_back(0);
                    symtable.address.push_back(address_num);
                    address_num++;
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
    call_number=0;
    address_num=0;
    func_term=new function_term;
    table_count.push_back(my_count);
    string func_name;
    if(kind.at(cc)=="IDENT")
    {
        func_name=value.at(cc);
        cc++;
    }
    else
        return;
    func_term->name=func_name;
    struct SymbolItem* symbolitem=new SymbolItem;
    symbolitem->name=func_name;
    symbolitem->kind="void";
    QuaterInstr quater0(SETL,symbolitem,NULL,NULL);
    quaterline.push_back(quater0);
    QuaterInstr quater1(BEGIN,NULL,NULL,NULL);
    quaterline.push_back(quater1);
    if(value.at(cc)=="(")
        cc++;
    else
    {
        Error("(",0);
    }
    int parnum=parameter_number();
    func_term->formal_parameters=parnum;
    symtable.name.push_back(func_name);
    symtable.func_value.push_back(0);
    symtable.kind.push_back("void");
    symtable.feature.push_back(parnum);
    symtable.formal_or_actual.push_back(0);
    symtable.address.push_back(NULL);
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
            symtable.address.push_back(address_num);
            address_num++;
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
    func_term->var_space=address_num;
    //set the max_quaterinstr
    int index;
    for(int i=0;i<symtable.name.size();i++)
    {
        if(symtable.name.at(i)==func_name&&symtable.func_value.at(i)==0)
        {
            index=i;
            break;
        }
    }
    symtable.formal_or_actual.at(index)=max_quaterinstr;
    func_term->quater_space=max_quaterinstr;
    func_term->function_call_space=call_number;
    max_quaterinstr=0;


    func_table.push_back(func_term);
    if(value.at(cc)=="}")
        cc++;
    else
        Error("}",0);
    QuaterInstr quater2(END,NULL,NULL,NULL);
    quaterline.push_back(quater2);
}
/*＜有返回值函数定义＞  ::=  ＜声明头部＞‘(’＜参数＞‘)’ ‘{’＜复合语句＞‘}’*/
void Parser::func_return()
{
    call_number=0;
    address_num=0;
    func_term=new function_term;
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
    func_term->name=func_name;
    struct SymbolItem* symbolitem=new SymbolItem;
    symbolitem->name=func_name;
    symbolitem->kind=func_kind;
    QuaterInstr quater0(SETL,symbolitem,NULL,NULL);
    quaterline.push_back(quater0);
    QuaterInstr quater1(BEGIN,NULL,NULL,NULL);
    quaterline.push_back(quater1);
    if(value.at(cc)=="(")
        cc++;
    else
        Error("(",0);
    int parnum=parameter_number();
    func_term->formal_parameters=parnum;
    symtable.name.push_back(func_name);
    symtable.func_value.push_back(0);
    symtable.kind.push_back(func_kind);
    symtable.feature.push_back(parnum);
    symtable.formal_or_actual.push_back(NULL);
    symtable.address.push_back(NULL);
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
            symtable.address.push_back(address_num);
            address_num++;
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
    func_term->var_space=address_num;
    if(value.at(cc)=="}")
        cc++;
    else
        Error("}",0);

        //set the max_quaterinstr
        int index;
        for(int i=0;i<symtable.name.size();i++)
        {
            if(symtable.name.at(i)==func_name&&symtable.func_value.at(i)==0)
            {
                index=i;
                break;
            }
        }
        symtable.formal_or_actual.at(index)=max_quaterinstr;
        func_term->quater_space=max_quaterinstr;
        func_term->function_call_space=call_number;
        max_quaterinstr=0;


        func_table.push_back(func_term);


    QuaterInstr quater2(END,NULL,NULL,NULL);
    quaterline.push_back(quater2);
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
                symtable.address.push_back(address_num);
                address_num++;
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
                symtable.address.push_back(address_num);
                address_num++;
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
    if(quaternum>max_quaterinstr)
        max_quaterinstr=quaternum;
    QuaterInstr::clear_QuaterInstr(&quaternum);
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
        //jump label2
        struct SymbolItem* symbolitem=new SymbolItem;
        label2=new_label(&labelnum);
        symbolitem->name=label2;
        QuaterInstr quater0(JUMP,symbolitem,NULL,NULL);
        quaterline.push_back(quater0);

        //set label1
        symbolitem=new SymbolItem;
        symbolitem->name=label1;
        QuaterInstr quater1(SETL,symbolitem,NULL,NULL);
        quaterline.push_back(quater1);


        Statement();
        //set label2
        symbolitem=new SymbolItem;
        symbolitem->name=label2;
        QuaterInstr quater2(SETL,symbolitem,NULL,NULL);
        quaterline.push_back(quater2);
    }
    else{
        struct SymbolItem* symbolitem;
        //set label1
        symbolitem=new SymbolItem;
        symbolitem->name=label1;
        QuaterInstr quater1(SETL,symbolitem,NULL,NULL);
        quaterline.push_back(quater1);
    }
}
/*＜条件＞    ::=  ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞*/
void Parser::Condition()
{
    struct SymbolItem* temp0;
    struct SymbolItem* temp1;

    struct SymbolItem* symbolitem=new SymbolItem;
    label1=new_label(&labelnum);
    symbolitem->name=label1;

    int branch_number;
    temp0=Expression();
    if(value.at(cc)=="=="||value.at(cc)=="<="||value.at(cc)==">="||value.at(cc)==">"||value.at(cc)=="<"||value.at(cc)=="!=")
    {
        if(value.at(cc)=="==")
            branch_number=0;
            else if(value.at(cc)=="<=")
                branch_number=1;
                else if(value.at(cc)==">=")
                    branch_number=2;
                    else if(value.at(cc)==">")
                        branch_number=3;
                        else if(value.at(cc)=="<")
                            branch_number=4;
                            else if(value.at(cc)=="!=")
                                branch_number=5;
        cc++;
        temp1=Expression();
        if(quaternum>max_quaterinstr)
            max_quaterinstr=quaternum;
        QuaterInstr::clear_QuaterInstr(&quaternum);
    }
    if(branch_number==0)
    {
        QuaterInstr quater(BNE,symbolitem,temp0,temp1);
        quaterline.push_back(quater);
    }
    else if(branch_number==1)
    {
        QuaterInstr quater(BGR,symbolitem,temp0,temp1);
        quaterline.push_back(quater);
    }
    else if(branch_number==2)
    {
        QuaterInstr quater(BLS,symbolitem,temp0,temp1);
        quaterline.push_back(quater);
    }
    else if(branch_number==3)
    {
        QuaterInstr quater(BLE,symbolitem,temp0,temp1);
        quaterline.push_back(quater);
    }
    else if(branch_number==4)
    {
        QuaterInstr quater(BGE,symbolitem,temp0,temp1);
        quaterline.push_back(quater);
    }
    else if(branch_number==5)
    {
        QuaterInstr quater(BEQ,symbolitem,temp0,temp1);
        quaterline.push_back(quater);
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
    struct SymbolItem* symbolitem;
    //set label1
    symbolitem=new SymbolItem;
    symbolitem->name=label1;
    QuaterInstr quater1(SETL,symbolitem,NULL,NULL);
    quaterline.push_back(quater1);
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
    struct SymbolItem* temp0=new SymbolItem;
    struct SymbolItem* temp1=new SymbolItem;
    struct SymbolItem* temp2=new SymbolItem;
    int add_or_sub=0;
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
        temp0->name=value.at(cc);
        temp0->type=0;
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
    temp1=Expression();
    if(value.at(cc)==";")
        cc++;
    else
        Error(";",0);
    QuaterInstr quater0(ASS,temp0,temp1,NULL);
    quaterline.push_back(quater0);
    if(quaternum>max_quaterinstr)
        max_quaterinstr=quaternum;
    QuaterInstr::clear_QuaterInstr(&quaternum);
    //set label2
    struct SymbolItem* symbolitem=new SymbolItem;
    label2=new_label(&labelnum);
    symbolitem->name=label2;
    QuaterInstr quater1(SETL,symbolitem,NULL,NULL);
    quaterline.push_back(quater1);

    Condition();
    if(value.at(cc)==";")
        cc++;
    else
        Error(";",0);
    if(kind.at(cc)=="IDENT")
    {
        temp1=new SymbolItem;
        temp1->name=value.at(cc);
        temp1->type=0;
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
        temp2->name=value.at(cc);
        temp2->type=0;
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
        if(value.at(cc)=="-")
          add_or_sub=1;
        cc++;
    }
    else
        Error("+ or -");
    if(kind.at(cc)=="NUMBER")
    {
        symbolitem=new SymbolItem;
        int n;
        sscanf(value.at(cc).c_str(),"%d",&n);
        symbolitem->name=QuaterInstr::new_QuaterInstr(&quaternum);
        symbolitem->kind="int";
        symbolitem->type=1;
        symbolitem->value=n;
        cc++;
    }
    else
    {
        Error("NUMBER",0);
    }
    if(add_or_sub==0)
    {
        QuaterInstr quater2(ADD,temp1,temp2,symbolitem);
        if(value.at(cc)==")")
            cc++;
        else
            Error(")");
        //wprintf(L"这是for语句\n");
        Statement();
        quaterline.push_back(quater2);
    }
    else
    {
        QuaterInstr quater2(SUB,temp1,temp2,symbolitem);
        if(value.at(cc)==")")
            cc++;
        else
            Error(")");
        //wprintf(L"这是for语句\n");
        Statement();
        quaterline.push_back(quater2);
    }
    //jump label2
    symbolitem=new SymbolItem;
    symbolitem->name=label2;
    QuaterInstr quater4(JUMP,symbolitem,NULL,NULL);
    quaterline.push_back(quater4);
    //set label1
    symbolitem=new SymbolItem;
    symbolitem->name=label1;
    QuaterInstr quater3(SETL,symbolitem,NULL,NULL);
    quaterline.push_back(quater3);
    //print_all_quater();
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
struct SymbolItem* Parser::Func_call()               //函数调用
{
    int para=0;
    struct SymbolItem* symbolitem=new SymbolItem;
    if(kind.at(cc)=="IDENT")
    {
        symbolitem->name=value.at(cc);
        cc++;
    }
    else
        return;
    if(value.at(cc)=="(")
        cc++;
    else
        Error("(");
    if(value.at(cc)!=")")
    {
        cc--;
        do {
            struct SymbolItem* temp;
            cc++;
            temp=Expression();
            QuaterInstr quater(PUSH,temp,NULL,NULL);
            quaterline.push_back(quater);
            para++;
        } while(value.at(cc)==",");
    }
    if(value.at(cc)==")")
        cc++;
    else
        Error(")",0);
    if(para>call_number)
        call_number=para;
    QuaterInstr quater1(CALL,symbolitem,NULL,NULL);
    quaterline.push_back(quater1);
    struct SymbolItem* get_return=new SymbolItem;
    get_return->name=QuaterInstr::new_QuaterInstr(&quaternum);
    get_return->kind="_call_";
    get_return->kind+=symbolitem->name;
    get_return->type=0;
    QuaterInstr quater2(GET_RETURN,get_return,NULL,NULL);
    quaterline.push_back(quater2);
    return get_return;
    //wprintf(L"这是函数调用语句\n");
}
/*＜赋值语句＞   ::=  ＜标识符＞＝＜表达式＞|＜标识符＞‘[’＜表达式＞‘]’=＜表达式＞*/
void Parser::Assignment()              //赋值语句
{
    struct SymbolItem* temp0;
    struct SymbolItem* temp1;
    struct SymbolItem* temp2;
    temp0=new SymbolItem;
    temp0->name=value.at(cc);
    temp0->type=0;
    cc++;
    if(value.at(cc)=="=")
    {
        cc++;
        temp1=Expression();
        QuaterInstr quater2(ASS,temp0,temp1,NULL);
        quaterline.push_back(quater2);
    }
    else if(value.at(cc)=="[")
    {
        cc++;
        temp1=Expression();
        if(value.at(cc)=="]")
            cc++;
        else
            Error("]",0);
        if(value.at(cc)=="=")
            cc++;
        else
            Error("=",0);
        temp2=Expression();
        QuaterInstr quater2(ASSADD,temp0,temp1,temp2);
        quaterline.push_back(quater2);
    }
    //wprintf(L"这是赋值语句\n");
}
/*＜表达式＞    ::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}*/
struct SymbolItem* Parser::Expression()              //表达式
{
    int count_term=0,add_or_sub;
    struct SymbolItem* temp0;
    struct SymbolItem* temp1;
    struct SymbolItem* temp2;
    int initflag=0;
    if(value.at(cc)=="+"||value.at(cc)=="-")
    {
        if(value.at(cc)=="-")
            initflag=1;
        cc++;

    }
    cc--;
    do
    {
        if(count_term==0)
        {
            cc++;
            temp0=Term();
            if(initflag==1)
            {
                struct SymbolItem* temp=new SymbolItem;
                temp->name=QuaterInstr::new_QuaterInstr(&quaternum);
                temp->type=0;
                temp->kind="";
                QuaterInstr quater(NEG,temp,temp0,NULL);
                quaterline.push_back(quater);
                temp0=temp;
            }
            count_term++;
            continue;
        }
        if(count_term==1)
        {
            if(value.at(cc)=="+")
                add_or_sub=0;
            else
                add_or_sub=1;
            cc++;
            temp1=Term();
            temp2=new SymbolItem;
            temp2->name=QuaterInstr::new_QuaterInstr(&quaternum);
            temp2->type=0;
            temp2->kind="";
            if(add_or_sub==0)
            {
                QuaterInstr quater(ADD,temp2,temp0,temp1);
                quaterline.push_back(quater);
            }
            else
            {
                QuaterInstr quater(SUB,temp2,temp0,temp1);
                quaterline.push_back(quater);
            }
            temp0=temp2;
        }
    }while(value.at(cc)=="+"||value.at(cc)=="-");
    return temp0;
}
/*＜项＞     ::= ＜因子＞{＜乘法运算符＞＜因子＞}*/
struct SymbolItem* Parser::Term()                    //项
{
    int count_factor=0,mul_or_div;
    struct SymbolItem* temp0;
    struct SymbolItem* temp1;
    struct SymbolItem* temp2;
    cc--;
    do
    {
        if(count_factor==0)
        {
            cc++;
            temp0=Factor();
            count_factor++;
            continue;
        }
        if(count_factor==1)
        {
            if(value.at(cc)=="*")
                mul_or_div=0;
            else
                mul_or_div=1;
            cc++;
            temp1=Factor();
            temp2=new SymbolItem;
            temp2->name=QuaterInstr::new_QuaterInstr(&quaternum);
            temp2->type=0;
            temp2->kind="";
            if(mul_or_div==0)
            {
                QuaterInstr quater(MUL,temp2,temp0,temp1);
                quaterline.push_back(quater);
            }
            else
            {
                QuaterInstr quater(DIV,temp2,temp0,temp1);
                quaterline.push_back(quater);
            }
            temp0=temp2;
        }
    }while(value.at(cc)=="*"||value.at(cc)=="/");
    return temp0;
}
/*＜因子＞    ::= ＜标识符＞｜＜标识符＞‘[’＜表达式＞‘]’｜＜整数＞|＜字符＞｜＜有返回值函数调用语句＞|‘(’＜表达式＞‘)’*/
struct SymbolItem* Parser::Factor()                  //因子
{
    struct SymbolItem* symbolitem=new SymbolItem;
    struct SymbolItem* array;
    if(value.at(cc)=="(")
    {
        cc++;
        symbolitem=Expression();
        if(value.at(cc)==")")
            cc++;
        else
            Error(")");
    }
    else if(kind.at(cc)=="IDENT")
    {
        symbolitem->name=value.at(cc);
        symbolitem->type=0;
        cc++;
        if(value.at(cc)=="[")
        {
            cc++;
            array=Expression();
            if(value.at(cc)=="]")
                cc++;
            else
                Error("]");
            struct SymbolItem* temp=new SymbolItem;
            temp->name=QuaterInstr::new_QuaterInstr(&quaternum);
            temp->type=0;
            temp->kind="_array";
            temp->kind+=symbolitem->name;
            QuaterInstr quater(ARRADD,temp,symbolitem,array);
            quaterline.push_back(quater);
            return temp;
        }
        else if(value.at(cc)=="(")
        {
            cc--;
            symbolitem=Func_call();
            //to do
        }
        else
            ;
    }
    else if(kind.at(cc)=="CHAR")
    {
        symbolitem->name=QuaterInstr::new_QuaterInstr(&quaternum);
        symbolitem->kind="char";
        symbolitem->type=1;
        symbolitem->value=value.at(cc).at(0);
        cc++;
        //to do
    }
    else if(value.at(cc)=="+"||value.at(cc)=="-")
    {
        int flag=0;
        if(value.at(cc)=="-")
            flag=1;
        cc++;
        if(kind.at(cc)=="NUMBER"||kind.at(cc)=="ZERO")
        {
            int n;
            sscanf(value.at(cc).c_str(),"%d",&n);
            symbolitem->name=QuaterInstr::new_QuaterInstr(&quaternum);
            symbolitem->kind="int";
            symbolitem->type=1;
            if(flag==1)
                n=-n;
            symbolitem->value=n;
            cc++;
        }
        else
        {
            Error("NUMBER",0);
            return;
        }
    }
    else if(kind.at(cc)=="NUMBER"||kind.at(cc)=="ZERO")
    {
        int n;
        sscanf(value.at(cc).c_str(),"%d",&n);
        symbolitem->name=QuaterInstr::new_QuaterInstr(&quaternum);
        symbolitem->kind="int";
        symbolitem->type=1;
        symbolitem->value=n;
        cc++;
    }
    else
        Error("expressn error",0);
    return symbolitem;

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
        struct SymbolItem* symbolitem=new SymbolItem;
        symbolitem->name=QuaterInstr::new_QuaterInstr(&quaternum);
        symbolitem->kind="string";
        symbolitem->type=2;
        symbolitem->string_value=value.at(cc);
        QuaterInstr quater(WRITE,symbolitem,NULL,NULL);
        quaterline.push_back(quater);
        cc++;
        if(value.at(cc)==",")
        {
            cc++;
            struct SymbolItem* temp=  Expression();
            QuaterInstr quater2(WRITE,temp,NULL,NULL);
            quaterline.push_back(quater2);
        }
    }
    else
    {
        struct SymbolItem* temp=  Expression();
        QuaterInstr quater2(WRITE,temp,NULL,NULL);
        quaterline.push_back(quater2);
    }
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
            struct SymbolItem* symbolitem=new SymbolItem;
            symbolitem->name=value.at(cc);
            symbolitem->type=0;
            QuaterInstr quater(READ,symbolitem,NULL,NULL);
            quaterline.push_back(quater);
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
    struct SymbolItem* temp;
    if(value.at(cc)=="return")
        cc++;
    else
        return;
    if(value.at(cc)=="(")
    {
        cc++;
        temp=Expression();
        if(value.at(cc)==")")
            cc++;
        else
            Error(")",0);
        QuaterInstr quater(RETURN,NULL,temp,NULL);
        quaterline.push_back(quater);
    }
    //wprintf(L"这是return语句\n");
}
/*＜主函数＞    ::= void main‘(’‘)’ ‘{’＜复合语句＞‘}’*/
void Parser::main_define()
{
    call_number=0;
    address_num=0;
    func_term=new function_term;
    func_term->name="main";
    func_term->formal_parameters=0;
    struct SymbolItem* symbolitem=new SymbolItem;
    symbolitem->name="main";
    symbolitem->kind="void";
    QuaterInstr quater0(SETL,symbolitem,NULL,NULL);
    quaterline.push_back(quater0);
    QuaterInstr quater1(BEGIN,NULL,NULL,NULL);
    quaterline.push_back(quater1);
    table_count.push_back(my_count);
    symtable.name.push_back("main");
    symtable.func_value.push_back(0);
    symtable.kind.push_back("void");
    symtable.feature.push_back(0);
    symtable.formal_or_actual.push_back(NULL);
    symtable.address.push_back(NULL);
    my_count++;
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

    func_term->var_space=address_num;
    //set the max_quaterinstr
    int index;
    for(int i=0;i<symtable.name.size();i++)
    {
        if(symtable.name.at(i)=="main"&&symtable.func_value.at(i)==0)
        {
            index=i;
            break;
        }
    }
    symtable.formal_or_actual.at(index)=max_quaterinstr;
    func_term->quater_space=max_quaterinstr;
    func_term->function_call_space=call_number;
    max_quaterinstr=0;


    func_table.push_back(func_term);


    if(value.at(cc)=="}")
        cc++;
    else
        Error("}");
    QuaterInstr quater2(END,NULL,NULL,NULL);
    quaterline.push_back(quater2);
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

void Parser::print_symtable()
{
    cc=0;
    for(int i=0;i<table_count.size()-1;i++)
    {
        for(int j=0;j<table_count.at(i+1)-table_count.at(i);j++)
        {
             printf("%s\n",symtable.name.at(cc).c_str());
             cc++;
        }
        printf("\n\n\n");
    }
}

void Parser::print_all_quater()
{
    for(int i=0;i<quaterline.size();i++)
        quaterline.at(i).print_quater();
}

string Parser::new_label(int *n)
{
    char *s=(char*)malloc(sizeof(char)*100);
    sprintf(s,"_lable%d",*n);
    string str=s;
    (*n)++;
    return str;
}

void Parser::print_all_func_table()
{
    for(int i=0;i<func_table.size();i++)
    {
        printf("%s:\t%d\t%d\t%d\t%d\n",((func_table.at(i))->name).c_str(),(func_table.at(i))->formal_parameters,(func_table.at(i))->var_space,(func_table.at(i))->quater_space,(func_table.at(i))->function_call_space);
    }
}
