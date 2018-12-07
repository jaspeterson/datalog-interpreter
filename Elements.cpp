#include "Elements.h"
#include "Token.h"

using namespace std;

void Predicate::getParser(Parser* parser) {
   this->parser = parser;
}

void Predicate::addParameter(Parameter param) {
   this->parameters.push_back(param);
}

void Predicate::setHeader(Id header) {
   this->header = header;
}

bool Predicate::scan() {
   Token current = this->parser->getToken();
   Id header;
   header.setValue(current.getValue());
   this->setHeader(header);
   current = this->parser->advance();
   if (current.getType() == LEFT_PAREN) {
      current = this->parser->advance();
      bool isValidType = true;
      while (isValidType) {
         Parameter nextParameter;
         nextParameter.getParser(this->parser);
         if (!nextParameter.scan()) {
            return false;
         }
         this->addParameter(nextParameter);
         current = this->parser->advance();
         if (current.getType() == COMMA) {
            current = this->parser->advance();
         }
         switch(current.getType()) {
            case ID:
               isValidType = true;
               break;
            case STRING:
               isValidType = true;
               break;
            case LEFT_PAREN:
               isValidType = true;
               break;
            default:
               isValidType = false;
         }
      }
      if (current.getType() == RIGHT_PAREN && this->parameters.size() > 0) {
         return true;
      }
   }
   return false;
}

Id Predicate::getHeader() {
	return this->header;
}

vector<Parameter> Predicate::getParameters() {
	return this->parameters;
}

void Parameter::getParser(Parser* parser) {
   this->parser = parser;
}

void Parameter::addString(string str) {
   this->stringParam = str;
}

void Parameter::addId(Id id) {
   this->idParam = id;
}

void Parameter::addExpression(std::string nextExpression) {
   this->expression = nextExpression;
}

bool Parameter::scan() {
   Token current = this->parser->getToken();
   if (current.getType() == STRING) {
      this->addString(current.getValue());
      return true;
   }
   else if (current.getType() == ID) {
      Id nextId;
      nextId.setValue(current.getValue());
      this->addId(nextId);
      return true;
   }
   else if (current.getType() == LEFT_PAREN) {
      Expression expression;
      expression.getParser(this->parser);
      if (expression.scan()){
         this->addExpression(expression.toString());
         return true;
      }
   }
   return false;
}

void Expression::getParser(Parser* parser) {
   this->parser = parser;
}

bool Expression::isOperator() {
   Token current = this->parser->getToken();
   if (current.getType() == ADD) {
      this->setOperator(current.getValue());
      return true;
   }
   else if (current.getType() == MULTIPLY) {
      this->setOperator(current.getValue());
      return true;
   }
   return false;
}

void Expression::setParameter1(Parameter param) {
   this->parameter1 = param;
}

void Expression::setParameter2(Parameter param) {
   this->parameter2 = param;
}

void Expression::setOperator(string nextOperator) {
   this->expOperator = nextOperator;
}

bool Expression::scan() {
   Token current = this->parser->getToken();
   if (current.getType() == LEFT_PAREN) {
      current = this->parser->advance();
      Parameter parameter1;
      parameter1.getParser(this->parser);
      if (parameter1.scan()) {
         this->setParameter1(parameter1);
         current = this->parser->advance();
         if (this->isOperator()) {
            current = this->parser->advance();
            Parameter parameter2;
            parameter2.getParser(this->parser);
            if (parameter2.scan()) {
               this->setParameter2(parameter2);
               current = this->parser->advance();
               if (current.getType() == RIGHT_PAREN) {
                  return true;
               }
            }
         }
      }
   }
   return false;
}

void Id::setValue(string val) {
   this->value = val;
}

string Predicate::toString() {
   string output = this->header.toString() + "(";
   for (unsigned int i = 0; i < this->parameters.size(); i++) {
      output += this->parameters[i].toString();
      if (i < this->parameters.size()-1) {
         output += ",";
      }
   }
   return output + ")";
}

string Parameter::toString() {
   if (stringParam != "") {
      return stringParam;
   }
   else if (this->idParam.toString() != "") {
      return this->idParam.toString();
   }
   else {
      return this->expression;
   }
}

string Expression::toString() {
   return "(" + this->parameter1.toString() + this->expOperator + this->parameter2.toString() + ")";
}

string Id::toString() {
   return this->value;
}
