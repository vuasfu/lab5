# lab5
# ФИО: Булгакова Юлия Олеговна

# Постановка задач

Выполнить все задания в одном проекте в виде статических методов одного класса.
В задании 1 и 2 бинарные файлы содержат числовые данные, исходный файл необходимо заполнить
случайными данными, заполнение организовать отдельным методом.
В задании 3 бинарные файлы содержат величины типа struct, заполнение исходного файла
необходимо организовать отдельным методом.
В задании 4 в текстовом файле хранятся целые числа по одному в строке, исходный файл
необходимо заполнить случайными данными, заполнение организовать отдельным методом.
В задании 5 в текстовом файле хранятся целые числа по несколько в строке, исходный файл
необходимо заполнить случайными данными, заполнение организовать отдельным методом.
В задании 6 в текстовом файле хранится текст.

# Задание 1

Из исходного бинарного файла вычислить произведение нечетных отрицательных чисел.

1. Открыть бинарный файл для чтения.
2. Читать числа последовательно из файла.
3. Проверять каждое число: является ли оно отрицательным и нечетным.
4. Если условие выполняется, умножать на накапливаемое произведение.

Реализация

```cpp
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
```

Заполнение файла случайными числами:

```cpp
void Lab5::FillBinaryFileNumbers(const std::string& filename, int count) {
  InitializeRandom();
  std::ofstream file(filename, std::ios::binary);
  CheckFileOpen(file, filename);
  
  for (int i = 0; i < count; ++i) {
    int number = std::rand() % 201 - 100;  // числа от -100 до 100
    file.write(reinterpret_cast<const char*>(&number), sizeof(number));
  }
  file.close();
}
```

# Тестирование
<img width="517" height="173" alt="image" src="https://github.com/user-attachments/assets/58a8a4d0-28b4-40f9-9d45-79cad1ec8813" />


# Задание 2 

Скопировать элементы заданного файла в квадратную матрицу размером n×n (если элементов файла недостает, заполнить оставшиеся элементы матрицы нулями). Заменить в каждом столбце минимальный элемент максимальным и наоборот.

Реализация:
```cpp
void Lab5::Task2MatrixSwapMinMaxInColumns(const std::string& filename, int size) {
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
  
  // Заполнение матрицы
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {
      if (index < static_cast<int>(numbers.size())) {
        matrix[row][col] = numbers[index++];
      }
    }
  }
  
  // Поиск и замена min/max в каждом столбце
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
    }
  }
}
```

# Тестирование

<img width="431" height="471" alt="image" src="https://github.com/user-attachments/assets/ebe8ff63-1105-443c-8210-46ed2bb6126f" />

# Задание 3

Файл содержит сведения о пассажирах: ID пассажира, количество единиц багажа, информация о каждой единице багажа (название и вес). Найти количество пассажиров, у которых больше 2 единиц багажа, и количество пассажиров с багажом выше среднего.

1. Открыть бинарный файл для чтения.
2. Считывать структуры Passenger последовательно.
3. Вычислять общее количество багажа и среднее значение.
4. Подсчитывать пассажиров с более чем 2 единицами багажа.
5. Подсчитывать пассажиров с багажом выше среднего.

Структуры данных:

```cpp
struct BaggageItem {
  char name[50];
  double weight;
};

struct Passenger {
  int id;
  int baggage_count;
  BaggageItem items[10];
};
```

Реализация:
```cpp
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
  
  for (const auto& passenger : passengers) {
    if (passenger.baggage_count > 2) {
      passengers_more_than_two++;
    }
    if (passenger.baggage_count > average_baggage) {
      passengers_above_average++;
    }
  }
}
```

Заполнение файла случайными данными:
```cpp
void Lab5::FillBinaryFileStructures(const std::string& filename, int passenger_count) {
  InitializeRandom();
  std::ofstream file(filename, std::ios::binary);
  CheckFileOpen(file, filename);
  
  const char* baggage_types[] = {"Чемодан", "Сумка", "Рюкзак", "Коробка", "Пакет", "Чехол"};
  
  for (int p = 0; p < passenger_count; ++p) {
    Passenger passenger;
    passenger.id = p + 1;
    passenger.baggage_count = std::rand() % 6 + 1;
    
    for (int i = 0; i < passenger.baggage_count; ++i) {
      BaggageItem item;
      std::strncpy(item.name, baggage_types[std::rand() % 6], 49);
      item.weight = 0.5 + (std::rand() % 245) / 10.0;
      passenger.items[i] = item;
    }
    
    file.write(reinterpret_cast<const char*>(&passenger), sizeof(passenger));
  }
  
  file.close();
}
```

