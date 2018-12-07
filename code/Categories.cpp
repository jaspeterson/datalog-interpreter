#include "Categories.h"
#include "Token.h"
#include <sstream>
#include <iostream>

using namespace std;

void Datalog::setFile(string filename) {
	this->file = filename;
}

void Datalog::getParser(Parser& parser) {
   this->parser = parser;
}

bool Datalog::beginParse() {
   this->schemes.getParser(this->parser);
   if (this->schemes.scan()) {
      this->facts.getParser(this->parser);
      if (this->facts.scan()) {
         this->rules.getParser(this->parser);
         if (this->rules.scan()) {
            this->queries.getParser(this->parser);
            if (this->queries.scan()) {
               return true;
            }
         }
      }
   }
   return false;
}

void Datalog::start() {
   Parser parse;
   parse.begin(this->file);
   this->getParser(parse);
   if (this->beginParse()) {
    //  cout << "Success!" << endl;
    //  cout << this->toString();
   }
   else {
      cout << "Failure!" << endl;
      Token failed = this->parser.getToken();
      cout << "  (" << failed.findType() << ",\"" << failed.getValue()
         << "\"," << failed.getFileLine() << ")" << endl;
   }
}

//Interpreter Interface
vector<vector<string>> Datalog::getSchemes() {
	vector<vector<string>> relations;
	for (int i = 0; i < this->schemes.getSize(); i++) {
		vector<string> nextScheme;
		nextScheme.push_back(this->schemes.getScheme(i).getHeader().toString());
		for (unsigned int j = 0; j < this->schemes.getScheme(i).getBody().size(); j++) {
			nextScheme.push_back(this->schemes.getScheme(i).getBody().at(j).toString());
		}
		relations.push_back(nextScheme);
	}
	return relations;
}

vector<vector<string>> Datalog::getFacts() {
	vector<vector<string>> tuples;
	for (int i = 0; i < this->facts.getSize(); i++) {
		vector<string> nextFact;
		nextFact.push_back(this->facts.getFact(i).getHeader().toString());
		for (unsigned int j = 0; j < this->facts.getFact(i).getBody().size(); j++) {
			nextFact.push_back(this->facts.getFact(i).getBody().at(j));
		}
		tuples.push_back(nextFact);
	}
	return tuples;
}

vector<vector<string>> Datalog::getQueries() {
	vector<vector<string>> convertedQueries;
	for (int i = 0; i < this->queries.getSize(); i++) {
		vector<string> nextQuery;
		nextQuery.push_back(this->queries.getQuery(i).getPredicate().getHeader().toString());
		for (unsigned int j = 0; j < this->queries.getQuery(i).getPredicate().getParameters().size(); j++) {
			nextQuery.push_back(this->queries.getQuery(i).getPredicate().getParameters().at(j).toString());
		}
		convertedQueries.push_back(nextQuery);
	}
	return convertedQueries;
}

vector<string> Datalog::getQueriesToString() {
	vector<string> queriesToString;
	for (int i = 0; i < this->queries.getSize(); i++) {
		queriesToString.push_back(this->queries.getQuery(i).toString());
	}
	return queriesToString;
}

//******** Schemes ********

void Schemes::getParser(Parser& parser) {
   this->parser = &parser;
}

bool Schemes::scan() {
   Token current = this->parser->getToken();
   if (current.getType() == SCHEMES) {
      current = this->parser->advance();
      if (current.getType() == COLON) {
         current = this->parser->advance();
         while (current.getType() == ID) {
            Scheme nextScheme;
            nextScheme.getParser(this->parser);
            if (nextScheme.scan()) {
               this->listSchemes.push_back(nextScheme);
            }
            else {return false;}
            current = this->parser->advance();
         }
         if (this->listSchemes.size() > 0) {
            return true;
         }
      }
   }
   return false;
}

int Schemes::getSize() {
	return this->listSchemes.size();
}

Scheme Schemes::getScheme(int index) {
	return this->listSchemes[index];
}

//******** Facts ********
// add functionality to save domains

