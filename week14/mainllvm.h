#ifndef __MAIN_H__
#define __MAIN_H__
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include<string>
#include <memory>
using namespace llvm;
using namespace std;
class MainLLVM{
    public:
        MainLLVM();
        void exec(const string& program);
    private:
        void saveModuleToFile(const string& filename);
        void moduleInit();
        unique_ptr<LLVMContext>context;
        unique_ptr<Module>module;
        unique_ptr<IRBuilder<>>builder;
};

#endif
