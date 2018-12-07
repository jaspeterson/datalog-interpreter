#include "Row.h"
#include <sstream>

using namespace std;

string Row::getElement(unsigned int index) {
	if (index < this->elements.size()) {
		return this->elements[index];
	}
	return "";
}

int Row::getSize() {
	return this->elements.size();
}

/*   ***** Deprecated ***** */
//except maybe not

string Row::toString() {
	ostringstream oss;
	for (unsigned int i = 0; i < this->elements.size(); i++) {
		if (i != 0) {oss << ",";}
		oss << this->elements[i];
	}
	return oss.str();
}
