#include <iostream>
#include <vector>
#include <string>
#include "Database.h"

using namespace std;
//Tests the to string of the table against the valid output
void tableTester(string outputValid, Table test);

Table test1();
Table test2();
Table test3();
Table test4();
/*Table test5();
Table test6();
Table test7();
Table test8();
Table test9();
Table test10();*/

int main() {
	//make an array of valid test output
	string validOut[10];
	validOut[0] = "test1\nA,B\n'a','b'\n'c','b'\n'a','g'\n'x','y'";
	validOut[1] = "test2\nA,B,C\n'a','b','c'\n'c','b','c'\n'a','g','a'";
	validOut[2] = "test3xtest3_2\nA,B,C,D\n'a','b','c','d'";
	validOut[3] = "test4xtest4_2\nA,B,C,D,E,F,G,H\n'a','b','c','d','e','f','g','h'\n'c','b','a','h','g','f','e','d'";
	validOut[4] = "test5\nA,B\n'a','b'\n'c','b'";
	validOut[5] = "test6\nA,B,C\n'a','b','c'";
	validOut[6] = "test7\nA,B,C\n'c','b','c'\n'a','g','a'";
	validOut[7] = "test8\nX,Y\n'b','c'\n'g','a'";
	validOut[8] = "test9\nY,X\n'b','c'\n'g','a'";
	validOut[9] = "test10\nZ,Y,X\n'a','b','c'";


	//run tests
	cout << "Running Test 1" << endl;
	tableTester(validOut[0],test1());
	cout << "Running Test 2" << endl;
	tableTester(validOut[1],test2());
	cout << "Running Test 3" << endl;
	tableTester(validOut[2],test3());
	cout << "Running Test 4" << endl;
	tableTester(validOut[3],test4());
	/*cout << "Running Test 5" << endl;
	tableTester(validOut[4],test5());
	cout << "Running Test 6" << endl;
	tableTester(validOut[5],test6());
	cout << "Running Test 7" << endl;
	tableTester(validOut[6],test7());
	cout << "Running Test 8" << endl;
	tableTester(validOut[7],test8());
	cout << "Running Test 9" << endl;
	tableTester(validOut[8],test9());
	cout << "Running Test 10" << endl;
	tableTester(validOut[9],test10());*/
	return 0;
}

void tableTester(string outputValid, Table testTable) {
	cout << "Actual\n" << testTable.toString() << endl << "Expected\n" << outputValid << endl;
	//compare test.toString() to output Valid
	if (testTable.toString() == outputValid) {
		cout << "  Passed" << endl;
	}
	else {
		cout << "  Failed" << endl;
	}
}
/*
vector<int> getUniqueVars(vector<string> params) {
	vector<int> uniqueElements;
	for (int i = 0; i < params.size(); i++) {
		bool isRepeat = false;
		for (int j = 0; j < i; j++) {
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
	for (int i = 0; i < unique.size(); i++) {
		newHeader.push_back(params[unique[i]]);
	}
	Header header(newHeader);
	return header;
}
*/
Table test1() {
	//Test 1: tests union
	//make a relation
	vector<string> headerElements = {"A","B"};
	Header header(headerElements);
	Table testRelation("test1", header);
	vector<string> row = {"'a'","'b'"};
	Row testRow(row);
	testRelation.addRow(testRow);
	row = {"'c'","'b'"};
	Row testRow1(row);
	testRelation.addRow(testRow1);
	row = {"'a'","'g'"};
	Row testRow2(row);
	testRelation.addRow(testRow2);
	cout << "Relation 1" << endl;
	//make another relation
	Table testRelation2("test2", header);
	row = {"'a'","'b'"};
	Row testRow3(row);
	testRelation2.addRow(testRow3);
	row = {"'x'","'y'"};
	Row testRow4(row);
	testRelation2.addRow(testRow4);
	cout << "Relation 2" << endl;
	testRelation.unionTable(testRelation2);
	return testRelation;
}

