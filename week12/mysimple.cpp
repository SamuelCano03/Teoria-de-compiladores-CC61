#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <memory>
#include <vector>
#include <iostream>

using namespace llvm;
using namespace std;

int main() {
    // Crear un contexto y un módulo
    auto TheContext = make_unique<LLVMContext>();
    auto TheModule = make_unique<Module>("SumModule", *TheContext);

    // Crear el tipo de función: int sum(int, int)
    vector<Type *> IntParams(2, Type::getInt32Ty(*TheContext));
    FunctionType *SumFuncType = FunctionType::get(Type::getInt32Ty(*TheContext), IntParams, false);

    // Crear la función 'sum'
    Function *SumFunc = Function::Create(SumFuncType, Function::ExternalLinkage, "sum", TheModule.get());

    // Crear un bloque básico dentro de la función
    BasicBlock *EntryBB = BasicBlock::Create(*TheContext, "entry", SumFunc);
    
    // Crear un IRBuilder para construir instrucciones dentro del bloque básico
    IRBuilder<> Builder(EntryBB);

    // Obtener los parámetros de la función
    auto ArgIt = SumFunc->arg_begin();
    Value *Arg1 = &*ArgIt++;
    Value *Arg2 = &*ArgIt;

    // Crear una instrucción de suma
    //Value *SumResult = Builder.CreateAdd(Arg1, Arg2, "ans");

    // Crear una instrucción de retorno
    Builder.CreateRet(Builder.CreateAdd(Arg1, Arg2, "ans"));

    // Verificar la validez del módulo
    //verifyModule(*TheModule, &errs());

    // Imprimir el módulo generado
    TheModule->print(errs(), nullptr);

    return 0;
}
