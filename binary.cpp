#include "binary.h"

#include <fstream>
#include <iostream>
#include <random>
#include <cstring>

namespace {

  // Структура багажа
  struct Luggage {
    char name[20];
    double weight;
  };

  // Структура пассажира
  struct Passenger {
    int luggage_count;
    Luggage luggage[10];
  };
}

// Заполнение файла случайными числами
bool Binary::FillFile(const std::string& filename, int size) {
    if (size <= 0) {
      std::cerr << "Неправильные парамерты для заполнения файла";
      return false; 
    }

    std::ofstream out(filename, std::ios::binary);
    if (!out) {
      std::cerr << "Не удаётся открыть файл для записи";
      return false;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-50, 50);

    std::cout << "Сгенерированные числа: ";
    for (int i = 0; i < size; ++i) {
      int number = dis(gen);
      std::cout << number << " ";
      out.write(reinterpret_cast<char*>(&number), sizeof(int));
    }
    std::cout << "\n";

    out.close();
    return true;
}

// Вычислить произведение нечетных отрицательных компонент файла.
long long Binary::Multiplication(const std::string& filename) {
  std::ifstream in(filename, std::ios::binary);
  if (!in) {
    std::cerr << "Не удаётся открыть файл для чтения";
    return 0;
  }

  long long product = 1;
  bool found = false;
  int number;

  while (in.read(reinterpret_cast<char*>(&number), sizeof(int))) {
    if (number < 0 && number % 2 != 0) {
      product *= number;
      found = true;
    }
  }
  in.close();
  if (!found) {
    return 0;
  }
  return product;
}

// Чтение матрицы для вывода
std::vector<std::vector<int>> Binary::ReadMatrix(const std::string& filename, int n) {
  if (n <= 0) {
    std::cerr << "Неверные параметры для матрицы\n";
    return {};
  }

  std::ifstream in(filename, std::ios::binary);
  if (!in) {
    std::cerr << "Невозможно открыть файл для чтения\n";
    return {};
  }

  std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

  int number = 0;
  int count = 0;
  while (in.read(reinterpret_cast<char*>(&number), sizeof(int)) && count < n * n) {
    int row = count / n;
    int col = count % n;
    matrix[row][col] = number;
    ++count;
  }

  in.close();
  return matrix;
}

// Поменять местами в каждом столбце минимальный и максимальный элементы
std::vector<std::vector<int>> Binary::MatrixSwapMinMax(const std::string& filename, int n) {
  auto matrix = ReadMatrix(filename, n);
  if (matrix.empty()) {
    return {};
  }
  for (int col = 0; col < n; ++col) {
    int min_index = 0;
    int max_index = 0;
    for (int row = 1; row < n; ++row) {
      if (matrix[row][col] < matrix[min_index][col]) min_index = row;
      if (matrix[row][col] > matrix[max_index][col]) max_index = row;
    }
    std::swap(matrix[min_index][col], matrix[max_index][col]);
  }

  return matrix;
}


bool Binary::FillPassengers(
    const std::string& filename,
    const std::vector<int>& luggage_counts, // количество багажа у каждого
    const std::vector<std::vector<std::pair<std::string, double>>>& luggage_data) {
  if (luggage_counts.size() != luggage_data.size()) {
    std::cerr << "Количество пассажиров не совпадает";
    return false;
  }

  std::ofstream out(filename, std::ios::binary);
  if (!out) {
    std::cerr << "Не удалось открыть файл для записи";
    return false;
  }

  for (size_t i = 0 ; i < luggage_counts.size(); ++i) {
    Passenger p{};
    p.luggage_count = luggage_counts[i];

    // Заполняем багаж пассажира
    for (int j = 0; j < p.luggage_count && j < 10; ++j) {
      std::strncpy(p.luggage[j].name, luggage_data[i][j].first.c_str(), sizeof(p.luggage[j].name) - 1);
      p.luggage[j].name[sizeof(p.luggage[j].name) - 1] = '\0';
      p.luggage[j].weight = luggage_data[i][j].second;
    }

    out.write(reinterpret_cast<char*>(&p), sizeof(Passenger));
  }

  out.close();
  return true;
}

std::pair<int, int> Binary::AnalyzePassengers(const std::string& filename) {
  int more_than_two = 0;
  std::vector<int> luggage_counts;
  
  std::ifstream in(filename, std::ios::binary);
  if (!in) {
    std::cerr << "Не удалось открыть файл для чтения";
    return {0, 0};
  }

  Passenger p{};
  while (in.read(reinterpret_cast<char*>(&p), sizeof(Passenger))) {
    if (p.luggage_count > 10) {
      std::cerr << "Некорректное количество багажа в файле\n";
      return {0, 0};
    }

    if (p.luggage_count > 2) {
      ++more_than_two;
    }
    luggage_counts.push_back(p.luggage_count);
  }

   in.close();

  int more_than_average = 0;
  if (!luggage_counts.empty()) {
    double sum = 0.0;
    for (int c : luggage_counts) {
      sum += c;
    }

    double average = sum / static_cast<double>(luggage_counts.size());

    for (int c : luggage_counts) {
      if (c > average) {
        ++more_than_average;
      }
    }
  }

  return std::make_pair(more_than_two, more_than_average);
}