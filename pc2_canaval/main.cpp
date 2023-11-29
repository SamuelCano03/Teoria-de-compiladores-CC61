#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "pcdosLexer.h"
#include "pcdosParser.h"
#include "antlr4-runtime.h"
#include "pcdosVisitorImpl.h"

int main(int argc, char **argv) {
  if (argc <= 1)
    return -1;
  std::ifstream is;
  is.open(argv[1]);
  antlr4::ANTLRInputStream input(is);
  pcdosLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  pcdosParser parser(&tokens);
  auto tree = parser.prog();
	pcdosVisitorImpl eval;
  eval.visitProg(tree);
	eval.test();
	//std::cout << tree->toStringTree(true) << std::endl;
}

//clang++ -std=c++17 -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime  *.cpp -I$LLVM15I  -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS  -lLLVM-15 