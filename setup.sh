#!/usr/bin/zsh
source $HOME/Documents/Teoria-de-compiladores-CC61/myenv/bin/activate
export CLASSPATH=.:~/.m2/repository/org/antlr/antlr4/4.13.1/antlr4-4.13.1-complete.jar:$CLASSPATH
alias grun='java org.antlr.v4.gui.TestRig'
