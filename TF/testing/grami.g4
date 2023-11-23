grammar grami;
@lexer::header{
    import java.util.*;
}
@lexer::members {
  boolean esPalabraReservada(String palabra) {
    return (palabra.contains("echo"));
  }
}

prog: command+ ;


command 
        : 'ls' path? NEWLINE            #lsco
        | 'cd' path? NEWLINE            #cdco
        | 'mkdir' path NEWLINE          #mkco
        | 'echo' STRING NEWLINE         #ecco
        | 'pwd' NEWLINE                 #pwco
        | 'exit' NEWLINE                #exco
        | NEWLINE                       #blank
        ;


// Regla para la ruta
item: ID | '.' | '..' { imprimir(item.getText()); } ;
dir: item ('/' item)*;
path: dir ;



//////////////////////////////////////////////////////
//lexer

// Definición de identificador (puedes expandir según necesites)
ID : [a-zA-Z][a-zA-Z0-9]+;
FOLDER : [a-zA-Z][a-zA-Z0-9_]+;
// Definición de cadena de caracteres
// STRING : '"' (.)*? '"';
STRING : ~[\r\n]+ {esPalabraReservada(getText());};

// Ignorar espacios en blanco y saltos de línea
WS : [ \t]+ -> skip;
NEWLINE: '\r'? '\n' ;

//antlr4 -Dlanguage=Cpp -no-listener -visitor gramatica.g4
//clang++ -std=c++17  -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime  *.cpp

// Acción semántica para verificar palabra reservada

//antlr4  grami.g4
//javac *.java
//java grami

