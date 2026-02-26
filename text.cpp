#include "text.h"

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>

// Заполнение случайными числами
bool Text::FillFile(const std::string& filename, int size) {
  if (size <= 0) {
    std::cerr << "Неправильный размер файла.\n";
    return false;
  }

  std::ofstream out(filename);
  if (!out) {
    std::cerr << "Не удалось открыть файл для записи.\n";
    return false;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-50, 50);

  std::cout << "Сгенерированные числа: ";
  for (int i = 0; i < size; ++i) {
    int number = dis(gen);
    std::cout << number << " ";
    out << number << "\n";
  }
   std::cout << "\n";

  out.close();
  return true;
}

// В файле найти сумму квадратов элементов
int Text::SumOfSquares(const std::string& filename) {
  std::ifstream in(filename);
  if (!in) {
    std::cerr << "Не удалось открыть файл для чтения.\n";
    return 0;
  }

  int sum = 0;
  int number = 0;
  while (in >> number) {
    sum += number * number;
  }

  in.close();
  return sum;
}

// Заполнение файла числами по несколько в строке
bool Text::FillFileMultiple(const std::string& filename, int lines, int numbers_per_line) {
  if (lines <= 0 || numbers_per_line <= 0) {
    std::cerr << "Неправильные параметры для заполнения файла.\n";
    return false;
  }

  std::ofstream out(filename);
  if (!out) {
    std::cerr << "Не удалось открыть файл для записи.\n";
    return false;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-50, 50);

  std::cout << "Сгенерированная матрица чисел:\n";
  for (int i = 0; i < lines; ++i) {
    for (int j = 0; j < numbers_per_line; ++j) {
      int number = dis(gen);
      std::cout << number << " ";
      out << number;
      if (j != numbers_per_line - 1) {
        out << " ";
      }
    }
    std::cout << "\n";
    out << "\n";
  }

  out.close();
  return true;
}

// Вычислить произведение элементов
long long Text::ProductOfElements(const std::string& filename) {
  std::ifstream in(filename);
  if (!in) {
    std::cerr << "Не удалось открыть файл для чтения.\n";
    return 0;
  }

  long long product = 1;
  std::string line;
  while (std::getline(in, line)) {
    std::istringstream iss(line);
    int number = 0;
    while (iss >> number) {
      product *= number;
    }
  }

  in.close();
  return product;
}

// Переписать в другой файл строки, имеющие заданную длину m.
bool Text::CopyLinesWithLength(const std::string& input_filename,
                                const std::string& output_filename,
                                size_t m) {
  if (m == 0) {
    std::cerr << "Длина строки должна быть больше нуля.\n";
    return false;
  }

  std::ifstream in(input_filename);
  if (!in) {
    std::cerr << "Не удалось открыть исходный файл для чтения.\n";
    return false;
  }

  std::ofstream out(output_filename);
  if (!out) {
    std::cerr << "Не удалось открыть файл для записи.\n";
    in.close();
    return false;
  }

  std::string line;
  while (std::getline(in, line)) {
    if (line.length() == m) {
      out << line << "\n";
    }
  }

  in.close();
  out.close();
  return true;
}