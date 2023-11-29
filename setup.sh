#!/usr/bin/zsh
source $HOME/Documents/Teoria-de-compiladores-CC61/myenv/bin/activate
export COMPILERS=$HOME/Documents/Teoria-de-compiladores-CC61

export CLASSPATH=.:~/.m2/repository/org/antlr/antlr4/4.13.1/antlr4-4.13.1-complete.jar:$CLASSPATH
alias grun='java org.antlr.v4.gui.TestRig'

export ANTLR4I=/home/samuel/MyApps/antlr4-cpp/run/usr/local/include
export ANTLR4L=/home/samuel/MyApps/antlr4-cpp/build/runtime

export LLVM15I=/usr/lib/llvm-15/include
export LLVM15L=/usr/lib/llvm-15/lib