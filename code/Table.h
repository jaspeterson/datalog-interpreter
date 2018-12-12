#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include "Header.h"
#include "Row.h"

class Table {
	private:
		std::string name;
		Header header;
		std::vector<Row> rows;
	public:
		Table(std::string tableName, Header head) {
			name = tableName;
			header = head;
		}
		Table() {
			name = "";
		}
		std::string getName();
		int getSize();
		Header getHeader();
		Header* getHeaderP();
		void setHeader(Header& newHeader);
		Row getRow(unsigned int index);
		Row* getRowP(unsigned int index);
		void addRow(Row nextRow);
		void setRows(std::vector<Row> newRows);
		bool checkRows(Row nextRow);
		//select
		Table select(int index, std::string value);
		Table select(int index1, int index2);
		Table* selectP(int index, std::string value);
		Table* selectP(int index1, int index2);
		//project
		Table project(std::vector<int> indeces);
		Table* projectP(std::vector<int> indeces);
		//rename
		Table rename(Header renamedHeader);
		Table* renameP(Header renamedHeader);
		std::string toString();
		void sort();
		Table joinTable(Table* jTable);
		void unionTable(Table& uTable);
		Table crossProduct(Table* Table2);
};


#endif
