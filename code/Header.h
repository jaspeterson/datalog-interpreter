#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>

class Header {
	private:
		std::vector<std::string> columns;
	public:
		Header(std::vector<std::string> head) {
			columns = head;
		}
		Header() {}
		std::string getElement(unsigned int index);
		void setElement(unsigned int index, std::string val);
		int getSize();
		std::string toString();
};

#endif
