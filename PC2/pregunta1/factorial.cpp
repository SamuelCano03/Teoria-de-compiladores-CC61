#include "llvm/ADT/APInt.h"
#include "llvm/IR/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;

static Function *CreateFactorialFunction(Module *M, LLVMContext &Context) {
  FunctionType *FactFTy = FunctionType::get(Type::getInt32Ty(Context), {Type::getInt32Ty(Context)}, false);
  Function *FactF = Function::Create(FactFTy, Function::ExternalLinkage, "factorial", M);

  BasicBlock *BB = BasicBlock::Create(Context, "EntryBlock", FactF);

  Value *One = ConstantInt::get(Type::getInt32Ty(Context), 1);

  Argument *ArgX = &*FactF->arg_begin(); 
  ArgX->setName("AnArg");                

  BasicBlock *RetBB = BasicBlock::Create(Context, "return", FactF);
  BasicBlock *RecurseBB = BasicBlock::Create(Context, "recurse", FactF);

  Value *CondInst = new ICmpInst(*BB, ICmpInst::ICMP_SLE, ArgX, One, "cond");
  BranchInst::Create(RetBB, RecurseBB, CondInst, BB);

  ReturnInst::Create(Context, One, RetBB);

  Value *Sub = BinaryOperator::CreateSub(ArgX, One, "arg", RecurseBB);
  CallInst *CallFactX1 = CallInst::Create(FactF, Sub, "factx1", RecurseBB);
  CallFactX1->setTailCall();

  Value *Mul = BinaryOperator::CreateMul(ArgX, CallFactX1, "mulresult", RecurseBB);

  ReturnInst::Create(Context, Mul, RecurseBB);

  return FactF;
}

int main(int argc, char **argv) {
  int n = argc > 1 ? atol(argv[1]) : 5; 

  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  LLVMContext Context;

  std::unique_ptr<Module> Owner(new Module("test", Context));
  Module *M = Owner.get();

  Function *FactF = CreateFactorialFunction(M, Context);

  std::string errStr;
  ExecutionEngine *EE =
      EngineBuilder(std::move(Owner))
          .setErrorStr(&errStr)
          .create();

  if (!EE) {
    errs() << argv[0] << ": Failed to construct ExecutionEngine: " << errStr << "\n";
    return 1;
  }

  errs() << "verifying... ";
  if (verifyModule(*M)) {
    errs() << argv[0] << ": Error constructing function!\n";
    return 1;
  }

  errs() << "OK\n";
  errs() << "We just constructed this LLVM module:\n\n---------\n" << *M;
  errs() << "---------\nstarting factorial(" << n << ") with JIT...\n";

  std::vector<GenericValue> Args(1);
  Args[0].IntVal = APInt(32, n);
  GenericValue GV = EE->runFunction(FactF, Args);

  outs() << "Result: " << GV.IntVal << "\n";

  return 0;
}

//clang++ factorial.cpp $(llvm-config-15 --cxxflags) -lLLVM-15 