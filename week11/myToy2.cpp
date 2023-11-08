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

namespace{
class ExprAST{ //esto lo genera antlr por nosotros, pero aquí lo implementamos de forma más básica
    public: 
        //virtual indica q es un metodo q se va a sobre escribir por la clase hija
        //equivale a una clase abstracta o 'interfaz'
        virtual ~ExprAST() = default; 
}; 
class NumberExprAST: public ExprAST{
    double val;
    public:
        NumberExprAST(double val):val(val){
            //this->val-val; 
            // la diferencia aquí es q val recibe 2 asignaciones (de memoria (0) y luego el de val)
            // por otro lado, val(val) hace una asignación directa
        }
};
class VariableExprAST: public ExprAST{
    string Name;
    public:
        VariableExprAST(const string &Name):Name(Name){

        }
};

class BinaryExprAST: public ExprAST{
    char Op;
    //unique_ptr es un mecanismo para que no tener q destruir un puntero manualmente
    unique_ptr<ExprAST> LHS, RHS;
    public:
        BinaryExprAST(char Op, unique_ptr<ExprAST>LHS, 
            unique_ptr<ExprAST>RHS):Op(Op), LHS(move(LHS)), RHS(move(RHS)){

            }
};

class CallExprAST: public ExprAST{
    string Callee;
    vector<unique_ptr<ExprAST>>Args;
    public:
        CallExprAST(const string &Callee,
        vector<unique_ptr<ExprAST>>Args):Callee(Callee), Args(move(Args)){

        }
};
class PrototypeAST{
    string Name;
    vector<string>Args;
    public:
        PrototypeAST(const string &Name, vector<string>Args):Name(Name),Args(move(Args)){}
        const string &getName()const{return Name;}
};

class FunctionAST{
    unique_ptr<PrototypeAST>Proto;
    unique_ptr<ExprAST>Body;
    public:
        FunctionAST(unique_ptr<PrototypeAST>Proto, unique_ptr<ExprAST>Body):Proto(move(Proto)), Body(move(Body)){}
};

}

static int CurTok;
static int getNextToken(){return CurTok = gettok();}
static map<char,int> BinopPrecedence;
static int GetTokenPrecedence(){
    if(!isascii(CurTok))return -1;
    int TokPrec = BinopPrecedence[CurTok];
    if(TokPrec<=0)return -1;
    return TokPrec;
}
unique_ptr<ExprAST>LogError(const char *Str){
    fprintf(stderr, "Error: %s", Str);
    return nullptr;
}
unique_ptr<PrototypeAST>LogErrorP(const char *Str){
    LogError(Str);
    return nullptr;
}

static unique_ptr<ExprAST>ParseExpression(){}

//numberexpr ::=number
static unique_ptr<ExprAST>PaserNumberExpr(){
    auto Result = make_unique<NumberExprAST>(NumVal);
    getNextToken();
    return move(Result);
}
//parenexpr ::= '(' expression ')'
static unique_ptr<ExprAST> PaserParenExpr(){
    getNextToken();
    auto v = ParseExpression();
    if(!v)return nullptr;
    if(CurTok!=')')return LogError("Expected ')'");
    getNextToken();
    return v;
}

// identifierExpr
//      ::= identifier '(' expression ')'
static unique_ptr<ExprAST>ParseIdentifierExpr(){
    string IdName = IdentifierStr;
    getNextToken();
    if(CurTok!='(')
        return make_unique<VariableExprAST>(IdName);
    getNextToken();
    vector<unique_ptr<ExprAST>>Args;
    if(CurTok!=')'){
        while(true){
            if(auto Arg = ParseExpression())
                Args.push_back(move(Arg));
            else return nullptr;
            if(CurTok==')')break;
            if(CurTok!=',')return LogError("Expected ')' ru ',' in argument list");
            getNextToken();
        }
    }
    getNextToken();
    return make_unique<CallExprAST>(IdName, move(Args));
}


int main(){
    int tok;
    int cnt=0;
    while((tok=gettok())!=tok_eof){
        cout<<cnt<<". ";
        cnt++;
        switch (tok)
        {
        case tok_number:
            cout<<"Number: "<<NumVal<<'\n';
            break;
        case tok_def:
            cout<<"Function: "<<IdentifierStr<<'\n';
            break;
        case tok_extern:
            break;
        case tok_identifier:
            cout<<"String: "<<IdentifierStr<<'\n';
            break;
        default:
            break;
        }
    }
    return 0;
}


/* 
    Manejo de memoria
    - No administrada: lenguajes -> asm, c, c++, ... (usan punteros)

    Es responsabilidad del programador liberar la memoria reservada por los punteros con delete
    esta labor se complica cuando el puntero viaja a funciones.
    o incluso a alguien se le puede olvidar ello
    entonces para evitar eso...
    Apara el conceptop de

    - Memoria administrada: lenguajes -> java, c#, python, js
    estos utilizan el concepto de garbage collector (gc)
    guarda un registro de la memoria asignada 
    si no hay un puntero q esté apuntando una memoria, lo elimina automáticamente.
    Por ello, es menos frecuente un segmentation fault en lenguajes que usen gc

    contras: necesita unidad de procesamiento aparte. hace más pesado los programas

    - Sistema de préstamo/propiedad de memoria
    lenguajes -> Rust
    concepto de ownership de memoria:
    una variable es dueña de una dirección de memoria
    esa variable pertenece a un contexto
    solo una variable puede tener disposición de memoria de una memoria
    en este concepto se puede hacer préstamos de memoria, 
    esperando que se devuelva la propiedad de memoria, en caso de que se libere
*/