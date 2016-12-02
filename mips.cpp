#include "mips.h"

void MIPS::Init()
{
    int i=0;
    string name;
    string kind;
    int type;
    int feature;
    int address;
    struct globaldata_term* term;
    //建立全局data
    while(i<table_count.at(1))
    {
        name=symtable.name.at(i);
        kind=symtable.kind.at(i);
        type=symtable.func_value.at(i);
        feature=symtable.feature.at(i);
        address=symtable.address.at(i);

        term=new globaldata_term;
        term->name=name;
        term->kind=kind;
        term->type=type;
        term->value=feature;
        term->str_value="";
        //printf("%s:\t%s\t%d\t%d\t%d\n",term->name.c_str(),term->kind.c_str(),term->type,term->value,address);
        globaldata.push_back(term);
        i++;
    }
    func_count=0;
    stringname_count=0;
    push_sp=0;
    string code="jal main";
    mips_code.push_back(code);
    code="j _end";
    mips_code.push_back(code);
    generate_mips();
    code="_end:";
    mips_code.push_back(code);
    print_globaldata();
    print_asm();
}

void MIPS::generate_mips()
{
    for(int index=0;index<quaterline.size();index++)
    {
        QuaterInstr quater=quaterline.at(index);
        SymbolItem* des=quater.des;
        SymbolItem* src1=quater.src1;
        SymbolItem* src2=quater.src2;
        string code;
        int sp;
        char number[10];
        if(quater.op==SETL)
        {
            code=des->name+" :";
            mips_code.push_back(code);
        }
        else if(quater.op==BEGIN)
        {
            struct function_term* func_term=func_table.at(func_count);
            //保存当前函数各种不同类型参数的地址
            cur_call=func_term->function_call_space;
            cur_quater=func_term->quater_space;
            cur_var=func_term->var_space-func_term->formal_parameters;
            cur_formal=func_term->formal_parameters;
            cur_space=func_term->var_space+func_term->quater_space+func_term->function_call_space+3;
            //栈指针自减
            code="addiu $sp,$sp,-";
            //itoa(cur_space*4, number, 10);
            sprintf(number,"%d",cur_space*4);
            code+=number;
            mips_code.push_back(code);
            //保存$ra
            code="sw  $ra,";
            sp=cur_space-1;
            //itoa(sp*4, number, 10);
            sprintf(number,"%d",sp*4);
            code+=number;
            code+="($sp)";
            mips_code.push_back(code);
            //保存$s7,即保存了栈指针
            code="sw  $s7,";
            sp=cur_space-2;
            //itoa(sp*4, number, 10);
            sprintf(number,"%d",sp*4);
            code+=number;
            code+="($sp)";
            mips_code.push_back(code);
            //这之后使用$s7，不使用$sp
            code="move    $s7,$sp";
            mips_code.push_back(code);
            //copy 形参
            int formal_address_begin=cur_call;
            for(int i=0;i<cur_formal;i++)
            {
                code="lw  $t0,";
                sp=cur_space+i;
                //itoa(sp*4, number, 10);
                sprintf(number,"%d",sp*4);
                code+=number;
                code+="($sp)";
                mips_code.push_back(code);
                code="sw  $t0,";
                sp=formal_address_begin+i;
                //itoa(sp*4, number, 10);
                sprintf(number,"%d",sp*4);
                code+=number;
                code+="($sp)";
                mips_code.push_back(code);
            }

        }
        else if(quater.op==END)
        {
            //恢复$ra
            code="lw  $ra,";
            sp=cur_space-1;
            //itoa(sp*4, number, 10);
            sprintf(number,"%d",sp*4);
            code+=number;
            code+="($sp)";
            mips_code.push_back(code);
            //恢复$s7
            code="lw  $s7,";
            sp=cur_space-2;
            //itoa(sp*4, number, 10);
            sprintf(number,"%d",sp*4);
            code+=number;
            code+="($sp)";
            mips_code.push_back(code);
            //栈指针自加
            code="addiu $sp,$sp,";
            //itoa(cur_space*4, number, 10);
            sprintf(number,"%d",cur_space*4);
            code+=number;
            mips_code.push_back(code);
            //跳转回去
            code="jr  $ra";
            mips_code.push_back(code);
            func_count++;
        }
        else if(quater.op==ADD)
        {
            generate_src(src1,1);
            generate_src(src2,2);
            code="add $t0,$t1,$t2";
            mips_code.push_back(code);
            generate_des(des);
        }
        else if(quater.op==SUB)
        {
            generate_src(src1,1);
            generate_src(src2,2);
            code="sub $t0,$t1,$t2";
            mips_code.push_back(code);
            generate_des(des);
        }
        else if(quater.op==MUL)
        {
            generate_src(src1,1);
            generate_src(src2,2);
            code="mul $t0,$t1,$t2";
            mips_code.push_back(code);
            generate_des(des);
        }
        else if(quater.op==DIV)
        {
            generate_src(src1,1);
            generate_src(src2,2);
            code="div $t0,$t1,$t2";
            mips_code.push_back(code);
            generate_des(des);
        }
        else if(quater.op==NEG)
        {
            generate_src(src1,1);
            code="neg $t0,$t1";
            mips_code.push_back(code);
            generate_des(des);
        }
        else if(quater.op==BGR)// >
        {
            generate_src(src1,1);
            generate_src(src2,2);
            code="bgt $t1,$t2,";
            code+=des->name;
            mips_code.push_back(code);
        }
        else if(quater.op==BGE)// >=
        {
            generate_src(src1,1);
            generate_src(src2,2);
            code="bge $t1,$t2,";
            code+=des->name;
            mips_code.push_back(code);
        }
        else if(quater.op==BLS)// <
        {
            generate_src(src1,1);
            generate_src(src2,2);
            code="blt $t1,$t2,";
            code+=des->name;
            mips_code.push_back(code);
        }
        else if(quater.op==BLE)// <=
        {
            generate_src(src1,1);
            generate_src(src2,2);
            code="ble $t1,$t2,";
            code+=des->name;
            mips_code.push_back(code);
        }
        else if(quater.op==BEQ)// ==
        {
            generate_src(src1,1);
            if(src2==NULL)
            {
                code="li $t2,0";
                mips_code.push_back(code);
            }
            else
                generate_src(src2,2);
            code="beq $t1,$t2,";
            code+=des->name;
            mips_code.push_back(code);
        }
        else if(quater.op==BNE)// !=
        {
            generate_src(src1,1);
            if(src2==NULL)
            {
                code="li $t2,0";
                mips_code.push_back(code);
            }
            else
                generate_src(src2,2);
            code="bne $t1,$t2,";
            code+=des->name;
            mips_code.push_back(code);
        }
        else if(quater.op==ASS)
        {
            generate_src(src1,1);
            code="addiu $t0,$t1,0";
            mips_code.push_back(code);
            generate_des(des);
        }
        else if(quater.op==ASSADD)
        {
            generate_src(src1,1);
            generate_src(src2,2);
                int flag=0;
                int i;
                for(i=table_count.at(func_count+1);i<table_count.at(func_count+2);i++)
                {
                    if(symtable.name.at(i)==des->name)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==1)
                {
                    int temp_address=symtable.address.at(i);
                    int base=cur_call;
                    //取到地址
                    code="addi $t7,$s7,";
                    sp=temp_address+base;
                    //itoa(sp*4, number, 10);
                    sprintf(number,"%d",sp*4);
                    code+=number;
                    mips_code.push_back(code);
                    //加上偏移
                    code="mul $t1,$t1,4";
                    mips_code.push_back(code);
                    code="add $t7,$t7,$t1";
                    mips_code.push_back(code);
                    //存
                    code="sw $t2,($t7)";
                    mips_code.push_back(code);
                }
                else
                {
                    code="la $t7,"+des->name;
                    mips_code.push_back(code);
                    code="mul $t1,$t1,4";
                    mips_code.push_back(code);
                    code="add $t7,$t7,$t1";
                    mips_code.push_back(code);
                    //存
                    code="sw $t2,($t7)";
                    mips_code.push_back(code);
                }
        }
        else if(quater.op==ARRADD)
        {
            generate_src(src2,2);
                int flag=0;
                int i;
                for(i=table_count.at(func_count+1);i<table_count.at(func_count+2);i++)
                {
                    if(symtable.name.at(i)==src1->name)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==1)
                {
                    int temp_address=symtable.address.at(i);
                    int base=cur_call;
                    //取到地址
                    code="addi $t7,$s7,";
                    sp=temp_address+base;
                    //itoa(sp*4, number, 10);
                    sprintf(number,"%d",sp*4);
                    code+=number;
                    mips_code.push_back(code);
                    //加上偏移
                    code="mul $t2,$t2,4";
                    mips_code.push_back(code);
                    code="add $t7,$t7,$t2";
                    mips_code.push_back(code);
                    //lw
                    code="lw $t1,($t7)";
                    mips_code.push_back(code);
                }
                else
                {
                    code="la $t7,"+src1->name;
                    mips_code.push_back(code);
                    code="mul $t2,$t2,4";
                    mips_code.push_back(code);
                    code="add $t7,$t7,$t2";
                    mips_code.push_back(code);
                    //存
                    code="lw $t1,($t7)";
                    mips_code.push_back(code);
                }
            code="addiu $t0,$t1,0";
            mips_code.push_back(code);
            generate_des(des);
        }
        else if(quater.op==JUMP)
        {
            code="j  ";
            code+=des->name;
            mips_code.push_back(code);
        }
        else if(quater.op==READ)
        {
                int flag=0;
                int i;
                for(i=table_count.at(func_count+1);i<table_count.at(func_count+2);i++)
                {
                    if(symtable.name.at(i)==des->name)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==1)
                {
                    if(symtable.kind.at(i)=="int")
                    {
                        code="li $v0,5";
                        mips_code.push_back(code);
                    }
                    else if(symtable.kind.at(i)=="char")
                    {
                        code="li $v0,12";
                        mips_code.push_back(code);
                    }
                }
                else
                {
                    for(i=0;i<table_count.at(1);i++)
                    {
                        if(symtable.name.at(i)==des->name)
                            break;
                    }
                    if(symtable.kind.at(i)=="int")
                    {
                        code="li $v0,5";
                        mips_code.push_back(code);
                    }
                    else if(symtable.kind.at(i)=="char")
                    {
                        code="li $v0,12";
                        mips_code.push_back(code);
                    }
                }
            code="syscall";
            mips_code.push_back(code);
            code="move $t0,$v0";
            mips_code.push_back(code);
            generate_des(des);
        }
        else if(quater.op==WRITE)
        {
            if(des->name.at(0)=='.')
            {
                if(des->type==2)//打印字符串
                {
                    struct globaldata_term* stringterm=new globaldata_term;
                    stringterm->name=new_stringname(&stringname_count);
                    stringterm->type=0;
                    stringterm->value=des->string_value.size();
                    stringterm->str_value=des->string_value;
                    globaldata.push_back(stringterm);
                    code="la $a0,.string";
                    //itoa(stringname_count, number, 10);
                    sprintf(number,"%d",stringname_count);
                    code+=number;
                    mips_code.push_back(code);
                    stringname_count++;
                    code="li $v0,4";
                    mips_code.push_back(code);
                    code="syscall";
                    mips_code.push_back(code);
                }
                else if(des->type==1)//打印常量
                {
                    if(des->kind=="int")
                    {
                        code="li $v0,1";
                        mips_code.push_back(code);
                    }
                    else
                    {
                        code="li $v0,11";
                        mips_code.push_back(code);
                    }
                    code="li $a0,";
                    code+=des->value;
                    mips_code.push_back(code);
                    code="syscall";
                    mips_code.push_back(code);
                }
                else
                {
                    int n=0;
                    n=find_quater(des->name);
                    int quater_base=cur_call+cur_var+cur_formal;
                    code="lw $a0,";
                    sp=n+quater_base;
                    //itoa(sp*4, number, 10);
                    sprintf(number,"%d",sp*4);
                    code+=number;
                    code+="($s7)";
                    mips_code.push_back(code);
                    if(des->kind=="")
                    {
                        code="li $v0,1";
                        mips_code.push_back(code);
                    }
                    else //数组或者是函数调用
                    {
                        if(des->kind.substr(0,6)=="_array")
                        {
                            string array_name=des->kind.substr(6);
                            int flag=0;
                            int i;
                            for(i=table_count.at(func_count+1);i<table_count.at(func_count+2);i++)
                            {
                                if(symtable.name.at(i)==array_name)
                                {
                                    flag=1;
                                    break;
                                }
                            }
                            if(flag==1)
                            {
                                if(symtable.kind.at(i)=="int")
                                {
                                    code="li $v0,1";
                                    mips_code.push_back(code);
                                }
                                else if(symtable.kind.at(i)=="char")
                                {
                                    code="li $v0,11";
                                    mips_code.push_back(code);
                                }
                            }
                            else
                            {
                                for(i=0;i<table_count.at(1);i++)
                                {
                                    if(symtable.name.at(i)==array_name)
                                        break;
                                }
                                if(symtable.kind.at(i)=="int")
                                {
                                    code="li $v0,1";
                                    mips_code.push_back(code);
                                }
                                else if(symtable.kind.at(i)=="char")
                                {
                                    code="li $v0,11";
                                    mips_code.push_back(code);
                                }
                            }
                        }
                        else if(des->kind.substr(0,6)=="_call_")
                        {
                            string func_name=des->kind.substr(6);
                            int flag=0;
                            int i;
                            for(i=1;i<table_count.size()-1;i++)
                            {
                                if(symtable.name.at(table_count.at(i))==func_name)
                                    break;
                            }
                            if(symtable.kind.at(table_count.at(i))=="int")
                            {
                                code="li $v0,1";
                                mips_code.push_back(code);
                            }
                            else if(symtable.kind.at(table_count.at(i))=="char")
                            {
                                code="li $v0,11";
                                mips_code.push_back(code);
                            }
                        }
                    }
                    code="syscall";
                    mips_code.push_back(code);
                }
            }
            else
            {

                int flag=0;
                int i;
                for(i=table_count.at(func_count+1);i<table_count.at(func_count+2);i++)
                {
                    if(symtable.name.at(i)==des->name)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==1)
                {
                    int temp_address=symtable.address.at(i);
                    int base=cur_call;
                    code="lw $a0,";
                    sp=temp_address+base;
                    //itoa(sp*4, number, 10);
                    sprintf(number,"%d",sp*4);
                    code+=number;
                    code+="($s7)";
                    mips_code.push_back(code);
                    if(symtable.kind.at(i)=="int")
                    {
                        code="li $v0,1";
                        mips_code.push_back(code);
                    }
                    else if(symtable.kind.at(i)=="char")
                    {
                        code="li $v0,11";
                        mips_code.push_back(code);
                    }
                }
                else
                {
                    code="la $a0,"+des->name;
                    mips_code.push_back(code);
                    code="lw $a0,($a0)";
                    mips_code.push_back(code);
                    for(i=0;i<table_count.at(1);i++)
                    {
                        if(symtable.name.at(i)==des->name)
                            break;
                    }
                    if(symtable.kind.at(i)=="int")
                    {
                        code="li $v0,1";
                        mips_code.push_back(code);
                    }
                    else if(symtable.kind.at(i)=="char")
                    {
                        code="li $v0,11";
                        mips_code.push_back(code);
                    }
                }
                code="syscall";
                mips_code.push_back(code);
            }
            code="li $a0 10";
            mips_code.push_back(code);
            code="li $v0 11";
            mips_code.push_back(code);
            code="syscall";
            mips_code.push_back(code);
        }
        else if(quater.op==PUSH)
        {
            generate_src(des,1);
            code="sw $t1,";
            //itoa(push_sp*4, number, 10);
            sprintf(number,"%d",push_sp*4);
            code+=number;
            code+="($s7)";
            mips_code.push_back(code);
            push_sp++;
        }
        else if(quater.op==CALL)
        {
            code="jal  ";
            code+=des->name;
            mips_code.push_back(code);
            push_sp=0;
        }
        else if(quater.op==GET_RETURN)
        {
            code="move $t0,$v0";
            mips_code.push_back(code);
            generate_des(des);
            code="move $sp,$s7";
            mips_code.push_back(code);
        }
        else if(quater.op==RETURN)
        {
            generate_src(src1,1);
            code="move $v0,$t1";
            mips_code.push_back(code);
            //恢复$ra
            code="lw  $ra,";
            sp=cur_space-1;
            //itoa(sp*4, number, 10);
            sprintf(number,"%d",sp*4);
            code+=number;
            code+="($sp)";
            mips_code.push_back(code);
            //恢复$s7
            code="lw  $s7,";
            sp=cur_space-2;
            //itoa(sp*4, number, 10);
            sprintf(number,"%d",sp*4);
            code+=number;
            code+="($sp)";
            mips_code.push_back(code);
            //栈指针自加
            code="addiu $sp,$sp,";
            //itoa(cur_space*4, number, 10);
            sprintf(number,"%d",cur_space*4);
            code+=number;
            mips_code.push_back(code);
            //跳转回去
            code="jr  $ra";
            mips_code.push_back(code);
        }
    }
}

void MIPS::generate_src(SymbolItem* temp,int n)
{
    string code;
    int sp;
    char number[10];
    if(n==1)
    {
            if(temp->name.at(0)=='.')
            {
                if(temp->type==1)
                {
                    int value=temp->value;
                    code="li $t1,";
                    //itoa(value, number, 10);
                    sprintf(number,"%d",value);
                    code+=number;
                    mips_code.push_back(code);
                    return;
                }
                int n=0;
                n=find_quater(temp->name);
                int quater_base=cur_call+cur_var+cur_formal;
                code="lw $t1,";
                sp=n+quater_base;
                //itoa(sp*4, number, 10);
                sprintf(number,"%d",sp*4);
                code+=number;
                code+="($s7)";
                mips_code.push_back(code);
            }
            else
            {
                int flag=0;
                int i;
                for(i=table_count.at(func_count+1);i<table_count.at(func_count+2);i++)
                {
                    if(symtable.name.at(i)==temp->name)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==1)
                {
                    int temp_address=symtable.address.at(i);
                    int base=cur_call;
                    code="lw $t1,";
                    sp=temp_address+base;
                    //itoa(sp*4, number, 10);
                    sprintf(number,"%d",sp*4);
                    code+=number;
                    code+="($s7)";
                    mips_code.push_back(code);
                }
                else
                {
                    code="la $t1,"+temp->name;
                    mips_code.push_back(code);
                    code="lw $t1,($t1)";
                    mips_code.push_back(code);
                }
            }
    }
    else if(n==2)
    {
            if(temp->name.at(0)=='.')
            {
                if(temp->type==1)
                {
                    int value=temp->value;
                    code="li $t2,";
                    //itoa(value, number, 10);
                    sprintf(number,"%d",value);
                    code+=number;
                    mips_code.push_back(code);
                    return;
                }
                int n=0;
                n=find_quater(temp->name);
                int quater_base=cur_call+cur_var+cur_formal;
                code="lw $t2,";
                sp=n+quater_base;
                //itoa(sp*4, number, 10);
                sprintf(number,"%d",sp*4);
                code+=number;
                code+="($s7)";
                mips_code.push_back(code);
            }
            else
            {
                int flag=0;
                int i;
                for(i=table_count.at(func_count+1);i<table_count.at(func_count+2);i++)
                {
                    if(symtable.name.at(i)==temp->name)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==1)
                {
                    int temp_address=symtable.address.at(i);
                    int base=cur_call;
                    code="lw $t2,";
                    sp=temp_address+base;
                    //itoa(sp*4, number, 10);
                    sprintf(number,"%d",sp*4);
                    code+=number;
                    code+="($s7)";
                    mips_code.push_back(code);
                }
                else
                {
                    code="la $t2,"+temp->name;
                    mips_code.push_back(code);
                    code="lw $t2,($t2)";
                    mips_code.push_back(code);
                }
            }
    }
}

