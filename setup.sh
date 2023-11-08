#!/usr/bin/zsh
source $HOME/Documents/Teoria-de-compiladores-CC61/myenv/bin/activate
export COMPILERS=$HOME/Documents/Teoria-de-compiladores-CC61
export MYAPPS=$HOME/MyApps

export CLASSPATH=.:~/.m2/repository/org/antlr/antlr4/4.13.1/antlr4-4.13.1-complete.jar:$CLASSPATH

alias grun='java org.antlr.v4.gui.TestRig'

export ANTLR4I=/home/samuel/MyApps/antlr4-cpp/run/usr/local/include
export ANTLR4L=/home/samuel/MyApps/antlr4-cpp/build/runtime

export LLVMI=$MYAPPS/llvm-project-16.0.6.src/llvm/include
export MYLLVMTOOLS=$MYAPPS/llvm-project-16.0.6.src/build/bin
