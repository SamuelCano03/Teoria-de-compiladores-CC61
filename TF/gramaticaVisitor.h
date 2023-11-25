
// Generated from gramatica.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "gramaticaParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by gramaticaParser.
 */
class  gramaticaVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by gramaticaParser.
   */
    virtual std::any visitProg(gramaticaParser::ProgContext *context) = 0;

    virtual std::any visitIfst(gramaticaParser::IfstContext *context) = 0;

    virtual std::any visitForst(gramaticaParser::ForstContext *context) = 0;

    virtual std::any visitOtherst(gramaticaParser::OtherstContext *context) = 0;

    virtual std::any visitExpr(gramaticaParser::ExprContext *context) = 0;

    virtual std::any visitLsco(gramaticaParser::LscoContext *context) = 0;

    virtual std::any visitCdco(gramaticaParser::CdcoContext *context) = 0;

    virtual std::any visitMkco(gramaticaParser::MkcoContext *context) = 0;

    virtual std::any visitEcco(gramaticaParser::EccoContext *context) = 0;

    virtual std::any visitRmco(gramaticaParser::RmcoContext *context) = 0;

    virtual std::any visitCpco(gramaticaParser::CpcoContext *context) = 0;

    virtual std::any visitMvco(gramaticaParser::MvcoContext *context) = 0;

    virtual std::any visitPwco(gramaticaParser::PwcoContext *context) = 0;

    virtual std::any visitClco(gramaticaParser::ClcoContext *context) = 0;

    virtual std::any visitExco(gramaticaParser::ExcoContext *context) = 0;

    virtual std::any visitBlank(gramaticaParser::BlankContext *context) = 0;

    virtual std::any visitPath(gramaticaParser::PathContext *context) = 0;

    virtual std::any visitItem(gramaticaParser::ItemContext *context) = 0;

    virtual std::any visitVar(gramaticaParser::VarContext *context) = 0;

    virtual std::any visitMsg(gramaticaParser::MsgContext *context) = 0;

    virtual std::any visitFlag(gramaticaParser::FlagContext *context) = 0;


};

