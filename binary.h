#ifndef BINARY_H_
#define BINARY_H_

#include <string>
#include <vector>

class Binary {
  public:
    static bool FillFile(const std::string& filename, int size);
    static long long Multiplication(const std::string& filename);
    static std::vector<std::vector<int>> MatrixSwapMinMax(const std::string& filename, int n);
    static std::vector<std::vector<int>> ReadMatrix(const std::string& filename, int n);
    static bool FillPassengers(const std::string& filename, const std::vector<int>& luggage_counts,
                               const std::vector<std::vector<std::pair<std::string, double>>>& luggage_data);
    static std::pair<int, int> AnalyzePassengers(const std::string& filename);
};
  
#endif