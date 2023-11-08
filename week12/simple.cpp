#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <memory>
#include <vector>
using namespace llvm;
using namespace std;
int main() {
	auto TheContext = make_unique<llvm::LLVMContext>();
    
	auto TheModule = make_unique<Module>("Mi cool jit", *TheContext);
	auto TheBuilder = make_unique<IRBuilder<>>(*TheContext);

	Type *Tys[] = { Type::getInt8PtrTy(*TheContext), Type::getInt32Ty(*TheContext) };
	Function *memset_func = Intrinsic::getDeclaration(TheModule.get(), Intrinsic::memset, Tys);

	auto getchar_func = TheModule->getOrInsertFunction("getchar", IntegerType::getInt32Ty(*TheContext));

	vector<Type*> Doubles(0, Type::getDoubleTy(*TheContext));
	FunctionType *FT = FunctionType::get(Type::getDoubleTy(*TheContext), Doubles, false);

	Function *Func = Function::Create(FT, Function::ExternalLinkage, "func", TheModule.get());

	BasicBlock *BB = BasicBlock::Create(*TheContext, "i * a = 3", Func);
	TheBuilder->SetInsertPoint(BB);
	BasicBlock *cc = BasicBlock::Create(*TheContext, "entry2", memset_func);
	TheBuilder->SetInsertPoint(cc);

	TheModule->print(errs(), nullptr);

	return 0;
}