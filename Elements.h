#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <vector>
#include "Parser.h"

class Id {
   private:
      std::string value;
   public:
      Id() {
         value = "";
      }
      std::string toString();
      void setValue(std::string val);
};

class Parameter {
   private:
      Parser* parser;
      std::string stringParam;
      Id idParam;
      std::string expression;
   public:
      Parameter() {
         stringParam = "";
         expression = "";
      }
      void getParser(Parser* parser);
      std::string toString();
      bool scan();
      void addString(std::string str);
      void addId(Id id);
      void addExpression(std::string nextExpression);
};

class Expression {
   private:
      Parser* parser;
      Parameter parameter1;
      Parameter parameter2;
      std::string expOperator;
   public:
      Expression() {}
      void getParser(Parser* parser);
      std::string toString();
      bool scan();
      void setParameter1(Parameter param);
      void setParameter2(Parameter param);
      void setOperator(std::string nextOperator);
      bool isOperator();
};

class Predicate {
   private:
      Parser* parser;
      Id header;
      std::vector<Parameter> parameters;
   public:
      Predicate() {}
      void getParser(Parser* parser);
      void setHeader(Id header);
      std::string toString();
      bool scan();
      void addParameter(Parameter param);
		Id getHeader();
		std::vector<Parameter> getParameters();
};

#endif
