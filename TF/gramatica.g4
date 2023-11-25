grammar gramatica;

prog: (command|stat)* EOF;

stat
        : 'if' '[' expr flag expr '];' 'then' command ('else' command)? 'fi' NEWLINE  #ifst
        | 'for' NEWLINE                         #forst
        | expr NEWLINE                        #otherst
        ;
expr
        : expr op=('+'|'-'|'*'|'/') expr
        | expr ('^'|'&'|'|') expr
        | expr '=' expr
        | NUMBER
        | STRING
        ;

command 
        :'ls' flag? path?       NEWLINE #lsco
        | 'cd'      path        NEWLINE #cdco
        | 'mkdir'   path        NEWLINE #mkco
        | 'echo'    (var|msg)   NEWLINE #ecco
        |'rm' flag? path        NEWLINE #rmco
        | 'cp' path path        NEWLINE #cpco
        | 'mv' path path        NEWLINE #mvco
        | 'pwd'                 NEWLINE #pwco
        | 'clear'               NEWLINE #clco
        | 'exit'                NEWLINE #exco
        |                       NEWLINE #blank
        ;

path: item ('/' item '/'?)*;
item: ('$'? STRING) | '.' | '..';
var: '$' STRING;
msg: STRING+;

flag: '-' '-'? STRING;

STRING : [a-zA-Z][a-zA-Z0-9_"'@!%^&.]*;

NUMBER: [0-9]+ ('.' [0-9]+ ( ('e' | 'E') ('+' | '-')? [0-9]+ )?)? ;
INT: [0-9]+;

WS : [ \t]+ -> skip;
NEWLINE: '\r'? '\n' ;





//antlr4 -Dlanguage=Cpp -no-listener -visitor gramatica.g4
//clang++ -std=c++17  -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime  *.cpp