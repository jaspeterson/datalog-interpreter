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
		void updateRelation(std::string tableName, Table update);
		//Query?
			//find table, perform table functions, return Table
		Table runQuery(std::vector<std::string> queryParams, std::string relationName, std::string queryHead);
};

#endif
