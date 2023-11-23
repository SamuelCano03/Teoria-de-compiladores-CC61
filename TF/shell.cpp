#include<bits/stdc++.h>
#include "myvisitor.h"
#include "antlr4-runtime.h"
#include "gramaticaLexer.h"
#include "gramaticaParser.h"
using namespace antlr4;
void solve(){
    string line;
    cout<<"Samu@Lenova>>";
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
		cout<<"\nSamu@Lenova>>";
	}
}
int main(int argc, char** argv) {
	solve();
    return 0;
}

//clang++ -std=c++17  -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime  *.cpp
//g++ *.cpp -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime