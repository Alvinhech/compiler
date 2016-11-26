#pragma once
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
enum Opcode {
	ADD,
	SUB,
	MUL,
	DIV,
	NEG,
	//calculate instructions.
	//>
	BGR,
	//>=
	BGE,
	//<
	BLS,
	//<=
	BLE,
	//==
	BEQ,
	//!=
	BNE,
	//branch if meeting the conditions.

	// des = src
	ASS,
	// des[src1] = src2
	ASSADD,
	// des = src1[src2]
	ARRADD,


	JUMP,
	SETL,
	READ,
	WRITE,
	PRINTCHAR,
	BEGIN,
	END,

	CALL,
	/*
	as a result of not knowing offset in generating
	quaters.So we can't get the address of the vairable
	or the parameters.So we must generate a push var
	to do this.
	*/
	PUSH,
	GET_RETURN,

	RETURN

};



struct SymbolItem
{
  string name;
  string kind; //int or char or string
  int type;    // 1 represents it's a constant,0 represents variable,2 represents it's a string
  int value;
  string string_value;
};





class QuaterInstr {
	//op des src1 src2
public:
	Opcode op;
	SymbolItem* des;
	SymbolItem* src1;
	SymbolItem* src2;
	string opstr[26]=
    {
        "ADD",
        "SUB",
        "MUL",
        "DIV",
        "NEG",
        //calculate instructions.
        //>
        "BGR",
        //>=
        "BGE",
        //<
        "BLS",
        //<=
        "BLE",
        //==
        "BEQ",
        //<>
        "BNE",
        //branch if meeting the conditions.

        // des = src
        "ASS",
        // des[src1] = src2
        "ASSADD",
        // des = src1[src2]
        "ARRADD",


        "JUMP",
        "SETL",
        "READ",
        "WRITE",
        "PRINTCHAR",
        "BEGIN",
        "END",

        "CALL",
        /*
        as a result of not knowing offset in generating
        quaters.So we can't get the address of the vairable
        or the parameters.So we must generate a push var
        to do this.
        */
        "PUSH",
        "GET_RETURN",

        "RETURN"
    };
public:
    QuaterInstr::QuaterInstr(Opcode _op, SymbolItem* _des, SymbolItem* _src1, SymbolItem* _src2) {
	op = _op;
	des = _des;
	src1 = _src1;
	src2 = _src2;
    }
    static string new_QuaterInstr(int *n)
    {
        int c=number_wei(*n)+2;
        char *s=(char*)malloc(sizeof(char)*c) ;
        sprintf(s, "_%d", *n);
        (*n)++;
        string str(s);
        return str;
    }
    static void clear_QuaterInstr(int *n)
    {
        (*n)=0;
    }
    static int number_wei(int n)
    {
        int i=1;
        while(n/10>0)
        {
            n/=10;
            i++;
        }
        return i;
    }
    void print_quater()
    {
        printf("%s\t",opstr[op].c_str());
        if(des!=NULL)
        {
            if(des->type==0)
                printf("%s",des->name.c_str());
            if(des->type==1)
                printf("%d",des->value);
            if(des->type==2)
                printf("%s",des->string_value.c_str());
        }
        printf(",");
        if(src1!=NULL)
        {
            if(src1->type==0)
                printf("%s",src1->name.c_str());
            if(src1->type==1)
                printf("%d",src1->value);
            if(src1->type==2)
                printf("%s",src1->string_value.c_str());
        }
        printf(",");
        if(src2!=NULL)
        {
            if(src2->type==0)
                printf("%s",src2->name.c_str());
            if(src2->type==1)
                printf("%d",src2->value);
            if(src2->type==2)
                printf("%s",src2->string_value.c_str());
        }
        printf("\n");
    }
};