Table test2() {
	//Test 2: tests query test2('a',X,'c')?
	//make a relation
	vector<string> headerElements = {"A","B","C"};
	Header header(headerElements);
	Table testRelation("test2", header);
	Table testRelation2("test2_2", header);
	vector<string> row = {"'a'","'b'","'c'"};
	Row testRow(row);
	testRelation.addRow(testRow);
	testRelation2.addRow(testRow);
	row = {"'c'","'b'","'c'"};
	Row testRow1(row);
	testRelation.addRow(testRow1);
	testRelation2.addRow(testRow1);
	row = {"'a'","'g'","'a'"};
	Row testRow2(row);
	testRelation.addRow(testRow2);
	testRelation2.addRow(testRow2);
	testRelation.unionTable(testRelation2);
	return testRelation;
}

Table test3() {
	//Test 3: tests Natural join
	vector<string> headerElements = {"A","B","C"};
	Header header(headerElements);
	Table testRelation("test3", header);
	headerElements = {"A","D"};
	Header header2(headerElements);
	Table testRelation2("test3_2", header2);
	vector<string> row = {"'a'","'b'","'c'"};
	Row testRow(row);
	testRelation.addRow(testRow);
	row = {"'c'","'b'","'a'"};
	Row testRow1(row);
	testRelation.addRow(testRow1);
	row = {"'a'","'d'"};
	Row testRow2(row);
	testRelation2.addRow(testRow2);
	Table joined = testRelation.joinTable(testRelation2);
	return joined;
}

