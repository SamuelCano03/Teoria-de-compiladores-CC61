#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <vector>
#include <iostream>

#define mu make_unique

using namespace llvm;
using namespace std;

int main() {
    unique_ptr<LLVMContext> ctx = mu<LLVMContext>();

    auto modu = mu<Module>("FibonacciModule", *ctx);

    // Crear el tipo de función: int fibonacci(int)
    vector<Type *> IntParam(1, Type::getInt32Ty(*ctx));
    FunctionType *FibFuncType = FunctionType::get(Type::getInt32Ty(*ctx), IntParam, false);

    // Crear la función 'fibonacci'
    Function *FibFunc = Function::Create(FibFuncType, Function::ExternalLinkage, "fibonacci", modu.get());

    // Crear un bloque básico dentro de la función
    BasicBlock *EntryBB = BasicBlock::Create(*ctx, "entry", FibFunc);

    // Crear un IRBuilder para construir instrucciones dentro del bloque básico
    IRBuilder<> Builder(EntryBB);

    // Obtener el parámetro de la función
    auto ArgIt = FibFunc->arg_begin();
    Value *N = &*ArgIt;

    // Crear instrucciones para la secuencia de Fibonacci
    Value *Result;
    if (N->getType() == Type::getInt32Ty(*ctx)) {
        // Base case: if N is 0 or 1, return N
        Result = Builder.CreateSelect(Builder.CreateICmpULT(N, Builder.getInt32(2)), N,
                                      Builder.CreateAdd(Builder.CreateCall(FibFunc, {Builder.CreateSub(N, Builder.getInt32(1))}), 
                                                        Builder.CreateCall(FibFunc, {Builder.CreateSub(N, Builder.getInt32(2))})));
    } else {
        // Handle other types if needed
        Result = Builder.getInt32(0);  // Placeholder for unsupported types
    }

    Builder.CreateRet(Result);

    // Llamar a la función con el argumento 3
    Function *MainFunc = llvm::cast<Function *>(modu->getOrInsertFunction("main", Type::getInt32Ty(*ctx)));
    BasicBlock *MainBB = BasicBlock::Create(*ctx, "entry", MainFunc);
    Builder.SetInsertPoint(MainBB);

    Value *Three = Builder.getInt32(3);
    Value *FibResult = Builder.CreateCall(FibFunc, {Three});
    Builder.CreateRet(FibResult);

    // Imprimir el módulo generado
    modu->print(errs(), nullptr);

    return 0;
}
