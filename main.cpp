#include "lab5.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <cctype>

#ifdef _WIN32
#include <cstdio>
#endif

void SetupConsoleEncoding() {
#ifdef _WIN32
  // Команда для установки UTF-8 в Windows консоли
  system("chcp 65001 > nul");
#else
  // Для Linux/Mac
  std::setlocale(LC_ALL, "ru_RU.UTF-8");
#endif
}

void ClearInputBuffer() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int GetIntInput(const std::string& prompt) {
  int value;
  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      ClearInputBuffer();
      return value;
    } else {
      std::cout << "Неверный ввод. Пожалуйста, введите целое число." << std::endl;
      ClearInputBuffer();
    }
  }
}

int GetIntInputWithRange(const std::string& prompt, int min, int max) {
  int value;
  while (true) {
    value = GetIntInput(prompt);
    if (value >= min && value <= max) {
      return value;
    } else {
      std::cout << "Неверный диапазон. Введите число от " << min 
                << " до " << max << "." << std::endl;
    }
  }
}

char GetCharInput(const std::string& prompt) {
  std::string input;
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, input);
    if (!input.empty()) {
      return std::tolower(input[0]);
    }
  }
}

void ShowMenu() {
  std::cout << "\n     ЛАБОРАТОРНАЯ РАБОТА №5: ФАЙЛЫ" << std::endl;
  std::cout << "1. Задание 1: Произведение нечетных отрицательных чисел" << std::endl;
  std::cout << "2. Задание 2: Матрица - замена min/max в столбцах" << std::endl;
  std::cout << "3. Задание 3: Анализ багажа пассажиров" << std::endl;
  std::cout << "4. Задание 4: Сумма квадратов элементов" << std::endl;
  std::cout << "5. Задание 5: Произведение элементов" << std::endl;
  std::cout << "6. Задание 6: Копирование строк заданной длины m" << std::endl;
  std::cout << "0. Выход" << std::endl;
}

int main() {
  SetupConsoleEncoding();

  int choice;
  std::string filename;

  do {
    ShowMenu();
    choice = GetIntInputWithRange("Выберите задание: ", 0, 6);

    switch (choice) {
      case 1: {
        std::cout << "\nЗадание 1" << std::endl;
        std::cout << "Произведение нечетных отрицательных чисел" << std::endl;
        std::cout << "Введите имя бинарного файла: ";
        std::getline(std::cin, filename);

        char answer = GetCharInput("Заполнить файл случайными числами? (y/n): ");
        
        if (answer == 'y') {
          int count = GetIntInputWithRange("Сколько чисел сгенерировать? (по умолчанию 20): ", 1, 1000);
          Lab5::FillBinaryFileNumbers(filename, count);
        }

        Lab5::Task1ProductOddNegative(filename);
        break;
      }

      case 2: {
        std::cout << "\nЗадание 2" << std::endl;
        std::cout << "Матрица - замена min и max в столбцах" << std::endl;
        std::cout << "Введите имя бинарного файла: ";
        std::getline(std::cin, filename);

        char answer = GetCharInput("Заполнить файл случайными числами? (y/n): ");
        
        if (answer == 'y') {
          Lab5::FillBinaryFileNumbers(filename, 25);
        }

        int size = GetIntInputWithRange("Введите размер матрицы (1-10): ", 1, 10);
        
        Lab5::Task2MatrixSwapMinMaxInColumns(filename, size);
        break;
      }

      case 3: {
        std::cout << "\nЗадание 3" << std::endl;
        std::cout << "Анализ багажа пассажиров" << std::endl;
        std::cout << "Введите имя бинарного файла: ";
        std::getline(std::cin, filename);

        char answer = GetCharInput("Заполнить файл случайными данными? (y/n): ");
        
        if (answer == 'y') {
          int count = GetIntInputWithRange("Сколько пассажиров сгенерировать? (по умолчанию 8): ", 1, 100);
          Lab5::FillBinaryFileStructures(filename, count);
        }

        Lab5::Task3BaggageAnalysis(filename);
        break;
      }

      case 4: {
        std::cout << "\nЗадание 4" << std::endl;
        std::cout << "Сумма квадратов элементов" << std::endl;
        std::cout << "Введите имя текстового файла: ";
        std::getline(std::cin, filename);

        char answer = GetCharInput("Заполнить файл случайными числами? (y/n): ");
        
        if (answer == 'y') {
          int count = GetIntInputWithRange("Сколько чисел сгенерировать? (по умолчанию 15): ", 1, 1000);
          Lab5::FillTextFileOneNumberPerLine(filename, count);
        }

        Lab5::Task4SumOfSquares(filename);
        break;
      }

      case 5: {
        std::cout << "\nЗадание 5" << std::endl;
        std::cout << "Произведение элементов" << std::endl;
        std::cout << "Введите имя текстового файла: ";
        std::getline(std::cin, filename);

        char answer = GetCharInput("Заполнить файл случайными числами? (y/n): ");
        
        if (answer == 'y') {
          int rows = GetIntInputWithRange("Сколько строк сгенерировать? (по умолчанию 6): ", 1, 100);
          Lab5::FillTextFileMultipleNumbersPerLine(filename, rows);
        }

        Lab5::Task5ProductOfElements(filename);
        break;
      }

      case 6: {
        std::cout << "\nЗадание 6" << std::endl;
        std::cout << "Копирование строк заданной длины m" << std::endl;

        std::string input_file;
        std::string output_file;

        std::cout << "Введите имя исходного файла: ";
        std::getline(std::cin, input_file);

        char answer = GetCharInput("Создать тестовый файл с текстом? (y/n): ");
        
        if (answer == 'y') {
          Lab5::FillTextFileText(input_file);
        }

        std::cout << "Введите имя выходного файла: ";
        std::getline(std::cin, output_file);

        int length_m = GetIntInputWithRange("Введите длину строк для копирования (m): ", 0, 100);
        
        Lab5::Task6CopyLinesOfLengthM(input_file, output_file, length_m);
        break;
      }

      case 0: {
        std::cout << "\nВыход из программы." << std::endl;
        break;
      }
    }

    if (choice != 0) {
      std::cout << "\nНажмите Enter для продолжения...";
      ClearInputBuffer();
    }

  } while (choice != 0);

  return 0;
}