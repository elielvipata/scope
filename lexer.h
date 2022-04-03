#include <string>

// This lexer returns tokens [0-255] if it is an unknown character, otherwise it returns one of the following

enum Token{
    tok_eof = -1,

    // Commands
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5,
};

static std::string IdentifierStr;   // Filled in if tok_identifier
static double NumVal;               // Filled in if tok_number
static int gettok();