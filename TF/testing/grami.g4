grammar grami;

prog: command* EOF;

command 
        : 'ls' path? NEWLINE            #lsco
        | 'cd' path? NEWLINE            #cdco
        | 'mkdir' path NEWLINE          #mkco
        | 'echo' arg NEWLINE         #ecco
        | 'pwd' NEWLINE                 #pwco
        | 'exit' NEWLINE                #exco
        | NEWLINE                       #blank
        ;

arg: STRING;
// Regla para la ruta
item: ID | '.' | '..';
dir: item ('/' item)*;
path: dir ;

//////////////////////////////////////////////////////
//lexer

// Definición de identificador (puedes expandir según necesites)
ID : [a-zA-Z][a-zA-Z0-9]+;
FOLDER : [a-zA-Z][a-zA-Z0-9_]+;
// Definición de cadena de caracteres
// STRING : '"' (.)*? '"';
STRING : [a-zA-Z0-9]+;

// Ignorar espacios en blanco y saltos de línea
WS : [ \t]+ -> skip;
NEWLINE: '\r'? '\n' ;

//antlr4 -Dlanguage=Cpp -no-listener -visitor gramatica.g4
//clang++ -std=c++17  -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime  *.cpp