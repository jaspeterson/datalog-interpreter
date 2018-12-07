#include "Header.h"
#include <sstream>

using namespace std;

string Header::getElement(unsigned int index) {
	if (index < this->columns.size() && index >= 0) {
		return this->columns[index];
	}
	return "";
}

void Header::setElement(unsigned int index, string val) {
	if (index < this->columns.size() && index >= 0) {
		this->columns[index] = val;
	}
}

int Header::getSize() {
	return this->columns.size();
}

string Header::toString() {
	ostringstream ostr;
	for (unsigned int i = 0; i < this->columns.size(); i++) {
		if (i < this->columns.size() - 1) {ostr << this->columns[i] << ",";}
		else {ostr << this->columns[i];}
	}
	return ostr.str();
}
