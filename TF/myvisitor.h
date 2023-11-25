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
			auto cpctx=dynamic_cast<gramaticaParser::CpcoContext*>(mylifecontext);
			if(cpctx){
				visitCpco(cpctx);continue;
			}
			auto mvctx=dynamic_cast<gramaticaParser::MvcoContext*>(mylifecontext);
			if(mvctx){
				visitMvco(mvctx);continue;
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
	// if
	any visitIfst(gramaticaParser::IfstContext *ctx){
		
	}
	// ls flag? <path>
	any visitLsco(gramaticaParser::LscoContext *ctx)  {
		string dir="ls ";
		if(ctx->flag()!=nullptr){
			dir=dir+ctx->flag()->getText()+" ";
		}
		if(ctx->path() != nullptr){
			dir = dir+ctx->path()->getText();
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
			int dumby = ctx->path()->children.size();
			for(int i=0;i<dumby;i++){
				string tmp = ctx->path()->children[i]->getText();
				if(tmp[0]=='$'){
					tmp=getenv(tmp.substr(1,tmp.size()-1).c_str());
				}
				dir=dir+tmp;
				if(i!=dumby-1)
					dir=dir+"/";
			}
		}
		dir="rm "+dir;
		// cout<<dir<<endl;
		system(dir.c_str());
		return visitChildren(ctx);
	}
	// mv path path
	any visitMvco(gramaticaParser::MvcoContext *ctx){
		auto pa1=ctx->children[1], pa2=ctx->children[2];
		string p1=" ", p2=" ";
		if(pa1!=nullptr){
			int dumby = pa1->children.size();
			for(int i=0;i<dumby;i++){
				string tmp = pa1->children[i]->getText();
				if(tmp[0]=='$'){
					tmp=getenv(tmp.substr(1,tmp.size()-1).c_str());
				}
				p1=p1+tmp;
				if(i!=dumby-1)
					p1=p1+"/";
			}
		}
		if(pa2!=nullptr){
			int dumby = pa2->children.size();
			for(int i=0;i<dumby;i++){
				string tmp = pa2->children[i]->getText();
				if(tmp[0]=='$'){
					tmp=getenv(tmp.substr(1,tmp.size()-1).c_str());
				}
				p2=p2+tmp;
				if(i!=dumby-1)
					p2=p2+"/";
			}
		}
		string msg="mv "+p1+" "+p2;
		system(msg.c_str());
		return any();
	}
	// cp path path
	any visitCpco(gramaticaParser::CpcoContext *ctx){
		auto pa1=ctx->children[1], pa2=ctx->children[2];
		string p1=" ", p2=" ";
		if(pa1!=nullptr){
			int dumby = pa1->children.size();
			for(int i=0;i<dumby;i++){
				string tmp = pa1->children[i]->getText();
				if(tmp[0]=='$'){
					tmp=getenv(tmp.substr(1,tmp.size()-1).c_str());
				}
				p1=p1+tmp;
				if(i!=dumby-1)
					p1=p1+"/";
			}
		}
		if(pa2!=nullptr){
			int dumby = pa2->children.size();
			for(int i=0;i<dumby;i++){
				string tmp = pa2->children[i]->getText();
				if(tmp[0]=='$'){
					tmp=getenv(tmp.substr(1,tmp.size()-1).c_str());
				}
				p2=p2+tmp;
				if(i!=dumby-1)
					p2=p2+"/";
			}
		}
		string msg="cp "+p1+" "+p2;
		system(msg.c_str());
		return any();
	}
	any visitClco(gramaticaParser::ClcoContext *ctx){
		system("clear");
		return any();
	}
	any visitExco(gramaticaParser::ExcoContext *ctx)  {
		exit=true;
		return any();
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
