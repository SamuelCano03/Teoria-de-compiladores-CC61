#include<bits/stdc++.h> //profe yo soy de progra competitiva por seeeee a caso
#include "antlr4-runtime.h"
#include "gramaLexer.h"
#include "gramaParser.h"
#include "gramaBaseVisitor.h"
#include "gramaBaseListener.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
using namespace llvm;
using namespace antlr4;
using namespace std;
class MyListener : public gramaBaseVisitor {
    map<string, any> memory;
public:
    any visitAssign(gramaParser::AssignContext *ctx)  {
        // Aquí puedes agregar la lógica para generar código IR con LLVM
        std::string id = ctx->ID()->getText();
		auto value = visit(ctx->expr());
		memory[id] = value;
        cout << "Generando código IR para la regla YourRule\n";
		return value;
    }
    /* expr NEWLINE */
	any visitPrintExpr(gramaParser::PrintExprContext* ctx) {
		auto value = visit(ctx->expr());
		std::cout << std::any_cast<int>(value) << '\n';
		return std::any();
	}

	/* INT */
	std::any visitInt(gramaParser::IntContext* ctx) {
		return std::any(std::stoi(ctx->INT()->getText()));
	}

	/* ID */
	std::any visitId(gramaParser::IdContext* ctx) {
		std::string id = ctx->ID()->getText();
		if (memory.count(id)) return memory[id];
		return std::any();
	}

	/* expr op=('*'|'/') expr */
	std::any visitMulDiv(gramaParser::MulDivContext* ctx) {
		int  left = std::any_cast<int>(visit(ctx->expr(0)));
		int right = std::any_cast<int>(visit(ctx->expr(1)));
		if (ctx->op->getType() == gramaParser::MUL) {
			return left * right;
		} else {
			return  left / right;
		}
		//return std::any(resp);
	}

	/* expr op=('+'|'-') expr */
	std::any visitAddSub(gramaParser::AddSubContext* ctx) {
		auto left = std::any_cast<int>(visit(ctx->expr(0)));
		auto right = std::any_cast<int>(visit(ctx->expr(1)));
		if (ctx->op->getType() == gramaParser::ADD) {
			return left + right;
		} else {
			return left - right;
		}
	}
    /* expr op=('>'|'<') expr */
	std::any visitCmp(gramaParser::AddSubContext* ctx) {
		auto left = std::any_cast<int>(visit(ctx->expr(0)));
		auto right = std::any_cast<int>(visit(ctx->expr(1)));
		if (ctx->op->getType() == gramaParser::CMPMN) {
			return left < right;
		} else {
			return left > right;
		}
	}

	/* '(' expr ')' */
	std::any visitParens(gramaParser::ParensContext* ctx) {
		return visit(ctx->expr());
	}

	std::any visitProg(gramaParser::ProgContext* ctx) {
		return visitChildren(ctx);
	}
};


int main(int argc, char** argv) {
    ifstream inputFile;
    if (argc > 1) {
        inputFile.open(argv[1]);
    }
    antlr4::ANTLRInputStream input(inputFile.is_open() ? inputFile : std::cin);
    gramaLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    gramaParser parser(&tokens);
    auto tree = parser.prog();
    
	LLVMContext context;
	gramaBaseListener listener(context);

    // Imprime el módulo LLVM generado
    tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);



    return 0;
}
    //tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    //tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
//clang++ -std=c++17  -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime  *.cpp
