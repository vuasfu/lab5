#include "lab5.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#include <stdexcept>

namespace {
bool random_initialized = false;

// Структуры
struct BaggageItem {
  char name[50];
  double weight;
};

struct Passenger {
  int id;
  int baggage_count;
  BaggageItem items[10];
};

// Вспомогательные функции для проверок
inline void CheckFileOpen(const std::ios& stream, const std::string& filename) {
  if (!stream) {
    throw std::runtime_error("Ошибка открытия файла: " + filename);
  }
}

inline void CheckPositive(int value, const std::string& param_name) {
  if (value <= 0) {
    throw std::runtime_error(param_name + " должно быть положительным");
  }
}

inline void CheckNonNegative(int value, const std::string& param_name) {
  if (value < 0) {
    throw std::runtime_error(param_name + " должно быть неотрицательным");
  }
}

inline void CheckRange(int value, int min, int max, const std::string& param_name) {
  if (value < min || value > max) {
    throw std::runtime_error(param_name + " должно быть в диапазоне [" + 
                            std::to_string(min) + ", " + std::to_string(max) + "]");
  }
}
}  // namespace

void Lab5::InitializeRandom() {
  if (!random_initialized) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    random_initialized = true;
  }
}

// Задание 1: Произведение нечетных отрицательных чисел 
void Lab5::FillBinaryFileNumbers(const std::string& filename, int count) {
  CheckPositive(count, "Количество чисел");
  
  InitializeRandom();
  std::ofstream file(filename, std::ios::binary);
  CheckFileOpen(file, filename);
  
  for (int i = 0; i < count; ++i) {
    int number = std::rand() % 201 - 100;
    file.write(reinterpret_cast<const char*>(&number), sizeof(number));
  }
  file.close();
  std::cout << "Файл " << filename << " заполнен " << count
            << " случайными числами." << std::endl;
}

void Lab5::Task1ProductOddNegative(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary);
  CheckFileOpen(file, filename);
  
  long long product = 1;
  bool found = false;
  int count = 0;
  int number;
  
  std::cout << "Содержимое файла:" << std::endl;
  while (file.read(reinterpret_cast<char*>(&number), sizeof(number))) {
    std::cout << number << " ";
    if (number < 0 && number % 2 != 0) {
      product *= number;
      found = true;
      ++count;
    }
  }
  std::cout << std::endl;
  file.close();
  
  if (found) {
    std::cout << "Найдено " << count << " нечетных отрицательных чисел." << std::endl;
    std::cout << "Их произведение: " << product << std::endl;
  } else {
    std::cout << "Нечетных отрицательных чисел не найдено." << std::endl;
  }
}

// Задание 2: Матрица - замена min/max в столбцах
void Lab5::Task2MatrixSwapMinMaxInColumns(const std::string& filename, int size) {
  CheckRange(size, 1, 100, "Размер матрицы");
  
  std::ifstream file(filename, std::ios::binary);
  CheckFileOpen(file, filename);
  
  std::vector<int> numbers;
  int number;
  while (file.read(reinterpret_cast<char*>(&number), sizeof(number))) {
    numbers.push_back(number);
  }
  file.close();
  
  if (numbers.empty()) {
    std::cout << "Файл пуст." << std::endl;
    return;
  }
  
  std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
  int index = 0;
  
  std::cout << "Исходная матрица " << size << "x" << size << ":" << std::endl;
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {
      if (index < static_cast<int>(numbers.size())) {
        matrix[row][col] = numbers[index++];
      }
      std::cout << std::setw(5) << matrix[row][col];
    }
    std::cout << std::endl;
  }
  
  for (int col = 0; col < size; ++col) {
    int min_row = 0, max_row = 0;
    int min_val = matrix[0][col];
    int max_val = matrix[0][col];
    
    for (int row = 1; row < size; ++row) {
      if (matrix[row][col] < min_val) {
        min_val = matrix[row][col];
        min_row = row;
      }
      if (matrix[row][col] > max_val) {
        max_val = matrix[row][col];
        max_row = row;
      }
    }
    
    if (min_row != max_row) {
      std::swap(matrix[min_row][col], matrix[max_row][col]);
      std::cout << "Поменяли местами минимум и максимум в столбце " 
                << (col + 1) << std::endl;
    }
  }
  
  std::cout << "\nМатрица после замены минимума и максимума в каждом столбце:" << std::endl;
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {
      std::cout << std::setw(5) << matrix[row][col];
    }
    std::cout << std::endl;
  }
}

