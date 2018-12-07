#include "Individuals.h"
#include "Token.h"
#include <iostream>

using namespace std;

void Scheme::getParser(Parser* parser) {
   this->parser = parser;
}

void Scheme::setHeader(Token id) {
   Id head;
   head.setValue(id.getValue());
   this->header = head;
}

void Scheme::addId(Token id) {
   Id head;
   head.setValue(id.getValue());
   this->ids.push_back(head);
}

bool Scheme::scan() {
   Token current = this->parser->getToken();
   this->setHeader(current);
   current = this->parser->advance();
   if (current.getType() == LEFT_PAREN) {
      current = this->parser->advance();
      while (current.getType() == ID) {
         this->addId(current);
         current = this->parser->advance();
         if (current.getType() == COMMA) {
            current = this->parser->advance();
         }
      }
      if (current.getType() == RIGHT_PAREN && this->ids.size() > 0) {
         return true;
      }
   }
   return false;
}

Id Scheme::getHeader() {
	return this->header;
}

vector<Id> Scheme::getBody() {
	return this->ids;
}

void Fact::getParser(Parser* parser) {
   this->parser = parser;
}

void Fact::setHeader(Token id) {
   Id head;
   head.setValue(id.getValue());
   this->header = head;
}

void Fact::addString(Token str) {
   this->strings.push_back(str.getValue());
}

int Fact::getListSize() {
   return this->strings.size();
}

string Fact::getDomain(unsigned int index) {
   if (this->strings.size() > index && index >= 0) {
      return this->strings[index];
   }
   else {return "";}
}

Id Fact::getHeader() {
	return this->header;
}

vector<string> Fact::getBody() {
	return this->strings;
}

bool Fact::scan() {
   Token current = this->parser->getToken();
   this->setHeader(current);
   current = this->parser->advance();
   if (current.getType() == LEFT_PAREN) {
      current = this->parser->advance();
      while (current.getType() == STRING) {
         this->addString(current);
         current = this->parser->advance();
         if (current.getType() == COMMA) {
            current = this->parser->advance();
         }
      }
      if (current.getType() == RIGHT_PAREN && this->strings.size() > 0) {
         current = this->parser->advance();
         if (current.getType() == PERIOD) {
            return true;
         }
      }
   }
   return false;
}

void Rule::getParser(Parser* parser) {
   this->parser = parser;
}

void Rule::setHeader(Scheme head) {
   this->headPredicate = head;
}

void Rule::addPredicate(Predicate pred) {
   this->predicates.push_back(pred);
}

bool Rule::scan() {
   Scheme header;
   header.getParser(this->parser);
   if (header.scan()) {
      this->setHeader(header);
      Token current = this->parser->advance();
      if (current.getType() == COLON_DASH) {
         current = this->parser->advance();
         while (current.getType() == ID) {
            Predicate nextPredicate;
            nextPredicate.getParser(this->parser);
            if (!nextPredicate.scan()) {
               return false;
            }
            this->addPredicate(nextPredicate);
            current = this->parser->advance();
            if (current.getType() == COMMA) {
               current = this->parser->advance();
            }
         }
         if (this->predicates.size() > 0 && current.getType() == PERIOD) {
            return true;
         }
      }
   }
   return false;
}

void Query::getParser(Parser* parser) {
   this->parser = parser;
}

void Query::addPredicate(Predicate nextPred) {
   this->predicate = nextPred;
}

bool Query::scan() {
   Token current = this->parser->getToken();
   if (current.getType() == ID) {
      Predicate nextPredicate;
      nextPredicate.getParser(this->parser);
      if (nextPredicate.scan()) {
         this->addPredicate(nextPredicate);
         Token current = this->parser->advance();
         if (current.getType() == Q_MARK) {
            return true;
         }
      }
   }
   return false;
}

Predicate Query::getPredicate() {
	return this->predicate;
}

string Scheme::toString() {
   string output = this->header.toString() + "(";
   for (unsigned int i = 0; i < this->ids.size(); i++) {
      output += this->ids[i].toString();
      if (i < this->ids.size() - 1) {
         output += ",";
      }
   }
   return output + ")";
}

string Fact::toString() {
   string output = this->header.toString() + "(";
   for (unsigned int i = 0; i < this->strings.size(); i++) {
      output += this->strings[i];
      if (i < this->strings.size() - 1) {
         output += ",";
      }
   }
   return output + ").";
}

string Rule::toString() {
   string output = this->headPredicate.toString() + " :- ";
   for (unsigned int i = 0; i < this->predicates.size(); i++) {
      output += this->predicates[i].toString();
      if (i < this->predicates.size() - 1) {
         output += ",";
      }
   }
   return output + ".";
}

string Query::toString() {
   return this->predicate.toString() + "?";
}
