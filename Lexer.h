/*
Joseph Peterson, Section 002, joseph.as.peterson@gmail.com
Lexer class declaration
*/
#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "InputStream.h"
#include "Token.h"

class Lexer {
   private:
      InputStream* inStream;
      std::vector<Token> tokens;
      std::string currentString;
      char currentChar;
   public:
      Lexer(std::string file_name) {
         inStream = new InputStream(file_name);
         currentString = "";
      }
      ~Lexer() {
         delete inStream;
      }
      std::vector<Token> begin();
      void outputTokens();
      void clearString();
      std::string getCurrentString();
      void popEOFChar();
      void addToken(Token token);
      int getFileLine();
      char advance();
      char lookAhead();
};




#endif