void Facts::getParser(Parser& parser) {
   this->parser = &parser;
}

void Facts::getDomains(Fact nextFact) {
   for (int i = 0; i < nextFact.getListSize(); i++) {
      this->domains.insert(nextFact.getDomain(i));
   }
}

bool Facts::scan() {
   Token current = this->parser->getToken();
   if (current.getType() == FACTS) {
      current = this->parser->advance();
      if (current.getType() == COLON) {
         current = this->parser->advance();
         while (current.getType() == ID) {
            Fact nextFact;
            nextFact.getParser(this->parser);
            if (nextFact.scan()) {
               this->listFacts.push_back(nextFact);
               this->getDomains(nextFact);
            }
            else {return false;}
            current = this->parser->advance();
         }
         return true;
      }
   }
   return false;
}

Fact Facts::getFact(int index) {
	return this->listFacts[index];
}

int Facts::getSize() {
	return this->listFacts.size();
}

//******** Rules ********

void Rules::getParser(Parser& parser) {
   this->parser = &parser;
}

bool Rules::scan() {
   Token current = this->parser->getToken();
   if (current.getType() == RULES) {
      current = this->parser->advance();
      if (current.getType() == COLON) {
         current = this->parser->advance();
         while (current.getType() == ID) {
            Rule nextRule;
            nextRule.getParser(this->parser);
            if (nextRule.scan()) {
               this->listRules.push_back(nextRule);
            }
            else {return false;}
            current = this->parser->advance();
         }
         return true;
      }
   }
   return false;
}

//******** Queries ********

void Queries::getParser(Parser& parser) {
   this->parser = &parser;
}

bool Queries::scan() {
   Token current = this->parser->getToken();
   if (current.getType() == QUERIES) {
      current = this->parser->advance();
      if (current.getType() == COLON) {
         current = this->parser->advance();
         while (current.getType() == ID) {
            Query nextQuery;
            nextQuery.getParser(this->parser);
            if (nextQuery.scan()) {
               this->listQueries.push_back(nextQuery);
            }
            else {return false;}
            current = this->parser->advance();
         }
         if (this->listQueries.size() > 0 && current.getType() == ENDFILE) {
            return true;
         }
      }
   }
   return false;
}

Query Queries::getQuery(int index) {
	return this->listQueries[index];
}

int Queries::getSize() {
	return this->listQueries.size();
}

string Datalog::toString() {
   return this->schemes.toString() + this->facts.toString() + this->rules.toString()
      + this->queries.toString() + this->facts.toStringDomains();
}

string Schemes::toString() {
   stringstream output;
   output << "Schemes(" << this->listSchemes.size() << "):\n";
   for (unsigned int i = 0; i < this->listSchemes.size(); i++) {
      output << "  " << this->listSchemes[i].toString() << "\n";
   }
   return output.str();
}

string Facts::toString() {
   stringstream output;
   output << "Facts(" << this->listFacts.size() << "):\n";
   for (unsigned int i = 0; i < this->listFacts.size(); i++) {
      output << "  " << this->listFacts[i].toString() << "\n";
   }
   return output.str();
}

string Facts::toStringDomains() {
   stringstream output;
   output << "Domain(" << this->domains.size() << "):\n";
   set<string> :: iterator itr;
   for (itr = this->domains.begin(); itr != this->domains.end(); ++itr) {
      string currentDomain = *itr;
      output << "  " << currentDomain << "\n";
   }
   return output.str();
}

string Rules::toString() {
   stringstream output;
   output << "Rules(" << this->listRules.size() << "):\n";
   for (unsigned int i = 0; i < this->listRules.size(); i++) {
      output << "  " << this->listRules[i].toString() << "\n";
   }
   return output.str();
}

string Queries::toString() {
   stringstream output;
   output << "Queries(" << this->listQueries.size() << "):\n";
   for (unsigned int i = 0; i < this->listQueries.size(); i++) {
      output << "  " << this->listQueries[i].toString() << "\n";
   }
   return output.str();
}