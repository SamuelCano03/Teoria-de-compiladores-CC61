#include<bits/stdc++.h>
#include "myvisitor.h"
#include "antlr4-runtime.h"
#include "gramaticaLexer.h"
#include "gramaticaParser.h"
using namespace std;
using namespace antlr4;
/*import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.FileInputStream;
import java.io.InputStream;
*/

int main(int argc, char** argv) {
	// solve(argc, argv);
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
        cout<<"\nSamu@Lenova>>";
	}
    return 0;
}

//clang++ -std=c++17  -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime  *.cpp
//g++ *.cpp -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime