#ifndef CATEGORIES_H
#define CATEGORIES_H

#include "Individuals.h"
#include "Elements.h"
#include "Parser.h"
#include <vector>
#include <set>

class Schemes {
   private:
      Parser* parser;
      std::vector<Scheme> listSchemes;
   public:
      Schemes() {}
      bool scan();
      void getParser(Parser& parser);
      std::string toString();
		Scheme getScheme(int index);
		int getSize();
};

class Facts {
   private:
      Parser* parser;
      std::vector<Fact> listFacts;
      std::set<std::string> domains;
   public:
      Facts() {}
      bool scan();
      void getParser(Parser& parser);
      std::string toString();
      void getDomains(Fact nextFact);
      std::string toStringDomains();
		Fact getFact(int index);
		int getSize();
};

class Rules {
   private:
      Parser* parser;
      std::vector<Rule> listRules;
   public:
      Rules() {}
      bool scan();
      void getParser(Parser& parser);
      std::string toString();
		Rule getRule(int index);
		int getSize();
};

class Queries {
   private:
      Parser* parser;
      std::vector<Query> listQueries;
   public:
      Queries() {}
      bool scan();
      void getParser(Parser& parser);
      std::string toString();
		Query getQuery(int index);
		int getSize();
};

class Datalog {
   private:
      Schemes schemes;
      Facts facts;
      Rules rules;
      Queries queries;
      Parser parser;
      std::string file;
   public:
      Datalog() {}
		void setFile(std::string filename);
      void getParser(Parser& parser);
      bool beginParse();
      void start();
      std::string toString();
		//Interaction with Interpreter
		std::vector<std::vector<std::string>> getSchemes();
		std::vector<std::vector<std::string>> getFacts();
		std::vector<std::vector<std::vector<std::string>>> getRules();
		std::vector<std::vector<std::string>> getQueries();
		std::vector<std::string> getQueriesToString();
};

#endif
