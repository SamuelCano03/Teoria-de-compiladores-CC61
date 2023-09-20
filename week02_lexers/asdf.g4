parser grammar ExprParser;
options { tokenVocab=ExprLexer; }

program
    : stat EOF
    | func EOF
    ;

stat: ID EQ expr
    | expr 
    ;


expr: ID
    | INT
    | expr MULT expr
    | expr SUM expr
    ;

func : FUNC expr | FUNC stat;

lexer grammar ExprLexer;


//palabras reservadas
FUNC: 'func';
END: 'end';
MOD: 'mod';
LOOP: 'loop';
COND: 'cond';

//operadores
SUM: '+';
MINUS: '-';
MULT: '*';
DIV: '/';
DIVE: '\\';
EXP: '^';

//identificadores: dígitos y letras
ID: [a-zA-Z][a-zA-Z0-9]* ;

//enteros:
INT : [0-9]+ ;

//reales
NUM: [-+]?[0-9]*'.'?[0-9]+([eE][-+]?[0-9]+)?;

//omiter espacios en blanco
WS: [ \t\n\r\f]+ -> skip ;

EQ: '=';