#include<bits/stdc++.h>
#include "myvisitor.h"
#include "antlr4-runtime.h"
#include "gramaticaLexer.h"
#include "gramaticaParser.h"
using namespace antlr4;
void printfx() {
    cout << "\033[32m"
         << "                                    .%%%%%                                      \n"
         << "                                 %%%%%%%%%%%%%%%                                \n"
         << "                               %%%%%%%%%%%%%%%%%%%                              \n"
         << "                              &%%%%%%%%%%%%%%%%%%%&                             \n"
         << "                             #%%%%%%%%%%%%%%%%%%%%%,                            \n"
         << "                             ,%%%%%%%%%%%%%%%%%%%%%                             \n"
         << "               %%%%%%%%%%     %%%%%%%%%%%%%%%%%%%%%    ,%%%%%%%%&(              \n"
         << "            %%%%%%%%%%%%%%%%   &%%%%%%%%%%%%%%%%%/  %%%%%%%%%%%%%%%%%           \n"
         << "          %%%%%%%%%%%%%%%%%%%%% (%%%%%%%%%%%%%%%  %%%%%%%%%%%%%%%%%%%%/         \n"
         << "         %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%         \n"
         << "         &%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        \n"
         << "         %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%         \n"
         << "          %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%          \n"
         << "            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%(           \n"
         << "               .%%%%%%&%%&&%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&%%%%%%&               \n"
         << "                         %&%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                        \n"
         << "                     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%.                    \n"
         << "                   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#                  \n"
         << "                  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                 \n"
         << "                 %%%%%%%%%%%%%%%%%%%%%%.%%%%%%%%%%%%%%%%%%%%%%%                 \n"
         << "                 &%%%%%%%%%%%%%%%%%%%%% %#%%%%%%%%%%%%%%%%%%%%%                 \n"
         << "                  &%%%%%%%%%%%%%%%%%%%,,% &%%%%%%%%%%%%%%%%%%%%                 \n"
         << "                   %%%%%%%%%%%%%%%%%&  %&  %%%%%%%%%%%%%%%%%%                   \n"
         << "                     .%%%%%%%%%%%%#   /%%     %%%%%%%%%%%%&                     \n"
         << "                                      %%*                                       \n"
         << "                                     %%%                                        \n"
         << "                                   #%%%                                         \n"
         << "                                  %%%%                                          \n"
         << "                                   /                                            \n"
         << "\033[0m\n\n";
}

void solve(){
	system("clear");
	printfx();
    string line, dir=current_path();
	string lred="\033[1;31m",r="\033[0m";
	string lgre="\033[1;92m";
	string lblu="\033[1;36m";
	string user=getenv("USER");
	string s=lred+user+r+" in "+ lgre+dir+r+lblu+" λ "+r;
    cout<<s;
	// +lgre+" λ "+r+lblu+"->"+r;
	while(true){
		getline(cin,line);
		line=line+"\n";
		ANTLRInputStream input(line);
		gramaticaLexer lexer(&input);
		CommonTokenStream token(&lexer);
		gramaticaParser parser(&token);
		auto tree = parser.prog();
		myvisitor eval;
		eval.visitProg(tree);
		if(eval.getExit())break;
		dir=current_path();
		s=lred+user+r+" in "+ lgre+dir+r+lblu+" λ "+r;
		cout<<s;
	}
}
int main(int argc, char** argv) {
	solve();
	return 0;
}

//clang++ -std=c++17  -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime  *.cpp
//g++ *.cpp -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime