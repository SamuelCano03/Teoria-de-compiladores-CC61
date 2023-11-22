#include<bits/stdc++.h>

#include "myvisitor.h"
#include "antlr4-runtime.h"
#include "gramaticaLexer.h"
#include "gramaticaParser.h"

/*import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.FileInputStream;
import java.io.InputStream;
*/

int main(int argc, char** argv) {
    std::ifstream inputFile;
    if (argc > 1) {
        inputFile.open(argv[1]);
    }
    antlr4::ANTLRInputStream input(inputFile.is_open() ? inputFile : std::cin);
    gramaticaLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    gramaticaParser parser(&tokens);
    auto tree = parser.prog();
    myvisitor eval;
    eval.visitProg(tree);
    return 0;
}

//clang++ -std=c++17  -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime  *.cpp
//g++ *.cpp -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime