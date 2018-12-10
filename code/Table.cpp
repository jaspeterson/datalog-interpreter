#include "Table.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

string Table::getName() {
	return this->name;
}

int Table::getSize() {
	return this->rows.size();
}

Header Table::getHeader() {
	return this->header;
}

Header* Table::getHeaderP() {
	return &(this->header);
}

void Table::setHeader(Header& newHeader) {
	this->header = newHeader;
}

Row Table::getRow(unsigned int index) {
	//if (index < this->rows.size()) {
	return this->rows[index];
	//}
	//Return something else if false
}

void Table::addRow(Row nextRow) {
	if (!checkRows(nextRow)) {
		this->rows.push_back(nextRow);
	}
}

void Table::setRows(vector<Row> newRows) {
	this->rows = newRows;
}

bool Table::checkRows(Row nextRow) {
	//check all rows, if the same return true
	for (unsigned int i = 0; i < this->rows.size(); i++) {
		if (nextRow.toString() == this->rows[i].toString()) {return true;}
		/*int count = 0;
		for (int j = 0; j < this->header.getSize(); j++) {
			if (nextRow.getElement(j) == this->rows[i].getElement(j)) {count++;}
		}
		if (count == this->header.getSize()) {return true;}*/
	}
	return false;
}


//select
Table Table::select(int index, string value) {
	Table updatedTable(this->name, this->header);
	for (int i = 0; i < this->getSize(); i++) {
		if (this->getRow(i).getElement(index) == value) {
			updatedTable.addRow(this->getRow(i));
		}
	}
	return updatedTable;
}

Table Table::select(int index1, int index2) {
	Table updatedTable(this->name, this->header);
	for (int i = 0; i < this->getSize(); i++) {
		if (this->getRow(i).getElement(index1) == this->getRow(i).getElement(index2)) {
			updatedTable.addRow(this->getRow(i));
		}
	}
	return updatedTable;	
}

Table* Table::selectP(int index1, int index2) {
	Table* updatedTable = new Table(this->name, this->header);
	for (int i = 0; i < this->getSize(); i++) {
		if (this->getRow(i).getElement(index1) == this->getRow(i).getElement(index2)) {
			updatedTable->addRow(this->getRow(i));
		}
	}
	return updatedTable;
}

//project
Table Table::project(vector<int> indeces) {
	vector<string> headerVals;
	for (unsigned int i = 0; i < indeces.size(); i++) {
		headerVals.push_back(this->header.getElement(indeces[i]));
	}
	Header head(headerVals);
	Table projectedTable(this->name,head);
	for (unsigned int i = 0; i < this->rows.size(); i++) {
		vector<string> rowVals;
		for (unsigned int j = 0; j < indeces.size(); j++) {
			rowVals.push_back(this->rows[i].getElement(indeces[j]));
		}
		Row nextRow(rowVals);
		projectedTable.addRow(nextRow);
	}
	return projectedTable;
}

Table* Table::projectP(vector<int> indeces) {
	vector<string> headerVals;
	for (unsigned int i = 0; i < indeces.size(); i++) {
		headerVals.push_back(this->header.getElement(indeces[i]));
	}
	Header head(headerVals);
	Table* projectedTable = new Table(this->name,head);
	for (unsigned int i = 0; i < this->rows.size(); i++) {
		vector<string> rowVals;
		for (unsigned int j = 0; j < indeces.size(); j++) {
			rowVals.push_back(this->rows[i].getElement(indeces[j]));
		}
		Row nextRow(rowVals);
		projectedTable->addRow(nextRow);
	}
	return projectedTable;
}

//rename
Table Table::rename(Header renamedHeader) {
	Table renamedTable(this->name,renamedHeader);
	for (unsigned int i = 0; i < this->rows.size(); i++) {
		renamedTable.addRow(this->rows[i]);
	}
	return renamedTable;
}

//Union
void Table::unionTable(Table& uTable) {
	if (this->getHeader().toString() == uTable.getHeader().toString()) {
		for (int i = 0; i < uTable.getSize(); i++) {
			this->addRow(uTable.getRow(i));
		}
	}
}

Header combineHeaders(Header a, Header b) {
	vector<string> newHeader;
	for (int i = 0; i < a.getSize(); i++) {
		newHeader.push_back(a.getElement(i));
	}
	for (int i = 0; i < b.getSize(); i++) {
		newHeader.push_back(b.getElement(i));
	}
	Header header(newHeader);
	return header;
}

Row combineRows(Row a, Row b) {
	vector<string> newRow;
	for (int i = 0; i < a.getSize(); i++) {
		newRow.push_back(a.getElement(i));
	}
	for (int i = 0; i < b.getSize(); i++) {
		newRow.push_back(b.getElement(i));
	}
	Row row(newRow);
	return row;
}

