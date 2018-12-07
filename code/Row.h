#ifndef ROW_H
#define ROW_H

#include <vector>
#include <string>

class Row {
	private:
		std::vector<std::string> elements;
	public:
		Row(std::vector<std::string> rowElements) {
			elements = rowElements;
		}
		Row () {}
		std::string getElement(unsigned int index);
		int getSize();
		// Deprecated - maybe no
		std::string toString();
};

#endif
