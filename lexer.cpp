#include "lexer.h"

// Return the next token from the standard input

static int gettok(){
    static int LastChar = ' ';

    // Skip any whitespace.
    while(isspace(LastChar))
        LastChar = getchar();

        // Identify keywords "def" and "extern", otherwise ignore whitespace

        if(isalpha(LastChar)){
            IdentifierStr = LastChar;
            while(isalnum((LastChar = getchar()))){
                IdentifierStr +=LastChar;
            }
        
            if(IdentifierStr == "def"){
                return tok_def;
            }

            if(IdentifierStr == "extern"){
                return tok_extern;
            }
            return tok_identifier;
        }

        // Identify numbers
        if(isdigit(LastChar) || LastChar == '.'){
            std::string NumStr;
            do{
                NumStr += LastChar;
                LastChar = getchar();
            }while(isdigit(LastChar) || LastChar == '.');

            NumVal = strtod(NumStr.c_str(), 0);
            return tok_number;
        }

        // Handle Comments
        if(LastChar == '#'){
            // Comment until end of line
            do{
                LastChar == getchar();
            }while(LastChar != EOF && LastChar != '\n' && LastChar != '\r');
            if(LastChar != EOF){
                return gettok();
            }
        }

        // Check for end of file, Don't process the EOF
        if(LastChar == EOF){
            return tok_eof;
        }

        // Otherwise, return the character as its ascii value
        int ThisChar = LastChar;
        LastChar = getchar();
        return ThisChar;
}