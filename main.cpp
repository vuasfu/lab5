#include "binary.h"
#include "text.h"

#include <iostream>
#include <limits>
#include <locale>
#include <string>
#include <vector>

namespace {

int ReadInt(const std::string& prompt) {
  int value;
  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      return value;
    }

    std::cout << "Ошибка ввода. Введите целое число.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

std::string ReadString(const std::string& prompt) {
  std::cout << prompt;
  std::string value;
  std::cin >> value;
  return value;
}

void PrintMatrix(const std::vector<std::vector<int>>& matrix) {
  if (matrix.empty()) {
    std::cout << "Матрица пуста.\n";
    return;
  }

  for (const auto& row : matrix) {
    for (int value : row) {
      std::cout << value << " ";
    }
    std::cout << "\n";
  }
}

void Task1() {
  std::string filename = ReadString("Введите имя бинарного файла: ");
  int size = ReadInt("Введите количество элементов: ");

  // Генерация и вывод чисел
  if (!Binary::FillFile(filename, size)) {
    return;
  }

  long long result = Binary::Multiplication(filename);
  std::cout << "Произведение отрицательных нечётных элементов: " << result << "\n";
}

void Task2() {
  std::string filename = ReadString("Введите имя бинарного файла: ");
  int size = ReadInt("Введите количество элементов: ");
  int n = ReadInt("Введите размер матрицы n: ");

  if (!Binary::FillFile(filename, size)) {
    return;
  }

  std::cout << "Матрица до замены min/max:\n";
  auto matrix_before = Binary::ReadMatrix(filename, n);
  PrintMatrix(matrix_before);

  auto matrix_after = Binary::MatrixSwapMinMax(filename, n);
  std::cout << "Матрица после замены min/max:\n";
  PrintMatrix(matrix_after);
}

void Task3() {
  std::string filename = ReadString("Введите имя бинарного файла: ");
  int passengers = ReadInt("Введите количество пассажиров: ");

  if (passengers <= 0) {
    std::cout << "Количество пассажиров должно быть положительным.\n";
    return;
  }

  std::vector<int> luggage_counts(passengers);
  std::vector<std::vector<std::pair<std::string, double>>> luggage_data(
      passengers);

  for (int i = 0; i < passengers; ++i) {
    int count = ReadInt("Количество единиц багажа пассажира: ");
    if (count < 0 || count > 10) {
      std::cout << "Допустимо от 0 до 10.\n";
      return;
    }

    luggage_counts[i] = count;
    luggage_data[i].resize(count);

    for (int j = 0; j < count; ++j) {
      std::string name = ReadString("Название багажа: ");
      double weight;
      std::cout << "Вес: ";
      while (!(std::cin >> weight)) {
        std::cout << "Ошибка ввода. Введите число.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }

      luggage_data[i][j] = {name, weight};
    }
  }

  if (!Binary::FillPassengers(filename, luggage_counts, luggage_data)) {
    return;
  }

  auto result = Binary::AnalyzePassengers(filename);

  std::cout << "Более двух единиц багажа: " << result.first << "\n";
  std::cout << "Количество выше среднего: " << result.second << "\n";
}

void Task4() {
  std::string filename = ReadString("Введите имя текстового файла: ");
  int size = ReadInt("Введите количество чисел: ");

  if (!Text::FillFile(filename, size)) {
    return;
  }

  int sum = Text::SumOfSquares(filename);
  std::cout << "Сумма квадратов: " << sum << "\n";
}

void Task5() {
  std::string filename = ReadString("Введите имя текстового файла: ");
  int lines = ReadInt("Введите количество строк: ");
  int per_line = ReadInt("Введите чисел в строке: ");

  if (!Text::FillFileMultiple(filename, lines, per_line)) {
    return;
  }

  long long product = Text::ProductOfElements(filename);
  std::cout << "Произведение элементов: " << product << "\n";
}

void Task6() {
  std::string input = ReadString("Введите имя исходного файла: ");
  std::string output = ReadString("Введите имя выходного файла: ");
  int m = ReadInt("Введите длину строки m: ");

  if (!Text::CopyLinesWithLength(input, output, m)) {
    return;
  }

  std::cout << "Строки успешно скопированы.\n";
}

}

int main() {
  try {
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());
    std::cin.imbue(std::locale());
    std::cerr.imbue(std::locale());
  } catch (...) {
  }

  while (true) {
    std::cout << "1. Произведение отрицательных нечётных (бинарный)\n";
    std::cout << "2. Матрица и обмен min/max (бинарный)\n";
    std::cout << "3. Анализ багажа пассажиров (бинарный)\n";
    std::cout << "4. Сумма квадратов (текстовый)\n";
    std::cout << "5. Произведение элементов (текстовый)\n";
    std::cout << "6. Копирование строк длины m (текстовый)\n";
    std::cout << "0. Выход\n";

    int choice = ReadInt("Выберите пункт: ");

    switch (choice) {
      case 1:
        Task1();
        break;
      case 2:
        Task2();
        break;
      case 3:
        Task3();
        break;
      case 4:
        Task4();
        break;
      case 5:
        Task5();
        break;
      case 6:
        Task6();
        break;
      case 0:
        return 0;
      default:
        std::cout << "Неверный пункт меню.\n";
    }
  }
}