// Задание 3: Анализ багажа пассажиров
void Lab5::FillBinaryFileStructures(const std::string& filename, int passenger_count) {
  CheckRange(passenger_count, 1, 1000, "Количество пассажиров");
  
  InitializeRandom();
  std::ofstream file(filename, std::ios::binary);
  CheckFileOpen(file, filename);
  
  const char* baggage_types[] = {"Чемодан", "Сумка", "Рюкзак", "Коробка", "Пакет", "Чехол"};
  const int types_count = 6;
  
  for (int p = 0; p < passenger_count; ++p) {
    Passenger passenger;
    passenger.id = p + 1;
    passenger.baggage_count = std::rand() % 6 + 1;
    
    for (int i = 0; i < passenger.baggage_count; ++i) {
      BaggageItem item;
      std::strncpy(item.name, baggage_types[std::rand() % types_count], 49);
      item.name[49] = '\0';
      item.weight = 0.5 + (std::rand() % 245) / 10.0;
      
      passenger.items[i] = item;
    }
    
    file.write(reinterpret_cast<const char*>(&passenger), sizeof(passenger));
  }
  
  file.close();
  std::cout << "Файл " << filename << " заполнен данными о " 
            << passenger_count << " пассажирах." << std::endl;
}

void Lab5::Task3BaggageAnalysis(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary);
  CheckFileOpen(file, filename);
  
  std::vector<Passenger> passengers;
  int total_baggage = 0;
  
  while (!file.eof()) {
    Passenger passenger;
    file.read(reinterpret_cast<char*>(&passenger), sizeof(passenger));
    if (file.gcount() == sizeof(passenger)) {
      passengers.push_back(passenger);
      total_baggage += passenger.baggage_count;
    }
  }
  file.close();
  
  if (passengers.empty()) {
    std::cout << "Файл не содержит данных о пассажирах." << std::endl;
    return;
  }
  
  double average_baggage = static_cast<double>(total_baggage) / passengers.size();
  
  int passengers_more_than_two = 0;
  int passengers_above_average = 0;
  
  std::cout << "Данные о пассажирах:" << std::endl;

  for (const auto& passenger : passengers) {
    std::cout << "Пассажир " << passenger.id << ": " 
              << passenger.baggage_count << " единиц багажа" << std::endl;
    
    if (passenger.baggage_count > 2) {
      passengers_more_than_two++;
    }
    if (passenger.baggage_count > average_baggage) {
      passengers_above_average++;
    }
  }
  
  std::cout << "\nСтатистика:" << std::endl;
  std::cout << "Всего пассажиров: " << passengers.size() << std::endl;
  std::cout << "Всего единиц багажа: " << total_baggage << std::endl;
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Среднее количество багажа: " << average_baggage << std::endl;
  std::cout << "Пассажиров с более чем 2 единицами багажа: " << passengers_more_than_two << std::endl;
  std::cout << "Пассажиров с багажом выше среднего: " << passengers_above_average << std::endl;
}

// Задание 4: Сумма квадратов элементов
void Lab5::FillTextFileOneNumberPerLine(const std::string& filename, int count) {
  CheckPositive(count, "Количество чисел");
  
  InitializeRandom();
  std::ofstream file(filename);
  CheckFileOpen(file, filename);
  
  for (int i = 0; i < count; ++i) {
    int number = std::rand() % 201 - 100;
    file << number << std::endl;
  }
  
  file.close();
  std::cout << "Текстовый файл " << filename << " заполнен " << count 
            << " числами (по одному в строке)." << std::endl;
}

void Lab5::Task4SumOfSquares(const std::string& filename) {
  std::ifstream file(filename);
  CheckFileOpen(file, filename);
  
  long long sum_of_squares = 0;
  int number;
  int count = 0;
  
  std::cout << "Числа из файла:" << std::endl;
  while (file >> number) {
    std::cout << number << " ";
    sum_of_squares += static_cast<long long>(number) * number;
    ++count;
  }
  std::cout << std::endl;
  
  file.close();
  
  std::cout << "Прочитано " << count << " чисел." << std::endl;
  std::cout << "Сумма квадратов: " << sum_of_squares << std::endl;
}

