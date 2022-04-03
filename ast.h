// Abstract Syntax Tree for Scope
#include "lexer.h"
#include <memory>
#include <vector>

class ExprAST{
    public:
        virtual ~ExprAST(){}
};

// NumberExprAST - Expression class for numeric Literal like "1.0"
class NumberExprAST:public ExprAST{
    double Val;

public:
    NumberExprAST(double Val): Val(Val){}
};

// VariableExprAST - Expression class for referencing a variable like "a"
class VariableExprAst: public ExprAST{
    std::string Name;

public:
    VariableExprAst(const std::string &Name): Name(Name){}
};

// BinaryExprAst - Expression class for a binary operation
class BinaryExprAST: public ExprAST{
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS):Op(op), LHS(std::move(LHS)), RHS(std::move(RHS)){}
};

// CallExprAST - Expression class for function calls
class CallExprAST:public ExprAST{
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;

public:
    CallExprAST(const std::string &Callee, std::vector<std::unique_ptr<ExprAST>> Args):Callee(Callee), Args(std::move(Args)){}
};

// ProtoypeAST - represent function prototypes
// Captures the name, arguments and the number of arguments

class PrototypeAST{
    std::string Name;
    std::vector<std::string> Args;

public:
    PrototypeAST(const std::string &name, std::vector<std::string>Args):Name(name), Args(std::move(Args)) {}
    const std::string &getName() const {return Name;}
};

// FunctionAST - This class represents a function definition
class FunctionAST{
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<ExprAST> Body;

public:
    FunctionAST(std::unique_ptr<PrototypeAST> Proto, std::unique_ptr<ExprAST> Body):Proto(std::move(Proto)), Body(std::move(Body)){}
};