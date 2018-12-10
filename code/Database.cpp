#include "Database.h"
#include <iostream>

using namespace std;

void Database::addRelation(Table nextTable) {
	this->relations.insert({nextTable.getName(), nextTable});
}

Table Database::getRelation(string tableName) {
	map<string, Table>::iterator it;
	it = this->relations.find(tableName);
//	if (it != this->relations.end()) {
	return it->second;
//	}
	//Return something if false
}

void Database::updateRelation(string tableName, Table update) {
	map<string, Table>::iterator it;
	it = this->relations.find(tableName);
	if (it != this->relations.end()) {
		it->second = update;
	}
}

vector<int> getUniqueVars(vector<string> params) {
	vector<int> uniqueElements;
	for (unsigned int i = 0; i < params.size(); i++) {
		bool isRepeat = false;
		for (unsigned int j = 0; j < i; j++) {
			if (params[i] == params[j]) {isRepeat = true;}
		}
		if (!isRepeat && params[i][0] != '\'') {
			uniqueElements.push_back(i);
		}
	}
	return uniqueElements;
}

Header makeHeader(vector<int> unique, vector<string> params) {
	vector<string> newHeader;
	for (unsigned int i = 0; i < unique.size(); i++) {
		newHeader.push_back(params[unique[i]]);
	}
	Header header(newHeader);
	return header;
}

void outputResults(string queryHead, Table queriedRel, int unique) {
	cout << queryHead;
	if (queriedRel.getSize() > 0) {
		cout << " Yes(" << queriedRel.getSize() << ")" << endl;
		if (unique > 0) {
			queriedRel.sort();
			cout << queriedRel.toString();
		}
	}
	else {
		cout << " No" << endl;
	}
}

bool Database::runRule(std::vector<std::vector<std::string>> rulePreds, std::string relationName, std::vector<std::string> tableHead) {
	//Get the tables and rename to predicate header
	//Query the predicates
	//Natural join
	//project to match head predicate
	//rename to main table
	//save main table to string
	//union
	//compare strings, if different return true
}

Table Database::runQuery(vector<string> queryParams, string relationName, string queryHead) {
	Table queriedRel = this->getRelation(relationName);
	//select literals
	for (unsigned int i = 0; i < queryParams.size(); i++) {
		if (queryParams[i][0] == '\'') {
			queriedRel = queriedRel.select(i,queryParams[i]);
		}
	}
	//select variables
	for (unsigned int i = 0; i < queryParams.size(); i++) {
		for (unsigned int j = queryParams.size() - (i + 1); j < queryParams.size(); j++) {
			if (queryParams[i] == queryParams[j]) {
				queriedRel = queriedRel.select(i,j);
			}
		}
	}
	//project & rename
	vector<int> uniqueVariables = getUniqueVars(queryParams);
	if (uniqueVariables.size() > 0) {
		queriedRel = queriedRel.project(uniqueVariables);
		queriedRel = queriedRel.rename(makeHeader(uniqueVariables, queryParams));
	}
	//output
	outputResults(queryHead, queriedRel, uniqueVariables.size());
	return queriedRel;
}