void MIPS::generate_des(SymbolItem* temp)
{
    string code;
    int sp;
    char number[10];
            if(temp->name.at(0)=='.')
            {
                int n=0;
                n=find_quater(temp->name);
                int quater_base=cur_call+cur_var+cur_formal;
                code="sw $t0,";
                sp=n+quater_base;
                //itoa(sp*4, number, 10);
                sprintf(number,"%d",sp*4);
                code+=number;
                code+="($s7)";
                mips_code.push_back(code);
            }
            else
            {
                int flag=0;
                int i;
                for(i=table_count.at(func_count+1);i<table_count.at(func_count+2);i++)
                {
                    if(symtable.name.at(i)==temp->name)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==1)
                {
                    int temp_address=symtable.address.at(i);
                    int base=cur_call;
                    code="sw $t0,";
                    sp=temp_address+base;
                    //itoa(sp*4, number, 10);
                    sprintf(number,"%d",sp*4);
                    code+=number;
                    code+="($s7)";
                    mips_code.push_back(code);
                }
                else
                {
                    code="la $t7,"+temp->name;
                    mips_code.push_back(code);
                    code="sw $t0,($t7)";
                    mips_code.push_back(code);
                }
            }
}
int MIPS::find_quater(string n)
{
    int num;
    string temp=n.substr(1);
    sscanf(temp.c_str(),"%d",&num);
    return num;
}

