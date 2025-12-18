#ifndef LABORATORY_LAB5_H_
#define LABORATORY_LAB5_H_

#include <string>

class Lab5 {
 public:
  // Задание 1: Бинарные файлы (числа)
  static void FillBinaryFileNumbers(const std::string& filename, int count = 20);
  static void Task1ProductOddNegative(const std::string& filename);
  
  // Задание 2: Бинарные файлы (матрица)
  static void Task2MatrixSwapMinMaxInColumns(const std::string& filename, int size);
  
  // Задание 3: Бинарные файлы (багаж)
  static void FillBinaryFileStructures(const std::string& filename, int passenger_count = 8);
  static void Task3BaggageAnalysis(const std::string& filename);
  
  // Задание 4: Текстовые файлы (одно число в строке)
  static void FillTextFileOneNumberPerLine(const std::string& filename, int count = 15);
  static void Task4SumOfSquares(const std::string& filename);
  
  // Задание 5: Текстовые файлы (несколько чисел в строке)
  static void FillTextFileMultipleNumbersPerLine(const std::string& filename, int rows = 6);
  static void Task5ProductOfElements(const std::string& filename);
  
  // Задание 6: Текстовые файлы (текст)
  static void FillTextFileText(const std::string& filename);
  static void Task6CopyLinesOfLengthM(const std::string& input_file,
                                     const std::string& output_file,
                                     int m);
  
  // Вспомогательные методы
  static void ShowBinaryFileContents(const std::string& filename);
  static void ShowTextFileContents(const std::string& filename);

 private:
  static void InitializeRandom();
};

#endif  // LABORATORY_LAB5_H_