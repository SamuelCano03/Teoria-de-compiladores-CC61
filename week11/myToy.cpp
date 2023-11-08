#include<iostream>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

enum Token{
    tok_eof = -1,
    tok_def = -2, 
    tok_extern = -3,
    tok_identifier = -4,
    tok_number = -5,
};

static string IdentifierStr;
static double NumVal;

static int gettok(){
    static int LastChar = ' ';
    /* La función isspace() es una función que forma parte de la biblioteca estándar de C y C++. Su propósito es determinar si un carácter dado es un espacio en blanco. Los espacios en blanco incluyen caracteres como el espacio en blanco (' '), el tabulador ('\t'), el retorno de carro ('\r'), el avance de línea ('\n'), entre otros caracteres que representan espacio en blanco o formatos de control. */
    while(isspace(LastChar)) LastChar=getchar();

    if(isalpha(LastChar)){
        IdentifierStr = LastChar;
        while(isalnum((LastChar = getchar()))){
            IdentifierStr +=LastChar;
        }
        if(IdentifierStr == "def")return tok_def;
        if(IdentifierStr== "extern")return tok_extern;
        return tok_identifier;
    }
    

    if (isdigit(LastChar) || LastChar=='.'){
        string NumStr;
        do{
            NumStr+=LastChar;
            LastChar=getchar();
        } while(isdigit(LastChar) || LastChar == '.');
        NumVal = strtod(NumStr.c_str(), 0);

        return tok_number;
    }
    
    if(LastChar == '#'){
        do{
            LastChar=getchar();
        }while(LastChar!=EOF && LastChar !='\n' && LastChar!='\r');
        
        if(LastChar!= EOF)return gettok();
    }

    if (LastChar==EOF)return tok_eof;
    int ThisChar = LastChar;
    LastChar=getchar();
    return ThisChar;
}

int main(){
    int tok;
    while((tok=gettok())!=tok_eof){
        cout<<tok<<"-> \n";
    }
}
