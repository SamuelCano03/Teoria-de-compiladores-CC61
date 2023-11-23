#include "gramaticaBaseVisitor.h"
#include "gramaticaParser.h"
#include<bits/stdc++.h>
using namespace std;

/* added the Impl at the end of the class to avoid it being .gitignored sorry */
struct folder
{
	string name;
	map<string,folder> hijas;
};

class myvisitor: gramaticaBaseVisitor {

public:
	/* ID '=' expr NEWLINE */
	any visitProg(gramaticaParser::ProgContext* ctx) {
		return visitChildren(ctx);
	}
	any visitLsco(gramaticaParser::LscoContext *ctx)  {
		string dir="";
		
		if(ctx->path() != nullptr){
			dir = ctx->path()->dir()->getText();
		}
		dir="ls "+dir;
		system(dir.c_str());
		return any();
	}

	any visitCdco(gramaticaParser::CdcoContext *ctx)  {
		return any();
	}

	any visitMkco(gramaticaParser::MkcoContext *ctx)  {
		return visitChildren(ctx);
	}

	any visitEcco(gramaticaParser::EccoContext *ctx)  {
		return visitChildren(ctx);
	}

};
