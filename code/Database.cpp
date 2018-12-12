#include "Database.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void Database::addRelation(Table nextTable) {
	this->relations.insert({nextTable.getName(), nextTable});
}

Table Database::getRelation(string tableName) {
	map<string, Table>::iterator it;
	it = this->relations.find(tableName);
	return it->second;
}

Table* Database::getRelationP(string tableName) {
	map<string, Table>::iterator it;
	it = this->relations.find(tableName);
	return &(it->second);
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

bool Database::runRule(vector<vector<string>> rulePreds, string relationName, vector<string> tableHead) {
	//Get the tables and rename to predicate header
	//Query the predicates
	vector<Table> predicates;
	for (unsigned int i = 1; i < rulePreds.size(); i++) {
		predicates.push_back(runQuery(rulePreds[i], rulePreds[i][0]));
	}
	//Natural join
	Table* temp = &(predicates[0]);
	for (unsigned int i = 1; i < predicates.size(); i++) {
		*temp = temp->joinTable(&(predicates[i]));
	}
	//project to match head predicate
	vector<int> projVec;
	for(unsigned int i = 1; i < tableHead.size(); i++) {
		for(int j = 0; j < temp->getHeaderP()->getSize(); j++) {
			if (tableHead[i] == temp->getHeaderP()->getElement(j)) {
				projVec.push_back(j);
			}
		}
	}
	*temp = temp->project(projVec);
	*temp = temp->rename(this->getRelationP(relationName)->getHeader());
	//save main table to string
	string main = this->getRelationP(relationName)->toString();
	//union
	this->getRelationP(relationName)->unionTable(*temp);
	//compare strings, if different return true
	if (this->getRelationP(relationName)->toString() == main) {return false;}
	return true;
}

Table Database::runQuery(vector<string> queryParams, string relationName) {
	queryParams.erase(queryParams.begin());
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
	return queriedRel;
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