Table test4() {
	//Test 4: tests natural join
	vector<string> headerElements = {"A","B","C"};
	Header header(headerElements);
	Table testRelation("test4", header);
	headerElements = {"D","E","F","G","H"};
	Header header2(headerElements);
	Table testRelation2("test4_2", header2);
	vector<string> row = {"'a'","'b'","'c'"};
	Row testRow(row);
	testRelation.addRow(testRow);
	row = {"'c'","'b'","'a'"};
	Row testRow1(row);
	testRelation.addRow(testRow1);
	row = {"'d'","'e'","'f'","'g'","'h'"};
	Row testRow2(row);
	testRelation2.addRow(testRow2);
	row = {"'h'","'g'","'f'","'e'","'d'"};
	Row testRow3(row);
	testRelation2.addRow(testRow3);
	Table joined = testRelation.joinTable(testRelation2);
	return joined;
}
/*
Table test5() {
	//Test 5: tests project functionality A,B,C -> A,B
	vector<string> headerElements = {"A","B","C"};
	Header header(headerElements);
	Table testRelation("test5", header);
	vector<string> row = {"'a'","'b'","'c'"};
	Row testRow(row);
	testRelation.addRow(testRow);
	row = {"'c'","'b'","'a'"};
	Row testRow1(row);
	testRelation.addRow(testRow1);
	vector<int> valProject = {0,1};
	Table projected = testRelation.project(valProject);
	return projected;
}

Table test6() {
	//Test 6: tests select 1 (literal) A='a'
	vector<string> headerElements = {"A","B","C"};
	Header header(headerElements);
	Table testRelation("test6", header);
	vector<string> row = {"'a'","'b'","'c'"};
	Row testRow(row);
	testRelation.addRow(testRow);
	row = {"'c'","'b'","'a'"};
	Row testRow1(row);
	testRelation.addRow(testRow1);
	Table selected = testRelation.select(0,"'a'");
	return selected;
}

Table test7() {
	//Test 7: tests select 2 (variable repeats) A=C
	vector<string> headerElements = {"A","B","C"};
	Header header(headerElements);
	Table testRelation("test7", header);
	vector<string> row = {"'a'","'b'","'c'"};
	Row testRow(row);
	testRelation.addRow(testRow);
	row = {"'c'","'b'","'c'"};
	Row testRow1(row);
	testRelation.addRow(testRow1);
	row = {"'a'","'g'","'a'"};
	Row testRow2(row);
	testRelation.addRow(testRow2);
	Table selected = testRelation.select(0,2);
	return selected;
}

Table test8() {
	//Test 8: tests query test8('a',X,Y)?
	//make a relation
	vector<string> headerElements = {"A","B","C"};
	Header header(headerElements);
	Table testRelation("test8", header);
	vector<string> row = {"'a'","'b'","'c'"};
	Row testRow(row);
	testRelation.addRow(testRow);
	row = {"'c'","'b'","'c'"};
	Row testRow1(row);
	testRelation.addRow(testRow1);
	row = {"'a'","'g'","'a'"};
	Row testRow2(row);
	testRelation.addRow(testRow2);
	vector<string> queryParams = {"\'a\'","X","Y"};
	Table queried = testRelation;
	//select
	//select literals
	for (unsigned int i = 0; i < queryParams.size(); i++) {
		if (queryParams[i][0] == '\'') {
			queried = queried.select(i,queryParams[i]);
		}
	}
	//select variables
	for (unsigned int i = 0; i < queryParams.size(); i++) {
		for (unsigned int j = queryParams.size() - i; j < queryParams.size(); j++) {
			if (queryParams[i] == queryParams[j]) {
				queried = queried.select(i,j);
			}
		}
	}
	//project/rename
	vector<int> uniqueVariables = getUniqueVars(queryParams);
	if (uniqueVariables.size() > 0) {
		queried = queried.project(uniqueVariables);
		Header renamedHeader = makeHeader(uniqueVariables, queryParams);
		queried = queried.rename(renamedHeader);
	}
	return queried;
}

Table test9() {
	//Test 9: tests query test9('a',X,Y,X,X,Y,X)?
	//make a relation
	vector<string> headerElements = {"A","B","C","D","E","F","G"};
	Header header(headerElements);
	Table testRelation("test9", header);
	vector<string> row = {"'a'","'b'","'c'","'d'","'e'","'f'","'g'"};
	Row testRow(row);
	testRelation.addRow(testRow);
	row = {"'a'","'b'","'c'","'b'","'c'","'b'","'c'"};
	Row testRow1(row);
	testRelation.addRow(testRow1);
	row = {"'a'","'g'","'a'","'g'","'a'","'g'","'a'"};
	Row testRow2(row);
	testRelation.addRow(testRow2);
	vector<string> queryParams = {"'a'","Y","X","Y","X","Y","X"};
	Table queried = testRelation;
	//select
	//select literals
	for (unsigned int i = 0; i < queryParams.size(); i++) {
		if (queryParams[i][0] == '\'') {
			queried = queried.select(i,queryParams[i]);
		}
	}
	//select variables
	for (unsigned int i = 0; i < queryParams.size(); i++) {
		for (unsigned int j = queryParams.size() - i; j < queryParams.size(); j++) {
			if (queryParams[i] == queryParams[j]) {
				queried = queried.select(i,j);
			}
		}
	}
	//project/rename
	vector<int> uniqueVariables = getUniqueVars(queryParams);
	if (uniqueVariables.size() > 0) {
		queried = queried.project(uniqueVariables);
		Header renamedHeader = makeHeader(uniqueVariables, queryParams);
		queried = queried.rename(renamedHeader);
	}
	return queried;
}

Table test10() {
	//Test 10: tests query test10(Z,Y,X,Z,Y,X)?
	//make a relation
	vector<string> headerElements = {"A","B","C","D","E","F"};
	Header header(headerElements);
	Table testRelation("test10", header);
	vector<string> row = {"'a'","'b'","'c'","'a'","'b'","'c'"};
	Row testRow(row);
	testRelation.addRow(testRow);
	row = {"'a'","'b'","'c'","'d'","'e'","'f'"};
	Row testRow1(row);
	testRelation.addRow(testRow1);
	row = {"'c'","'b'","'a'","'c'","'b'","'d'"};
	Row testRow2(row);
	testRelation.addRow(testRow2);
	vector<string> queryParams = {"Z","Y","X","Z","Y","X"};
	Table queried = testRelation;
	//select
	//select literals
	for (unsigned int i = 0; i < queryParams.size(); i++) {
		if (queryParams[i][0] == '\'') {
			queried = queried.select(i,queryParams[i]);
		}
	}
	//select variables
	for (unsigned int i = 0; i < queryParams.size(); i++) {
		for (unsigned int j = queryParams.size() - i; j < queryParams.size(); j++) {
			if (queryParams[i] == queryParams[j]) {
				queried = queried.select(i,j);
			}
		}
	}
	//project/rename
	vector<int> uniqueVariables = getUniqueVars(queryParams);
	if (uniqueVariables.size() > 0) {
		queried = queried.project(uniqueVariables);
		Header renamedHeader = makeHeader(uniqueVariables, queryParams);
		queried = queried.rename(renamedHeader);
	}
	return queried;
}
*/
