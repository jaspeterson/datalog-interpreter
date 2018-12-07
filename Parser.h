#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "Lexer.h"
#include <vector>

class Parser {
   private:
      int index;
      std::vector<Token> tokens;
   public:
      Parser(){
         index = 0;
      }
      void begin(std::string fileName);
      Token advance();
      Token getToken();
};

#endif
