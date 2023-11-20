
// Generated from grama.h4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "gramaParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by gramaParser.
 */
class  gramaVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by gramaParser.
   */
    virtual std::any visitProg(gramaParser::ProgContext *context) = 0;

    virtual std::any visitPrintExpr(gramaParser::PrintExprContext *context) = 0;

    virtual std::any visitAssign(gramaParser::AssignContext *context) = 0;

    virtual std::any visitBlank(gramaParser::BlankContext *context) = 0;

    virtual std::any visitMulDiv(gramaParser::MulDivContext *context) = 0;

    virtual std::any visitAddSub(gramaParser::AddSubContext *context) = 0;

    virtual std::any visitParens(gramaParser::ParensContext *context) = 0;

    virtual std::any visitCmp(gramaParser::CmpContext *context) = 0;

    virtual std::any visitId(gramaParser::IdContext *context) = 0;

    virtual std::any visitInt(gramaParser::IntContext *context) = 0;

    virtual std::any visitFunc(gramaParser::FuncContext *context) = 0;

    virtual std::any visitArgList(gramaParser::ArgListContext *context) = 0;

    virtual std::any visitBodyFunction(gramaParser::BodyFunctionContext *context) = 0;


};

