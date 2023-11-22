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
	map<string, any> memory;
	folder vv={"samu"};
	map<string, folder>susHijas={{"saelc",vv }, {"eduardo", vv}};
	folder cur={"home", susHijas};
	//v.push_back(nuevodirectorio)

public:
	/* ID '=' expr NEWLINE */
	any visitProg(gramaticaParser::ProgContext* ctx) {
		return visitChildren(ctx);
	}
	any visitLsco(gramaticaParser::LscoContext *ctx)  {
		auto mypath=ctx->path();
		string s;
		while(true){
			s=mypath->item->getText();
			mypath=mypath->path();
			cur=cur.hijas[s];
			if(mypath->isEmpty())break;
		}
		/* for(auto e: cur.hijas){
			cout<<e.name<<endl;
		} */
		cout<<"this my fucking funciton\n";
		cout<<s<<endl;
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
