#include "types.hpp"
#include <memory>
#include <tuple>

class Expr {
public:
  virtual ~Expr() = default;
};

class DecExpr: public Expr {
    std::string name;
    Token type;

public:
    DecExpr(std::string name, Token type)
    : name(name), type(type) {}
};

class AssignExpr: public Expr {
    std::string name;
    std::optional<Token> type;
    Expr value;

public:
    AssignExpr(std::string name, std::optional<Token> type, Expr value)
    : name(name), type(type), value(value) {}
};

class BinExpr: public Expr {
    Token op;
    Expr lhs, rhs;

public:
    BinExpr(Token op, Expr lhs,
                Expr rhs)
    : op(op), lhs(lhs), rhs(rhs) {}
};

class CallExpr : public Expr {
  std::string callee;
  std::vector<Expr> args;

public:
  CallExpr(std::string callee,
              std::vector<Expr> args)
    : callee(callee), args(args) {}
};


class FuncExpr: public Expr {
  std::string name;
  std::vector<std::tuple<Expr, Token>> args;
  Expr body;

public:
  FuncExpr(std::string name,
                std::vector<std::tuple<Expr, Token>> args, Expr body)
    : name(name), args(args), body(body) {}
};


class IfExpr: public Expr {
    Expr cond;
    Expr body;
    std::optional<Expr> els;

public:
  IfExpr(Expr cond, Expr body, std::optional<Expr> els)
    : cond(cond), body(body), els(els) {}
};
