/*
Joseph Peterson, Section 002, joseph.as.peterson@gmail.com
InputStream class declaration
*/
#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <fstream>
#include <string>

class InputStream {
   private:
      std::string file_name;
      std::ifstream in_file;
      char current_char;
      int current_line;
   public:
      InputStream() : file_name("none"), current_line(0) {}
      InputStream(std::string name) {
         this->file_name = name;
         this->in_file.open(file_name);
         current_line = 1;
      }
      ~InputStream() {
         this->in_file.close();
      }
      char iterate();
      int getFileLine();
      void setFileName(std::string name);
      char lookAhead();
};

#endif
