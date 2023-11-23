#include "gramaticaBaseVisitor.h"
#include "gramaticaParser.h"
#include<bits/stdc++.h>
using namespace std;
using namespace filesystem;

/* added the Impl at the end of the class to avoid it being .gitignored sorry */
struct folder
{
	string name;
	map<string,folder> hijas;
};

class myvisitor: gramaticaBaseVisitor {
bool exit=false;
public:
	
	any visitProg(gramaticaParser::ProgContext* ctx) {
		return visitChildren(ctx);
	}
	// ls <path>
	any visitLsco(gramaticaParser::LscoContext *ctx)  {
		string dir="ls";
		
		if(ctx->path() != nullptr){
			dir = "ls "+ctx->path()->dir()->getText();
		}
		system(dir.c_str());
		return any();
	}
	// cd <path>
	any visitCdco(gramaticaParser::CdcoContext *ctx)  {
		string dir="";
		
		if(ctx->path() != nullptr){
			dir = ctx->path()->dir()->getText();
			current_path(dir);	
		}
		return any();
	}
	// mkdir <path>
	any visitMkco(gramaticaParser::MkcoContext *ctx)  {
		string path="",  cmnd="";
		if(ctx->path() != nullptr){
			path = ctx->path()->dir()->getText();
		}
		cmnd="mkdir "+ path;
		system(cmnd.c_str());
		return visitChildren(ctx);
	}
	// pwd
	any visitPwco(gramaticaParser::PwcoContext *ctx){
		system("pwd");
		return any();
	}

	any visitEcco(gramaticaParser::EccoContext *ctx)  {
		string msg="";
		if(ctx->STRING()!=nullptr){
			msg=ctx->STRING()->getText();
			string cmd="echo "+msg;
			system(cmd.c_str());
		}
		return visitChildren(ctx);
	}
	any visitExco(gramaticaParser::ExcoContext *ctx)  {
		exit=true;
		return visitChildren(ctx);
	}
	bool getExit(){return exit;}	

};
