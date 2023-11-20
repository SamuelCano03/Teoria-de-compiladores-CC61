#include<bits/stdc++.h> //profe yo soy de progra competitiva por seeeee a caso
#include "antlr4-runtime.h"
#include "gramaLexer.h"
#include "gramaParser.h"
#include "gramaBaseVisitor.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/LLVMContext.h"
//using namespace llvm;
//using namespace antlr4;
//using namespace std;
class MyListener : public gramaBaseVisitor {
private:
public:
    llvm::LLVMContext &context;
    llvm::Module module;
    llvm::IRBuilder<> builder;
    MyListener(llvm::LLVMContext &ctx) : context(ctx), module("MyModule", ctx), builder(ctx) {}
	void MyUnhappyLife(){

		std::vector<llvm::Type *> IntParams(2, llvm::Type::getInt32Ty(context));
		llvm::FunctionType *SumFuncType = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), IntParams, false);

		llvm::Function *SumFunc = llvm::Function::Create(SumFuncType, llvm::Function::ExternalLinkage, "sum", module);

		llvm::BasicBlock *EntryBB = llvm::BasicBlock::Create(context, "entry", SumFunc);
		
		llvm::IRBuilder<> Builder(EntryBB);

		auto ArgIt = SumFunc->arg_begin();
		llvm::Value *Arg1 = &*ArgIt++;
		llvm::Value *Arg2 = &*ArgIt;

		Builder.CreateRet(Builder.CreateAdd(Arg1, Arg2, "ans"));

		module.print(llvm::errs(), nullptr);
	}
};


int main(int argc, char** argv) {
    std::ifstream inputFile;
    if (argc > 1) {
        inputFile.open(argv[1]);
    }
    antlr4::ANTLRInputStream input(inputFile.is_open() ? inputFile : std::cin);
    gramaLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    gramaParser parser(&tokens);
    auto tree = parser.prog();
    
	llvm::LLVMContext context;
	MyListener listener(context);
    // Imprime el módulo LLVM generado
	listener.MyUnhappyLife();

    return 0;
}
//clang++ -std=c++17 -I $ANTLR4I -L $ANTLR4L -lantlr4-runtime  *.cpp -I/usr/lib/llvm-15/include  -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS  -lLLVM-15