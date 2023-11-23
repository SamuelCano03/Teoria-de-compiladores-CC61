
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

    virtual std::any visitLsco(gramaticaParser::LscoContext *context) = 0;

    virtual std::any visitCdco(gramaticaParser::CdcoContext *context) = 0;

    virtual std::any visitMkco(gramaticaParser::MkcoContext *context) = 0;

    virtual std::any visitEcco(gramaticaParser::EccoContext *context) = 0;

    virtual std::any visitBlank(gramaticaParser::BlankContext *context) = 0;

    virtual std::any visitItem(gramaticaParser::ItemContext *context) = 0;

    virtual std::any visitDir(gramaticaParser::DirContext *context) = 0;

    virtual std::any visitPath(gramaticaParser::PathContext *context) = 0;


};