Table* Table::crossProduct(Table& Table2) {
	//make one header
	Header header = combineHeaders(this->getHeader(), Table2.getHeader());
	Table* cpTable = new Table(this->name + "x" + Table2.getName(),header);
	//combine all rows - O(n^2)
	for (int i = 0; i < this->getSize(); i++) {
		for (int j = 0; j < Table2.getSize(); j++) {
			cpTable->addRow(combineRows(this->getRow(i), Table2.getRow(j)));
		}
	}
	return cpTable;
}

vector<vector<int>> makeColValPairs(Header* a, Header* b) {
	vector<vector<int>> pairs;
	for (int i = 0; i < a->getSize(); i++) {
		for (int j = 0; j < b->getSize(); j++) {
			if (a->getElement(i) == b->getElement(j)) {
				pairs.push_back({i,j});
			}
		}
	}
	return pairs;
}

//Natural Join
Table Table::joinTable(Table& jTable) {
	//compare the headers and make column value pairs
	vector<vector<int>> colValPairs = makeColValPairs(this->getHeaderP(),jTable.getHeaderP());
	//rename the second half: _Name
	for (unsigned int i = 0; i < colValPairs.size(); i++) {
		Header fixedHeader = jTable.getHeader();
		fixedHeader.setElement(colValPairs[i][1],"_" + this->header.getElement(colValPairs[i][1]));
		jTable.setHeader(fixedHeader);
		colValPairs[i][1] += this->getHeader().getSize();
	}
	//get the cross product
	Table* joinedTable = this->crossProduct(jTable);
	//cout << joinedTable->toString() << endl;
	//for (i in colpairs)
		//select firstIndex == secondIndex + firstheader.size
		//make project vector (all cols except 2nd half of tuple)
	vector<int> projVect;
	for (int i = 0; i < joinedTable->getHeader().getSize(); i++) {
		bool isRepeat = false;
		for (unsigned int j = 0; j < colValPairs.size(); j++) {
			if (i == colValPairs[j][1]) {isRepeat = true;}
		}
		if (!isRepeat) {projVect.push_back(i);}
	}
	
	for (unsigned int i = 0; i < colValPairs.size(); i++) {
		Table* temp = joinedTable;
		joinedTable = joinedTable->selectP(colValPairs[i][0],colValPairs[i][1]);
		delete temp;
	}
	
	/*for (unsigned int i = 0; i < projVect.size(); i++) {
		cout << projVect[i] << endl;
	}*/
	//project and return
	Table* temp = joinedTable;
	joinedTable = joinedTable->projectP(projVect);
	delete temp;
	return *joinedTable;
}

// ***** Deprecated *****
string Table::toString() {
	//name\nh1,h2,h3\nr1,r2,r3\n...
	ostringstream oss;
	oss << this->name << "\n";
	for (int i = 0; i < this->header.getSize(); i++) {
		if (i != 0) {oss << ",";}
		oss << this->header.getElement(i);
	}
	oss << "\n";
	//call row to string
	for (unsigned int i = 0; i < this->rows.size(); i++) {
		oss << this->rows[i].toString();
		if (i < (this->rows.size() - 1)) {oss << "\n";}
	}
	return oss.str();
} 

/*
string Table::toString() {
	ostringstream oss;
	for (unsigned int i = 0; i < this->rows.size(); i++) {
		for (int j = 0; j < this->header.getSize(); j++) {
			if (j != 0) {oss << ", ";}
			else {oss << "  ";}
			oss << this->header.getElement(j) << "=" << this->rows.at(i).getElement(j);
		}
		oss << "\n";
	}
	return oss.str();
}
*/

int compareRows(Row row1, Row row2) {
	for (int k = 0; k < row1.getSize(); k++) {
		if (row1.getElement(k) < row2.getElement(k)) {return 0;}
		if (row1.getElement(k) > row2.getElement(k)) {return 1;}
	}
	return -1; //crap...
}

void Table::sort() {
	vector<Row> sortedRows;
	sortedRows.push_back(this->getRow(0));
	for (int i = 1; i < this->getSize(); i++) {
		unsigned int j = 0;
		while (j < sortedRows.size() && compareRows(this->getRow(i),sortedRows[j]) == 1) {j++;}
		if (j < sortedRows.size()) {
			sortedRows.insert(sortedRows.begin() + j, this->getRow(i));
		}
		else {
			sortedRows.push_back(this->getRow(i));
		}
	}
	this->setRows(sortedRows);
}
