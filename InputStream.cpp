/*
Joseph Peterson, Section 002, joseph.as.peterson@gmail.com
Implements InputStream class member functions
*/
#include "InputStream.h"

char InputStream::iterate() {
   this->in_file.get(this->current_char);
   if (this->in_file.eof()) {
      return -1;
   }
   if (this->current_char == '\n') {
      this->current_line++;
   }
   return this->current_char;
}

int InputStream::getFileLine() {
   return this->current_line;
}

void InputStream::setFileName(std::string name) {
   this->in_file.close();
   this->file_name = name;
   this->in_file.open(this->file_name);
   this->current_line = 1;
}

char InputStream::lookAhead() {
   return this->in_file.peek();
}
