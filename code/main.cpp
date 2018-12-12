#include "Interpreter.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	
	if (argc == 2) {
		string file = argv[1];
		Interpreter interpreter(file);
		interpreter.makeRelations();
		interpreter.populateRelations();
		interpreter.runRules();
		interpreter.interpretQueries();
	}
	return 0;
}
