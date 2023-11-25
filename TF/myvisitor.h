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
		for(auto mylifecontext: ctx->command()){
			auto lsctx=dynamic_cast<gramaticaParser::LscoContext*>(mylifecontext);
			if(lsctx){ 
				visitLsco(lsctx);continue;
			}
			auto mkdirctx=dynamic_cast<gramaticaParser::MkcoContext*>(mylifecontext);
			if(mkdirctx){
				visitMkco(mkdirctx);continue;
			}
			auto cdctx=dynamic_cast<gramaticaParser::CdcoContext*>(mylifecontext);
			if(cdctx){
				visitCdco(cdctx);continue;
			}			
			auto echoctx=dynamic_cast<gramaticaParser::EccoContext*>(mylifecontext);
			if(echoctx){
				visitEcco(echoctx);continue;
			}			
			auto pwdctx=dynamic_cast<gramaticaParser::PwcoContext*>(mylifecontext);
			if(pwdctx){
				visitPwco(pwdctx);continue;
			}
			auto rmctx=dynamic_cast<gramaticaParser::RmcoContext*>(mylifecontext);
			if(rmctx){
				visitRmco(rmctx);continue;
			}
			auto clctx=dynamic_cast<gramaticaParser::ClcoContext*>(mylifecontext);
			if(clctx){
				visitClco(clctx);continue;
			}
			auto exitctx=dynamic_cast<gramaticaParser::ExcoContext*>(mylifecontext);
			if(exitctx){
				visitExco(exitctx);continue;
			}			
		}
		// 
		for(auto statscontext: ctx->stat()){
			auto ifstctx=dynamic_cast<gramaticaParser::IfstContext*>(statscontext);
			if(ifstctx){
				visitIfst(ifstctx);continue;
			}
			auto forstctx=dynamic_cast<gramaticaParser::ForstContext*>(statscontext);
			if(forstctx){
				visitForst(forstctx); continue;
			}
			auto otherstctx=dynamic_cast<gramaticaParser::OtherstContext*>(statscontext);
			if(otherstctx){
				visitOtherst(otherstctx);continue;
			}
		}
		return any();
	}
	any visitStat(gramaticaParser::StatContext *ctx){
		if(ctx!=nullptr){
			string m=ctx->getText();
			system(m.c_str());
		}
		return any();
	}
	// ls <path>
	any visitLsco(gramaticaParser::LscoContext *ctx)  {
		string dir="ls";
		if(ctx->path() != nullptr){
			dir = "ls "+ctx->path()->getText();
		}
		system(dir.c_str());
		return any();
	}
	// cd <path>
	any visitCdco(gramaticaParser::CdcoContext *ctx)  {
		string dir="";
		if(ctx->path() != nullptr){
			for(auto e: ctx->path()->children){
				string tmp=e->getText();
				if(tmp[0]=='$'){
					tmp=getenv(tmp.substr(1,tmp.size()-1).c_str());
				}
				dir=dir+tmp+"/";
			}
			current_path(dir);	
		}
		return any();
	}
	// mkdir <path>
	any visitMkco(gramaticaParser::MkcoContext *ctx)  {
		string path="",  cmnd="";
		if(ctx->path() != nullptr){
			path = ctx->path()->getText();
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
	// echo (msg|var)
	any visitEcco(gramaticaParser::EccoContext *ctx)  {
		string msg="";
		if(ctx->var()!=nullptr){
			msg=ctx->var()->getText();
			msg=msg.substr(1,msg.size()-1);
			msg=getenv(msg.c_str());
		}
		else if(ctx->msg()!=nullptr){
			for(auto e: ctx->msg()->children){
				msg=msg+" "+e->getText();
			}
		}
		string val ="echo "+ msg;
		system(val.c_str());
		return visitChildren(ctx);
	}
	// rm flag? path
	any visitRmco(gramaticaParser::RmcoContext *ctx){
		string dir=" ";
		if(ctx->flag()!=nullptr){
			dir+=ctx->flag()->getText()+ " ";
		}
		if(ctx->path()!=nullptr){
			for(auto e: ctx->path()->children){
				string tmp=e->getText();
				if(tmp[0]=='$'){
					tmp=getenv(tmp.substr(1,tmp.size()-1).c_str());
				}
				dir=dir+tmp+"/"; /////////error
			}
		}
		dir="rm "+dir;
		system(dir.c_str());
		return visitChildren(ctx);
	}
	any visitClco(gramaticaParser::ClcoContext *ctx){
		system("clear");
		return visitChildren(ctx);
	}
	any visitExco(gramaticaParser::ExcoContext *ctx)  {
		exit=true;
		return visitChildren(ctx);
	}

	any visitOtherst(gramaticaParser::OtherstContext *ctx){
		if(ctx->expr()!=nullptr){
			string s=ctx->expr()->getText();
			system(s.c_str());
		}
		return any();
	}

	bool getExit(){return exit;}	

};
