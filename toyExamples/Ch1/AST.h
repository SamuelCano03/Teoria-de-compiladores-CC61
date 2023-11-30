//===- AST.h - Node definition for the Toy AST ----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the AST for the Toy language. It is optimized for
// simplicity, not efficiency. The AST forms a tree structure where each node
// references its children using unique_ptr<>.
//
//===----------------------------------------------------------------------===//

#ifndef AST_H
#define AST_H

#include "Lexer.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Casting.h"
#include <utility>
#include <vector>
#include <optional>
using namespace std;
using namespace llvm;
namespace toy
{

  /// A variable type with shape information.
  struct VarType
  {
    vector<int64_t> shape;
  };

  /// Base class for all expression nodes.
  class ExprAST
  {
  public:
    enum ExprASTKind
    {
      Expr_VarDecl,
      Expr_Return,
      Expr_Num,
      Expr_Literal,
      Expr_Var,
      Expr_BinOp,
      Expr_Call,
      Expr_Print,
    };

    ExprAST(ExprASTKind kind, Location location): kind(kind), location(move(location)) {}
    virtual ~ExprAST() = default;

    ExprASTKind getKind() const { return kind; }

    const Location &loc() { return location; }

  private:
    const ExprASTKind kind;
    Location location;
  };

  /// A block-list of expressions.
  using ExprASTList = vector<unique_ptr<ExprAST>>;

  /// Expression class for numeric literals like "1.0".
  class NumberExprAST : public ExprAST
  {
    double val;

  public:
    NumberExprAST(Location loc, double val)
        : ExprAST(Expr_Num, move(loc)), val(val) {}

    double getValue() { return val; }

    /// LLVM style RTTI
    static bool classof(const ExprAST *c) { return c->getKind() == Expr_Num; }
  };

  /// Expression class for a literal value.
  class LiteralExprAST : public ExprAST
  {
    vector<unique_ptr<ExprAST>> values;
    vector<int64_t> dims;

  public:
    LiteralExprAST(Location loc, vector<unique_ptr<ExprAST>> values,vector<int64_t> dims)
        : ExprAST(Expr_Literal, move(loc)),
          values(move(values)),
          dims(move(dims)) {}

    ArrayRef<unique_ptr<ExprAST>> getValues() { return values; }
    ArrayRef<int64_t> getDims() { return dims; }

    /// LLVM style RTTI
    static bool classof(const ExprAST *c) { return c->getKind() == Expr_Literal; }
  };

  /// Expression class for referencing a variable, like "a".
  class VariableExprAST : public ExprAST
  {
    string name;

  public:
    VariableExprAST(Location loc, StringRef name)
        : ExprAST(Expr_Var, move(loc)), name(name) {}

    StringRef getName() { return name; }

    /// LLVM style RTTI
    static bool classof(const ExprAST *c) { return c->getKind() == Expr_Var; }
  };

  /// Expression class for defining a variable.
  class VarDeclExprAST : public ExprAST
  {
    string name;
    VarType type;
    unique_ptr<ExprAST> initVal;

  public:
    VarDeclExprAST(Location loc, StringRef name, VarType type,unique_ptr<ExprAST> initVal)
        : ExprAST(Expr_VarDecl, move(loc)), name(name),
          type(move(type)), initVal(move(initVal)) {}

    StringRef getName() { return name; }
    ExprAST *getInitVal() { return initVal.get(); }
    const VarType &getType() { return type; }

    /// LLVM style RTTI
    static bool classof(const ExprAST *c) { return c->getKind() == Expr_VarDecl; }
  };

  /// Expression class for a return operator.
  class ReturnExprAST : public ExprAST
  {
    optional<unique_ptr<ExprAST>> expr;

  public:
    ReturnExprAST(Location loc, optional<unique_ptr<ExprAST>> expr)
        : ExprAST(Expr_Return, move(loc)), expr(move(expr)) {}

    optional<ExprAST *> getExpr()
    {
      if (expr.has_value())
        return expr->get();
      return nullopt;
    }

    /// LLVM style RTTI
    static bool classof(const ExprAST *c) { return c->getKind() == Expr_Return; }
  };

  /// Expression class for a binary operator.
  class BinaryExprAST : public ExprAST
  {
    char op;
    unique_ptr<ExprAST> lhs, rhs;

  public:
    char getOp() { return op; }
    ExprAST *getLHS() { return lhs.get(); }
    ExprAST *getRHS() { return rhs.get(); }

    BinaryExprAST(Location loc, char op, unique_ptr<ExprAST> lhs,
                  unique_ptr<ExprAST> rhs)
        : ExprAST(Expr_BinOp, move(loc)), op(op), lhs(move(lhs)),
          rhs(move(rhs)) {}

    /// LLVM style RTTI
    static bool classof(const ExprAST *c) { return c->getKind() == Expr_BinOp; }
  };

  /// Expression class for function calls.
  class CallExprAST : public ExprAST
  {
    string callee;
    vector<unique_ptr<ExprAST>> args;

  public:
    CallExprAST(Location loc, const string &callee,
                vector<unique_ptr<ExprAST>> args)
        : ExprAST(Expr_Call, move(loc)), callee(callee),
          args(move(args)) {}

    StringRef getCallee() { return callee; }
    ArrayRef<unique_ptr<ExprAST>> getArgs() { return args; }

    /// LLVM style RTTI
    static bool classof(const ExprAST *c) { return c->getKind() == Expr_Call; }
  };

  /// Expression class for builtin print calls.
  class PrintExprAST : public ExprAST
  {
    unique_ptr<ExprAST> arg;

  public:
    PrintExprAST(Location loc, unique_ptr<ExprAST> arg)
        : ExprAST(Expr_Print, move(loc)), arg(move(arg)) {}

    ExprAST *getArg() { return arg.get(); }

    /// LLVM style RTTI
    static bool classof(const ExprAST *c) { return c->getKind() == Expr_Print; }
  };

  /// This class represents the "prototype" for a function, which captures its
  /// name, and its argument names (thus implicitly the number of arguments the
  /// function takes).
  class PrototypeAST
  {
    Location location;
    string name;
    vector<unique_ptr<VariableExprAST>> args;

  public:
    PrototypeAST(Location location, const string &name,
                 vector<unique_ptr<VariableExprAST>> args)
        : location(move(location)), name(name), args(move(args)) {}

    const Location &loc() { return location; }
    StringRef getName() const { return name; }
    ArrayRef<unique_ptr<VariableExprAST>> getArgs() { return args; }
  };

  /// This class represents a function definition itself.
  class FunctionAST
  {
    unique_ptr<PrototypeAST> proto;
    unique_ptr<ExprASTList> body;

  public:
    FunctionAST(unique_ptr<PrototypeAST> proto,
                unique_ptr<ExprASTList> body)
        : proto(move(proto)), body(move(body)) {}
    PrototypeAST *getProto() { return proto.get(); }
    ExprASTList *getBody() { return body.get(); }
  };

  /// This class represents a list of functions to be processed together
  class ModuleAST
  {
    vector<FunctionAST> functions;

  public:
    ModuleAST(vector<FunctionAST> functions)
        : functions(move(functions)) {}

    auto begin() { return functions.begin(); }
    auto end() { return functions.end(); }
  };

  void dump(ModuleAST &);

} // namespace toy

#endif // TOY_AST_H
