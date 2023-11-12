#include<bits/stdc++.h>
/* #include<iostream>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector> */
using namespace std;

static string IdentifierStr;
static double NumVal;
//declaración de dokents
enum Token{
    tok_eof = -1,
    tok_def = -2, 
    tok_extern = -3,
    tok_identifier = -4,
    tok_number = -5,
};
//lectura de tokens nada más ez
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
//    clase derivada        clase base
class NumberExprAST: public ExprAST{
    double val;
    public:
        NumberExprAST(double val):val(val){
            //this->val=val; 
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
        CallExprAST(const string &Callee, vector<unique_ptr<ExprAST>>Args):Callee(Callee), Args(move(Args)){

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
static map<char,int> BinopPrecedence;

static int getNextToken(){return CurTok = gettok();} //this does what you thing it does

//aún no entiendo para chichis es esta de aquí :c //edit: ya entendí, como usa el map bino..ence, entiendo q es para los operadores
static int GetTokenPrecedence(){
    if(!isascii(CurTok))return -1;
    int TokPrec = BinopPrecedence[CurTok];
    if(TokPrec<=0)return -1;
    return TokPrec;
}

//muestra mensajes de error
unique_ptr<ExprAST>LogError(const char *Str){
    //mensaje de error general
    fprintf(stderr, "Error: %s", Str);
    return nullptr;
}
unique_ptr<PrototypeAST>LogErrorP(const char *Str){
    //mensaje de error específico que vamos a invocar con logerror
    LogError(Str);
    return nullptr;
}

//body??
static unique_ptr<ExprAST>ParseExpression();

//numberexpr ::= number // solo se llama cuando sabemos de antemano que el token es un entero
static unique_ptr<ExprAST>ParseNumberExpr(){
    auto Result = make_unique<NumberExprAST>(NumVal);
    getNextToken();
    return move(Result);
}
//parenexpr ::= '(' expression ')' //solo se llama cuando sabemos de antemano que el curToken es un '('
static unique_ptr<ExprAST> ParseParenExpr(){ 
    getNextToken();
    auto v = ParseExpression(); //analiza si después del '(' hay una o más expresiones válidas.
    if(!v)return nullptr;
    if(CurTok!=')')return LogError("Expected ')'");
    getNextToken();
    return v;
}

// identifierExpr
//      ::= identifier
//      ::= identifier '(' (E | expression (',' expression)*) ')'
static unique_ptr<ExprAST>ParseIdentifierExpr(){
    string IdName = IdentifierStr;
    getNextToken();
    if(CurTok!='(')
        return make_unique<VariableExprAST>(IdName);
    getNextToken();
    vector<unique_ptr<ExprAST>>Args;
    if(CurTok!=')'){
        while(true){
            if(unique_ptr<ExprAST> Arg = ParseExpression())//auto
                Args.push_back(move(Arg)); //move hace q pueda mover la dirección de un puntero único a otro puntero único, tal que el primero se elimina para la eficiencia en la memoria
            else return nullptr;
            if(CurTok==')')break;
            if(CurTok!=',')return LogError("Expected ')' or ',' in argument list");
            getNextToken();
        }
    }
    getNextToken();
    return make_unique<CallExprAST>(IdName, move(Args));
}

// primary
//      ::= identifierExpr
//      ::= numberExper
//      ::= parenexpr
static unique_ptr<ExprAST>ParsePrimary(){
    switch (CurTok){
    case tok_identifier:
        return ParseIdentifierExpr();
    case tok_number:
        return ParseNumberExpr();
    case '(':
        return ParseParenExpr();
    default:
        return LogError("Unknown token when expecting an expression");
    }
}
// binopsrhs ::= (op_primary)*
static unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, unique_ptr<ExprAST> LHS){
    while (true){
        int TokPrec = GetTokenPrecedence();

        if (TokPrec < ExprPrec)
            return LHS;

        int BinOp = CurTok;
        getNextToken();

        auto RHS = ParsePrimary();
        if (!RHS)
            return nullptr;

        int NextPrec = GetTokenPrecedence();
        if (TokPrec < NextPrec){
            RHS = ParseBinOpRHS(TokPrec + 1, move(RHS));
            if (!RHS)
                return nullptr;
        }
        LHS = make_unique<BinaryExprAST>(BinOp, move(LHS), move(RHS));
    }
}
// expression ::= primary binoprhs
static unique_ptr<ExprAST> ParseExpression(){
    auto LHS = ParsePrimary();
    if(!LHS)return nullptr;
    return ParseBinOpRHS(0,move(LHS));
}

// protopype ::= id '(' (E|id (',' id)*) ')'
static unique_ptr<PrototypeAST> ParsePrototype() {
    //parseprototype solo es esta parte: 'def fibo(x)'
  if (CurTok != tok_identifier) //if != -4
    return LogErrorP("Expected function name in prototype");

  string FnName = IdentifierStr;
  getNextToken();

  if (CurTok != '(')
    return LogErrorP("Expected '(' in prototype");

  vector<string> ArgNames;
  while (getNextToken() == tok_identifier)
    ArgNames.push_back(IdentifierStr);

  if (CurTok != ')')
    return LogErrorP("Expected ')' in prototype");

  getNextToken();

  return make_unique<PrototypeAST>(FnName, move(ArgNames));
}

//definition ::= 'def' protoype expression
static unique_ptr<FunctionAST> ParseDefinition(){
    getNextToken();
    auto Proto = ParsePrototype();
    if(!Proto) return nullptr;
    if(auto E = ParseExpression())
        return make_unique<FunctionAST>(move(Proto), move(E));
    return nullptr;
}

static unique_ptr<FunctionAST> ParseTopLevelExpression(){
    if(auto E = ParseExpression()){
        auto Proto = make_unique<PrototypeAST>("__anon_expr", vector<string>());
        return make_unique<FunctionAST>(move(Proto),move(E));
    }
    return nullptr;
}

// external ::= prototype
static unique_ptr<PrototypeAST>ParseExtern(){
    getNextToken();
    return ParsePrototype();
}

//initial symbols
static void HandleDefinition(){
    if(ParseDefinition()){
        fprintf(stderr,"Parsed a function defintion.\n");
    }
    else{
        getNextToken();
    }
}
static void HandleExtern(){
    if(ParseExtern()){
        fprintf(stderr, "Parsed a top-level extern.\n");
    }
    else{
        getNextToken();
    }
}
static void HandleTopLevelExpression(){
    if(ParseTopLevelExpression()){
        fprintf(stderr, "Parced top-level expression.\n");
    }
    else{
        getNextToken();
    }
}
// top ::= definition | external | expression | ';'
static void MainLoop(){
    while(true){
        fprintf(stderr, "ready> ");
        switch (CurTok){
            case tok_eof: return;
            case ';': getNextToken(); break;
            case tok_def: HandleDefinition(); break;
            case tok_extern: HandleExtern(); break;
            default: HandleTopLevelExpression(); break;
        }
    }
}
int main(){
    BinopPrecedence['<']=10;
    BinopPrecedence['+']=20;
    BinopPrecedence['-']=20;
    BinopPrecedence['*']=40;
    fprintf(stderr, "ready> ");
    getNextToken();
    MainLoop();
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