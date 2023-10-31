import sys
from antlr4 import *
from LabeledExprLexer import LabeledExprLexer
from LabeledExprParser import LabeledExprParser
from EvalVisitorImpl import EvalVisitorImpl

def main():
    if len(sys.argv) <= 1:
        return -1
    input_stream = FileStream(sys.argv[1])
    lexer = LabeledExprLexer(input_stream)
    tokens = CommonTokenStream(lexer)
    parser = LabeledExprParser(tokens)
    tree = parser.prog()
    eval = EvalVisitorImpl()
    eval.visitProg(tree)

if __name__ == '__main__':
    main()

