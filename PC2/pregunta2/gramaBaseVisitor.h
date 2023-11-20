
// Generated from grama.h4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "gramaVisitor.h"


/**
 * This class provides an empty implementation of gramaVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  gramaBaseVisitor : public gramaVisitor {
public:

  virtual std::any visitProg(gramaParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrintExpr(gramaParser::PrintExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssign(gramaParser::AssignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlank(gramaParser::BlankContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulDiv(gramaParser::MulDivContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddSub(gramaParser::AddSubContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParens(gramaParser::ParensContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCmp(gramaParser::CmpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitId(gramaParser::IdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInt(gramaParser::IntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunc(gramaParser::FuncContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgList(gramaParser::ArgListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBodyFunction(gramaParser::BodyFunctionContext *ctx) override {
    return visitChildren(ctx);
  }


};

