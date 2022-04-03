#include "lexer.h"
#include "ast.h"
#include <memory>

// Example
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