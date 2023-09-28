grammar ArrayInit;

init
	: '{' value (',' value)* '}'
	;

value
	: init
	| INT
	;

INT : [0-9]+ ;
WS  : [ \t\r\n]+ -> skip ;

// recuerda!!
// antlr4 ArrayInit.g4
// javac *.java
// grun ArrayInit init -tokens