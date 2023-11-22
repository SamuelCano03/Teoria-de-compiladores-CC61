grammar gramatica;

prog: command+ ;


command 
        : 'ls' path NEWLINE     #lsco
        | 'cd' path NEWLINE     #cdco
        | 'mkdir' path NEWLINE  #mkco
        | 'echo' STRING NEWLINE #ecco
        | NEWLINE               #blank
        ;


// Regla para la ruta
path: item=(ID | '.' | '..') ('/' path)? ;








/////////////////////////////////////////////////////
//lexer
//////////////////////////////////////////////////////

// Definición de identificador (puedes expandir según necesites)
ID : [a-zA-Z][a-zA-Z0-9]+;

// Definición de cadena de caracteres
STRING : '"' .*? '"';

// Ignorar espacios en blanco y saltos de línea
WS : [ \t]+ -> skip;
NEWLINE: '\r'? '\n' ;

//antlr4 -Dlanguage=Cpp -no-listener -visitor gramatica.g4
//clang++ -std=c++17  -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime  *.cpp