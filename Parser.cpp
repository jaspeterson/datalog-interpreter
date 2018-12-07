#include "Parser.h"
#include <iostream>

using namespace std;

void Parser::begin(string fileName) {
   Lexer lex(fileName);
   tokens = lex.begin();
}

Token Parser::advance() {
   this->index++;
   return this->tokens[this->index];
}

Token Parser::getToken() {
   return this->tokens[this->index];
}
