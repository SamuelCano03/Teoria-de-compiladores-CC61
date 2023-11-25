
// Generated from gramatica.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "gramaticaVisitor.h"


/**
 * This class provides an empty implementation of gramaticaVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  gramaticaBaseVisitor : public gramaticaVisitor {
public:

  virtual std::any visitProg(gramaticaParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfst(gramaticaParser::IfstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForst(gramaticaParser::ForstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOtherst(gramaticaParser::OtherstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(gramaticaParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLsco(gramaticaParser::LscoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCdco(gramaticaParser::CdcoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMkco(gramaticaParser::MkcoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEcco(gramaticaParser::EccoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRmco(gramaticaParser::RmcoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCpco(gramaticaParser::CpcoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMvco(gramaticaParser::MvcoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPwco(gramaticaParser::PwcoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClco(gramaticaParser::ClcoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExco(gramaticaParser::ExcoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlank(gramaticaParser::BlankContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPath(gramaticaParser::PathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem(gramaticaParser::ItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVar(gramaticaParser::VarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMsg(gramaticaParser::MsgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlag(gramaticaParser::FlagContext *ctx) override {
    return visitChildren(ctx);
  }


};

