#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <errno.h>
#include <string.h>
#include <fstream>
#include <vector>
#include "Parser.h"

using namespace std;
/* "Parser.cpp" */
extern int correct_flag;
namespace File
{
  void ReadFileToStringOrDie(const char* filename, string* data)
  {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
    {
      perror(filename);
      exit(1);
    }

    data->clear();
    while (!feof(fp))
    {
      char buf[4096];
      size_t ret = fread(buf, 1, 4096, fp);
      if (ret == 0 && ferror(fp))
      {
        perror("fread");
        exit(1);
      }
      data->append(string(buf, ret));
    }

    fclose(fp);
  }

  void ReadFileToStringOrDie(const string& filename, string* data)
  {
    ReadFileToStringOrDie(filename.c_str(), data);
  }

  void WriteStringToFileOrDie(const string& str, const char* filename)
  {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL)
    {
      perror(filename);
      exit(1);
    }

    int ret = fwrite(str.data(), str.size(), 1, fp);
    if (ret != 1)
    {
      perror("fwrite");
      exit(1);
    }

    fclose(fp);
  }

}
extern vector<string> kind;
extern vector<string> value;


int main(int arg , char **argv)
{
    int countnumber=0;
    int num;
    string input_file,instr;
    cout << "Please input the file path:" << endl;
    cin >> input_file;
    char s[20];
    FILE *fp=fopen("Record","wb");

    File::ReadFileToStringOrDie(input_file,&instr);
    Parser parser(instr);
    parser.GetCh();
    while(parser.GetSym()!="EOF")
    {
        parser.GetWord();
        //printf("%d\t",countnumber++);
        kind.push_back(parser.GetSym());
        if(parser.GetSym()=="ZERO"||parser.GetSym()=="NUMBER")
        {
            num=parser.Get_int_Id();
            sprintf(s,"%d\0",num);
            instr=s;
            value.push_back(instr);
            //printf("%s\t%s\n",parser.GetSym().c_str(),instr.c_str());
        }
        else
        {
            instr=parser.Get_str_Id();
            value.push_back(instr);
            //printf("%s\t%s\n",parser.GetSym().c_str(),instr.c_str());
        }
        countnumber++;
    }

    for(num=0;num<countnumber;num++)
        fprintf(fp,"%d\t%s\t%s\n",num,kind.at(num).c_str(),value.at(num).c_str());

    parser.Grammatical_analysis();
    fclose(fp);
    //printf("%d",correct_flag);
    return 0;
}