void MIPS::print_asm()
{
    FILE *fp;
    fp=fopen("mips_code.asm","wb");
    int i;
    for(i=0;i<mips_code.size();i++)
    {
        fprintf(fp,"%s\n",mips_code.at(i).c_str());
    }
    fclose(fp);
}

string MIPS::new_stringname(int *n)
{
    int c=QuaterInstr::number_wei(*n)+2;
    char *s=(char*)malloc(sizeof(char)*c) ;
    sprintf(s, ".string%d", *n);
    string str(s);
    return str;
}

void MIPS::print_globaldata()
{
    string code;
    char number[10];
    code=".data";
    mips_code.push_back(code);
    for(int i=0;i<globaldata.size();i++)
    {
        code=globaldata.at(i)->name;
        code+=":  ";
        if(globaldata.at(i)->type==0)
        {
            code+=".asciiz  \"";
            code+=globaldata.at(i)->str_value;
            code+="\"";

        }
        else if(globaldata.at(i)->type==3)
        {
            code+=".space  ";
            //itoa(globaldata.at(i)->value*4, number, 10);
            sprintf(number,"%d",globaldata.at(i)->value*4);
            code+=number;

        }
        else if(globaldata.at(i)->type==2)
        {
            if(globaldata.at(i)->kind=="char")
            {
                code+=".word  \'";
                code+=(char)globaldata.at(i)->value;
                code+="\'";
            }
            else
            {
                code+=".word  ";
                int temp=globaldata.at(i)->value;
                //itoa(globaldata.at(i)->value, number, 10);
                sprintf(number,"%d",globaldata.at(i)->value);
                code+=number;
            }
        }
        else
        {
            code+=".word  0";
        }
        mips_code.push_back(code);
    }
}
