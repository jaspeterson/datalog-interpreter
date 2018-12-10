#ifndef INDIVIDUALS_H
#define INDIVIDUALS_H

#include "Elements.h"
#include "Parser.h"
#include <vector>

class Scheme {
   private:
      //required elements
      Parser* parser;
      Id header;
      std::vector<Id> ids;
   public:
      Scheme() {}
      void getParser(Parser* parser);
      std::string toString();
      bool scan();
      void setHeader(Token id);
      void addId(Token id);
		Id getHeader();
		std::vector<Id> getBody();
};

class Fact {
   private:
      //required elements
      Parser* parser;
      Id header;
      std::vector<std::string> strings;
   public:
      Fact() {}
      void getParser(Parser* parser);
      std::string toString();
      bool scan();
      void setHeader(Token id);
      void addString(Token str);
      int getListSize();
      std::string getDomain(unsigned int index);
		Id getHeader();
		std::vector<std::string> getBody();
};

class Rule {
   private:
      //required elements
      Parser* parser;
      Scheme headPredicate;
      std::vector<Predicate> predicates;
   public:
      Rule() {}
      void getParser(Parser* parser);
      std::string toString();
      bool scan();
      void setHeader(Scheme head);
      void addPredicate(Predicate pred);
		Scheme getHeadPredicate();
		std::vector<Predicate> getPredicates();
};

class Query {
   private:
      //required elements
      Parser* parser;
      Predicate predicate;
   public:
      Query() {}
      void getParser(Parser* parser);
      std::string toString();
      bool scan();
      void addPredicate(Predicate nextPred);
		Predicate getPredicate();
};

#endif
