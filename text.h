#ifndef TEXT_H_
#define TEXT_H_

#include <string>

class Text {
  public: 
    static bool FillFile(const std::string& filename, int size);
    static int SumOfSquares(const std::string& filename);
    static bool FillFileMultiple(const std::string& filename, int lines, int numbers_per_line);
    static long long ProductOfElements(const std::string& filename);
    static bool CopyLinesWithLength(const std::string& input_filename, const std::string& output_filename, size_t m);
};

#endif