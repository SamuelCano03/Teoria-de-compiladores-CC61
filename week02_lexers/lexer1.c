//~
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAXLEXEMA 256
#define COMP 256
#define ID 257
#define IF 258
#define ELSE 259
#define NUM 260

struct Handler{
	FILE* file;
	char lexema[MAXLEXEMA];
};

int lex(struct Handler* h) {
	size_t i=0;
	h->lexema[i] = fgetc(h->file);

	
	if(h->lexema[i]=='<'){
		h->lexema[++i]=fgetc(h->file);
		if(h->lexema[i]== '='){
			h->lexema[++i]= '\0';
			return COMP;
		}
		ungetc(h->lexema[i], h->file);
		h->lexema[i]='\0';
		return COMP;
	}
	if(h->lexema[i]=='>'){
		h->lexema[++i]=fgetc(h->file);
		if(h->lexema[i]== '='){
			h->lexema[++i]= '\0';
			return COMP;
		}
		ungetc(h->lexema[i], h->file);
		h->lexema[i]='\0';
		return COMP;
	}
	if(
		(h->lexema[i]>= 'a' && h->lexema[i]<='z')
		||
		(h->lexema[i]>= 'A' && h->lexema[i]<='Z')
		|| h->lexema[i]=='_'
	){
		do{
			h->lexema[++i]=fgetc(h->file);
		}while((h->lexema[i]>= 'a' && h->lexema[i]<='z')
		||
		(h->lexema[i]>= 'A' && h->lexema[i]<='Z')
		|| h->lexema[i]=='_' || 
		(h->lexema[i]>='0' && h->lexema[i]<='9')
		);
		h->lexema[i]='\0';
		ungetc(h->lexema[i], h->file);
		if(strcmp(h->lexema, "if")==0)
			return IF;
		else if (strcmp(h->lexema, "else")==0) 
			return ELSE; 
		else return ID;
	}
	return h->lexema[i]!=EOF?lex(h):EOF;
}

int main(int argc, char*argv[]){
	if(argc<2){
		printf("Usage: %s <sourcefile>\n", argv[0]);
		return -1;
	}
	
	struct Handler* handler = (struct Handler*) malloc(sizeof(struct Handler));
	handler->file=fopen(argv[1],"r");
	int tok;
	while((tok=lex(handler))!=EOF){
		printf("Lexem (%d): %s\n", tok,handler->lexema);
	}
	fclose(handler->file);
	free(handler);
	return 0;
}
/*
//~
<
<=
>
>=
!=
==
*/
//~