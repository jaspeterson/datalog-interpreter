/*
Joseph Peterson, Section 002, joseph.as.peterson@gmail.com
Implement Lexer class member functions
Models a finite state machine that reads in input from a file and creates
   a list of acceptable tokens
*/
#include "Lexer.h"
#include <ctype.h>
#include <iostream>

using namespace std;

void makeToken(Lexer& lexer, TokenType type, string value, int line) {
   Token token(type, value, line);
   lexer.addToken(token);
}

void endState(Lexer& lexer) {
   makeToken(lexer, ENDFILE, "", lexer.getFileLine());
   //lexer.outputTokens();
}

void undefinedState(Lexer& lexer) {
   makeToken(lexer, UNDEFINED, lexer.getCurrentString(), lexer.getFileLine());
}

void colonState(Lexer& lexer) {
   if (lexer.lookAhead() == '-') {
      lexer.advance();
      makeToken(lexer, COLON_DASH, ":-", lexer.getFileLine());
   }
   else {
      makeToken(lexer, COLON, ":", lexer.getFileLine());
   }
}

void operatorState(Lexer& lexer, char current) {
   switch(current) {
      case ',':
         makeToken(lexer, COMMA, ",", lexer.getFileLine());
         break;
      case '.':
         makeToken(lexer, PERIOD, ".", lexer.getFileLine());
         break;
      case '?':
         makeToken(lexer, Q_MARK, "?", lexer.getFileLine());
         break;
      case '(':
         makeToken(lexer, LEFT_PAREN, "(", lexer.getFileLine());
         break;
      case ')':
         makeToken(lexer, RIGHT_PAREN, ")", lexer.getFileLine());
         break;
      case ':':
         colonState(lexer);
         break;
      case '*':
         makeToken(lexer, MULTIPLY, "*", lexer.getFileLine());
         break;
      case '+':
         makeToken(lexer, ADD, "+", lexer.getFileLine());
         break;
   }
}

void undefinedString(Lexer& lexer, int line) {
   lexer.popEOFChar();
   makeToken(lexer, UNDEFINED, lexer.getCurrentString(), line);
}

void stringState(Lexer& lexer) {
   int startLine = lexer.getFileLine();
   bool validStr = true;
   char current = '-';
   while (validStr) {
      if (lexer.lookAhead() == '\'') {
         current = lexer.advance();
         if (lexer.lookAhead() != '\'') {
            validStr = false;
         }
         else {
            current = lexer.advance();
         }
      }
      else {
         current = lexer.advance();
      }
      if (current == -1) {
         validStr = false;
      }
   }
   if (current != -1) {
      makeToken(lexer, STRING, lexer.getCurrentString(), startLine);
   }
   else {
      undefinedString(lexer, startLine);
   }
}

bool checkID(Lexer& lexer, string id, int line) {
   if (id == "Schemes") {
      makeToken(lexer, SCHEMES, id, line);
      return true;
   }
   else if (id == "Rules") {
      makeToken(lexer, RULES, id, line);
      return true;
   }
   else if (id == "Facts") {
      makeToken(lexer, FACTS, id, line);
      return true;
   }
   else if (id == "Queries") {
      makeToken(lexer, QUERIES, id, line);
      return true;
   }
   return false;
}

void idState(Lexer& lexer) {
   bool validId = true;
   char current = '-',
    future = '-';
   while(validId) {
      future = lexer.lookAhead();
      if (!isdigit(future) && !isalpha(future)) {
         validId = false;
      }
      else {
         current = lexer.advance();
      }
   }
   if (current == -1) {
      lexer.popEOFChar();
   }
   if (!checkID(lexer, lexer.getCurrentString(), lexer.getFileLine())) {
      makeToken(lexer, ID, lexer.getCurrentString(), lexer.getFileLine());
   }
}

void undefinedComment(Lexer& lexer, int line) {
   lexer.popEOFChar();
   makeToken(lexer, UNDEFINED, lexer.getCurrentString(), line);
}

void multiLineComment(Lexer& lexer) {
   int startLine = lexer.getFileLine();
   char current = lexer.advance();
   bool stillComment = true;
   while (stillComment) {
      if (lexer.lookAhead() == '|') {
         current = lexer.advance();
         if (lexer.lookAhead() == '#') {
            current = lexer.advance();
            stillComment = false;
         }
      }
      else {
         current = lexer.advance();
      }
      if (current == -1) {
         stillComment = false;
      }
   }
   if (current == -1) {
      undefinedComment(lexer, startLine);
   }
   else {
      //makeToken(lexer, COMMENT, lexer.getCurrentString(), startLine);
   }
}

void singleLineComment(Lexer& lexer) {
   char future = lexer.lookAhead();
   while (future != -1 && future != '\n' && future != '\r') {
      lexer.advance();
      future = lexer.lookAhead();
   }
   //makeToken(lexer, COMMENT, lexer.getCurrentString(), lexer.getFileLine());
}

void commentState(Lexer& lexer) {
   char future = lexer.lookAhead();
   if (future == '|') {
      multiLineComment(lexer);
   }
   else if (future == '\n' || future == '\r') {
      //makeToken(lexer, COMMENT, lexer.getCurrentString(), lexer.getFileLine());
   }
   else {
      singleLineComment(lexer);
   }
}

void startState(Lexer& lexer) {
   lexer.clearString();
   char current = lexer.advance();
   while(current != -1) {
      switch (current) {
         case ',':
            operatorState(lexer,current);
            break;
         case '.':
            operatorState(lexer,current);
            break;
         case '?':
            operatorState(lexer,current);
            break;
         case '(':
            operatorState(lexer,current);
            break;
         case ')':
            operatorState(lexer,current);
            break;
         case ':':
            operatorState(lexer,current);
            break;
         case '*':
            operatorState(lexer,current);
            break;
         case '+':
            operatorState(lexer,current);
            break;
         case '\'':
            stringState(lexer);
            break;
         case '#':
            commentState(lexer);
            break;
         default:
            if (isalpha(current)) {
               idState(lexer);
            }
            else if (isspace(current)) {}
            else {
               undefinedState(lexer);
            }
      }
      lexer.clearString();
      current = lexer.advance();
   }
   endState(lexer);
}

vector<Token> Lexer::begin() {
   startState(*this);
   return this->tokens;
}

void Lexer::outputTokens() {
   for(unsigned int i = 0; i < this->tokens.size(); i++) {
      cout << "(" << this->tokens[i].findType() << ",\"" << this->tokens[i].getValue()
         << "\"," << this->tokens[i].getFileLine() << ")" << endl;
      }
   cout << "Total Tokens = " << this->tokens.size() << endl;
}

void Lexer::clearString() {
   this->currentString = "";
}

string Lexer::getCurrentString() {
   return this->currentString;
}

void Lexer::popEOFChar() {
   this->currentString = this->currentString.substr(0,this->currentString.length()-1);
}

void Lexer::addToken(Token token) {
   this->tokens.push_back(token);
}

int Lexer::getFileLine() {
   return this->inStream->getFileLine();
}

char Lexer::advance() {
   this->currentChar = this->inStream->iterate();
   this->currentString += this->currentChar;
   return this->currentChar;
}

char Lexer::lookAhead() {
   return this->inStream->lookAhead();
}