// Задание 5: Произведение элементов
void Lab5::FillTextFileMultipleNumbersPerLine(const std::string& filename, int rows) {
  CheckPositive(rows, "Количество строк");
  
  InitializeRandom();
  std::ofstream file(filename);
  CheckFileOpen(file, filename);
  
  for (int i = 0; i < rows; ++i) {
    int numbers_in_row = std::rand() % 5 + 1;
    for (int j = 0; j < numbers_in_row; ++j) {
      int number = std::rand() % 21 - 10;
      file << number;
      if (j < numbers_in_row - 1) {
        file << " ";
      }
    }
    file << std::endl;
  }
  
  file.close();
  std::cout << "Текстовый файл " << filename << " заполнен." << std::endl;
}

void Lab5::Task5ProductOfElements(const std::string& filename) {
  std::ifstream file(filename);
  CheckFileOpen(file, filename);
  
  long long product = 1;
  std::string line;
  int total_numbers = 0;
  bool first_number = true;
  
  std::cout << "Содержимое файла:" << std::endl;
  while (std::getline(file, line)) {
    std::cout << line << std::endl;
    std::istringstream stream(line);
    int number;
    
    while (stream >> number) {
      if (first_number) {
        product = number;
        first_number = false;
      } else {
        product *= number;
      }
      ++total_numbers;
    }
  }
  
  file.close();
  
  if (total_numbers == 0) {
    std::cout << "Файл пуст." << std::endl;
  } else {
    std::cout << "Всего чисел: " << total_numbers << std::endl;
    std::cout << "Произведение всех чисел: " << product << std::endl;
  }
}

// Задание 6: Копирование строк заданной длины m
void Lab5::FillTextFileText(const std::string& filename) {
  std::ofstream file(filename);
  CheckFileOpen(file, filename);
  
  file << "a" << std::endl;
  file << "ab" << std::endl;
  file << "abc" << std::endl;
  file << "abcd" << std::endl;
  file << "abcde" << std::endl;
  file << "abcdef" << std::endl;
  file << "abcdefg" << std::endl;
  file << "abcdefgh" << std::endl;
  file << "abcdefghi" << std::endl;
  file << "abcdefghij" << std::endl;
  
  file.close();
  std::cout << "Текстовый файл " << filename << " создан." << std::endl;
}

void Lab5::Task6CopyLinesOfLengthM(const std::string& input_file,
                                   const std::string& output_file,
                                   int m) {
  CheckNonNegative(m, "Длина строки");
  
  std::ifstream input(input_file);
  CheckFileOpen(input, input_file);
  
  std::ofstream output(output_file);
  CheckFileOpen(output, output_file);
  
  std::string line;
  int copied_count = 0;
  
  std::cout << "Копируем строки длиной " << m << " символов:" << std::endl;
  
  while (std::getline(input, line)) {
    if (line.length() == m) {
      output << line << std::endl;
      ++copied_count;
      std::cout << "Скопировано: \"" << line << "\" (длина: " 
                << line.length() << ")" << std::endl;
    }
  }
  
  input.close();
  output.close();
  
  std::cout << "Скопировано " << copied_count << " строк." << std::endl;
  std::cout << "Результат записан в файл: " << output_file << std::endl;
}

// Вспомогательные методы
void Lab5::ShowBinaryFileContents(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary);
  CheckFileOpen(file, filename);
  
  std::cout << "Содержимое бинарного файла " << filename << ":" << std::endl;
  int number;
  int count = 0;
  while (file.read(reinterpret_cast<char*>(&number), sizeof(number))) {
    std::cout << std::setw(6) << number;
    ++count;
    if (count % 10 == 0) std::cout << std::endl;
  }
  if (count % 10 != 0) std::cout << std::endl;
  std::cout << "Всего чисел: " << count << std::endl;
  file.close();
}

void Lab5::ShowTextFileContents(const std::string& filename) {
  std::ifstream file(filename);
  CheckFileOpen(file, filename);
  
  std::cout << "Содержимое текстового файла " << filename << ":" << std::endl;
  std::string line;
  int line_number = 1;
  while (std::getline(file, line)) {
    std::cout << std::setw(3) << line_number << ": " << line 
              << " (длина: " << line.length() << ")" << std::endl;
    ++line_number;
  }
  file.close();
}