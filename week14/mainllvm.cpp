#include "mainllvm.h"

MainLLVM::MainLLVM(){
    moduleInit();
}
void MainLLVM::saveModuleToFile(const string& fileName){
    error_code errorCode;
    raw_fd_stream outLL(fileName, errorCode);
    module->print(outLL, nullptr); //para guardar el archivo 
}

void MainLLVM::moduleInit(){
    context = make_unique<LLVMContext>();
    module = make_unique<Module>("MyExample", *context);
    builder = make_unique<IRBuilder<>>(*context);
}
void MainLLVM::exec(const string& program){
    saveModuleToFile("out.ll");
}
int main(int argc, const char *argv[]){
    string program = R"(
        42
    )";
    MainLLVM vm;
    vm.exec(program);
    return 0;
}
