#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <string>
#include "Table.h"

class Database {
	private:
		std::map<std::string, Table> relations;
		//map of tables
			//table name is the key
	public:
		Database() {}
		//find table
		void addRelation(Table nextTable);
		Table getRelation(std::string tableName);
		Table* getRelationP(std::string tableName);
		void updateRelation(std::string tableName, Table update);
		bool runRule(std::vector<std::vector<std::string>> rulePreds, std::string relationName, std::vector<std::string> tableHead);
		//Query?
			//find table, perform table functions, return Table
		Table runQuery(std::vector<std::string> queryParams, std::string relationName);
		Table runQuery(std::vector<std::string> queryParams, std::string relationName, std::string queryHead);
};

#endif
