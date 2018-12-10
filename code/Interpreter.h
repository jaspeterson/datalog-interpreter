#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Categories.h"
#include "Database.h"

class Interpreter {
	private:
		Datalog datalogProgram;
		Database relationalDatabase;
	public:
		Interpreter(std::string filename) {
			datalogProgram.setFile(filename);
			datalogProgram.start();
		}
		void start();
		void makeRelations();
		void populateRelations();
		void runRules();
		void interpretQueries();
};

#endif
