grammar LabeledExpr;

/* Syntax analizer */

prog: stat+ ;
//esas etiquetas con # son para etiquetar, se crearán funciones con sus nombres
stat
	: expr NEWLINE          # printExpr
	| ID '=' expr NEWLINE   # assign
	| NEWLINE               # blank
	;

expr
	: expr op=('*'|'/') expr   # MulDiv
	| expr op=('+'|'-') expr   # AddSub
	| INT                   # Int
	| ID                    # Id
	| '(' expr ')'          # Parens
	;

/* Lexical analizer */

MUL: '*' ;
DIV: '/' ;
ADD: '+' ;
SUB: '-' ;

ID     : [a-zA-Z]+ ;
INT    : [0-9]+ ;
NEWLINE: '\r'? '\n' ;
WS     : [ \t]+ -> skip ;

//recuerda :D
//antlr4 -no-listener -visitor LabeledExpr.g4