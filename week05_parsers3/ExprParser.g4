parser grammar ExprParser;
options { tokenVocab=ExprLexer; }

program
    : lststat EOF
    ;

lststat
    : lststat stat
    |
    ;

stat
    : ID '=' expr
    | expr
    ;

expr
    : expr expr ('+'|'-')
    | NUM
    ;

//source ./../setup.sh
//antlr4 *.g4
//javac *.java
//grun Expr program -tokens //mira que el .g4 se llama ExprParser, pero el comando solo toma Expr
//: D