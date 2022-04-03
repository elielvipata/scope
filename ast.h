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

// PARSER

// auto LHS = std::make_unique<VariableExprAst>("x");
// auto RHS = std::make_unique<VariableExprAst>("y");
// auto Result = std::make_unique<BinaryExprAST>('+', std::move(LHS), std::move(RHS));


// CurTok/getNextToken - provide a simple token buffer. CutTok is the current token the parser is looking at.
// getNextToken reads another token from the lexer and updates CurTok with its results

static int CurTok;
static int getNextToken(){
    return CurTok = gettok();
}

// Log Error- helper functions for error handling
std::unique_ptr<ExprAST> LogError(const char * Str){
    fprintf(stderr, "LogError:%s\n", Str);
    return nullptr;
}

std::unique_ptr<PrototypeAST> LogErrorP(const char * Str){
    LogError(Str);
    return nullptr;
}

// Expression Parsing
// numberexpr ::= number
// Called when the current token is a tok_number token.
// Takes the current value, creates a NumberExprAST node, advances the lexer to the next token and finally returns
static std::unique_ptr<ExprAST> ParseNumberExpr(){
    auto Result = std::make_unique<NumberExprAST>(NumVal);
    getNextToken(); // consume the number
    return std::move(Result);
}

// parenexpr:= '(' expression ')'
static std::unique_ptr<ExprAST> ParseParenExpr(){
    getNextToken();
    auto V = ParseExpression();
    if(!V){
        return nullptr;
    }

    if(CurTok != ')'){
        return LogError("Expected ')'");
    }
    getNextToken();
    return V;
}
