/*
Joseph Peterson, Section 002, joseph.as.peterson@gmail.com
Token class declaration
*/
#ifndef TOKEN_H
#define TOKEN_H
#include <string>

//Enumerated token types
enum TokenType {
   COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN,
   COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES,
   ID, STRING, COMMENT, UNDEFINED, ENDFILE, NONE
};


class Token {
   private:
      TokenType type;
      std::string value;
      int file_line;
   public:
      Token() {
         file_line = 0;
         type = NONE;
         value = "none";
      }
      Token(TokenType typeIn, std::string val, int line) {
         type = typeIn;
         value = val;
         file_line = line;
      }
      TokenType getType();
      std::string findType();
      std::string getValue();
      int getFileLine();
};


#endif
