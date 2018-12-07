/*
Joseph Peterson, Section 002, joseph.as.peterson@gmail.com
Implements Token class member functions
*/
#include "Token.h"

TokenType Token::getType() {
  return this->type;
}

std::string Token::findType() {
   TokenType checkType = this->type;
   switch(checkType) {
      case COMMA:
         return "COMMA";
      case PERIOD:
         return "PERIOD";
      case Q_MARK:
         return "Q_MARK";
      case LEFT_PAREN:
         return "LEFT_PAREN";
      case RIGHT_PAREN:
         return "RIGHT_PAREN";
      case COLON:
         return "COLON";
      case COLON_DASH:
         return "COLON_DASH";
      case MULTIPLY:
         return "MULTIPLY";
      case ADD:
         return "ADD";
      case SCHEMES:
         return "SCHEMES";
      case FACTS:
         return "FACTS";
      case RULES:
         return "RULES";
      case QUERIES:
         return "QUERIES";
      case ID:
         return "ID";
      case STRING:
         return "STRING";
      case COMMENT:
         return "COMMENT";
      case UNDEFINED:
         return "UNDEFINED";
      case ENDFILE:
         return "EOF";
      default:
         return "NONE";
   }
}

std::string Token::getValue() {
  return this->value;
}

int Token::getFileLine() {
  return this->file_line;
}
