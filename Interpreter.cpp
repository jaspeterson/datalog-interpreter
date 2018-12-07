#include "Interpreter.h"
#include <iostream>

using namespace std;

void Interpreter::start() {

}

void Interpreter::makeRelations() {
	//Get schemes
	vector<vector<string>> schemes = datalogProgram.getSchemes();
	//make a relation for every scheme
	for (unsigned int i = 0; i < schemes.size(); i++) {
		string newName = schemes[i][0];
		schemes[i].erase(schemes[i].begin());
		Header newHeader(schemes[i]);
		Table newRelation(newName,newHeader);
		relationalDatabase.addRelation(newRelation);
		//cout << newRelation.toString() << endl;
	}
}

void Interpreter::populateRelations() {
	//Get facts
	vector<vector<string>> facts = datalogProgram.getFacts();
	//turn each fact into a row of the appropriate relation
	for (unsigned int i = 0; i < facts.size(); i++) {
		string name = facts[i][0];
		Table updatedRelation = relationalDatabase.getRelation(name);	
		facts[i].erase(facts[i].begin());
		Row newRow(facts[i]);
		updatedRelation.addRow(newRow);
		relationalDatabase.updateRelation(name,updatedRelation);
		//cout << updatedRelation.toString() << endl;
	}
}

void Interpreter::interpretQueries() {
	//Get queries
	vector<vector<string>> queries = datalogProgram.getQueries();
	vector<string> queryOutput = datalogProgram.getQueriesToString();
	//run each query with the appropriate output
	for (unsigned int i = 0; i < queries.size(); i++) {
		string name = queries[i][0];
		queries[i].erase(queries[i].begin());
		Table queriedRelation = relationalDatabase.runQuery(queries[i], name, queryOutput[i]);
	}
}