# Тестирование

<img width="348" height="347" alt="image" src="https://github.com/user-attachments/assets/6838114a-b619-441b-9d54-731fd30f685a" />

# Задание 4

Для текстового файла, содержащего целые числа по одному в строке, вычислить сумму квадратов всех чисел.

1. Открыть текстовый файл для чтения.
2. Читать числа последовательно из файла.
3. Для каждого числа вычислять его квадрат и добавлять к сумме.

Реализация:
```cpp
void Lab5::Task4SumOfSquares(const std::string& filename) {
  std::ifstream file(filename);
  CheckFileOpen(file, filename);
  
  long long sum_of_squares = 0;
  int number;
  int count = 0;
  
  while (file >> number) {
    sum_of_squares += static_cast<long long>(number) * number;
    ++count;
  }
  
  file.close();
  
  std::cout << "Прочитано " << count << " чисел." << std::endl;
  std::cout << "Сумма квадратов: " << sum_of_squares << std::endl;
}
```

Заполнение файла случайными числами:

```cpp
void Lab5::FillTextFileOneNumberPerLine(const std::string& filename, int count) {
  InitializeRandom();
  std::ofstream file(filename);
  CheckFileOpen(file, filename);
  
  for (int i = 0; i < count; ++i) {
    int number = std::rand() % 201 - 100;  // числа от -100 до 100
    file << number << std::endl;
  }
  
  file.close();
}
```

# Тестирование

<img width="470" height="164" alt="image" src="https://github.com/user-attachments/assets/0219baca-1cc9-4614-ba18-c42ad44ffcc0" />

# Задание 5

Для текстового файла, содержащего целые числа по несколько в строке, вычислить произведение всех чисел.

1. Открыть текстовый файл для чтения.
2. Читать файл построчно.
3. Для каждой строки разбивать на числа с помощью stringstream.
4. Перемножать все числа.

Реализация: 

```cpp
void Lab5::Task5ProductOfElements(const std::string& filename) {
  std::ifstream file(filename);
  CheckFileOpen(file, filename);
  
  long long product = 1;
  std::string line;
  int total_numbers = 0;
  bool first_number = true;
  
  while (std::getline(file, line)) {
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
```

Заполнение файла случайными данными:

```cpp
void Lab5::FillTextFileMultipleNumbersPerLine(const std::string& filename, int rows) {
  InitializeRandom();
  std::ofstream file(filename);
  CheckFileOpen(file, filename);
  
  for (int i = 0; i < rows; ++i) {
    int numbers_in_row = std::rand() % 5 + 1;  // от 1 до 5 чисел в строке
    for (int j = 0; j < numbers_in_row; ++j) {
      int number = std::rand() % 21 - 10;  // числа от -10 до 10
      file << number;
      if (j < numbers_in_row - 1) {
        file << " ";
      }
    }
    file << std::endl;
  }
  
  file.close();
}
```
# Тестирование

<img width="351" height="250" alt="image" src="https://github.com/user-attachments/assets/dbaa161c-b05a-4658-972e-be3700ba5ca7" />

# Задание 6

Переписать в другой файл строки, длина которых равна заданному числу m.

1. Открыть исходный текстовый файл для чтения.
2. Открыть выходной файл для записи.
3. Читать строки из исходного файла.
4. Если длина строки равна m, записывать её в выходной файл.

Реализация:

```cpp
void Lab5::Task6CopyLinesOfLengthM(const std::string& input_file,
                                   const std::string& output_file,
                                   int m) {
  std::ifstream input(input_file);
  CheckFileOpen(input, input_file);
  
  std::ofstream output(output_file);
  CheckFileOpen(output, output_file);
  
  std::string line;
  int copied_count = 0;
  
  while (std::getline(input, line)) {
    if (line.length() == m) {
      output << line << std::endl;
      ++copied_count;
    }
  }
  
  input.close();
  output.close();
  
  std::cout << "Скопировано " << copied_count << " строк." << std::endl;
}
```

Создание текстового файла для примера (ограниченное количество строк):

```cpp
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
}
```

# Тестирование

<img width="312" height="207" alt="image" src="https://github.com/user-attachments/assets/8fddba46-2756-455e-8b6a-6b15ef63b60e" />
