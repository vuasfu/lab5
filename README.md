# lab5
# ФИО: Булгакова Юлия Олеговна

# Постановка задач

Выполнить все задания в одном проекте в виде статических методов одного класса.
В задании 1 и 2 бинарные файлы, содержат числовые данные, исходный файл необходимо заполнить
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

1. Открыть бинарный файл для чтения в режиме std::ios::binary.
2. Последовательно считывать числа типа int через метод read.
3. Проверять каждое число: является ли оно отрицательным (num < 0) и нечетным (num % 2 != 0).
4. Если условия выполнены, умножать число на накапливаемую переменную произведения.
5. Вывести результат или 0, если подходящих чисел не найдено.

Реализация

```cpp
bool Binary::FillFile(const std::string& filename, int size) {
    if (size <= 0) {
      std::cerr << "Неправильные параметры для заполнения файла";
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
```

# Тестирование
<img width="377" height="90" alt="image" src="https://github.com/user-attachments/assets/3bf2298e-2129-4076-9f97-19645d877fa3" />
<img width="380" height="93" alt="image" src="https://github.com/user-attachments/assets/ca57be06-27e9-40f1-afa3-371346482ae2" />


# Задание 2

Скопировать элементы заданного файла в квадратную матрицу размером n×n. Заменить в каждом столбце минимальный элемент максимальным и наоборот.

1. Считать все числа из бинарного файла.
2. Заполнить матрицу n×n (если чисел меньше, оставить нули).
3. В каждом столбце найти индексы минимального и максимального элементов.
4. Выполнить обмен значений с помощью std::swap.

Реализация
```cpp
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
```

# Тестирование
<img width="361" height="225" alt="image" src="https://github.com/user-attachments/assets/477119e4-9941-489e-bfcd-9847e559b641" />




# Задание 3
Файл содержит сведения о пассажирах: количество единиц багажа, информация о каждой единице багажа (название и вес). Найти количество пассажиров, у которых больше 2 единиц багажа, и количество пассажиров с багажом выше среднего.

1. Определить структуры Luggage и Passenger.
2. Заполнить файл данными, введенными пользователем.
3. Считать все структуры из бинарного файла.
4. Подсчитать пассажиров с багажом > 2.
5. Вычислить среднее количество багажа и подсчитать пассажиров выше среднего.

Структуры данных

```cpp
namespace {
  struct Luggage {
    char name[20];
    double weight;
  };

  struct Passenger {
    int luggage_count;
    Luggage luggage[10];
  };
}
```

Реализация

```cpp
bool Binary::FillPassengers(
    const std::string& filename,
    const std::vector<int>& luggage_counts,
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
```

# Тестирование 

<img width="326" height="296" alt="image" src="https://github.com/user-attachments/assets/ad664d6a-c98d-4c90-b350-42c6eaed61e3" />


# Задание 4
Для текстового файла, содержащего целые числа по одному в строке, вычислить сумму квадратов всех чисел.

1. Заполнить файл случайными числами.
2. Открыть файл для чтения.
3. Читать числа через оператор >>.
4. Каждое число возвести в квадрат и прибавить к сумме.

Реализация

```cpp
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

  for (int i = 0; i < size; ++i) {
    int number = dis(gen);
    out << number << "\n";
  }

  out.close();
  return true;
}

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
```

# Тестирование
<img width="257" height="91" alt="image" src="https://github.com/user-attachments/assets/b179b033-325a-48b7-9238-492a34de2f9d" />

# Задание 5
Для текстового файла, содержащего целые числа по несколько в строке, вычислить произведение всех чисел.

1. Заполнить файл числами по несколько в строке.
2. Читать файл построчно через std::getline.
3. Использовать std::istringstream для разбора строки.
4. Перемножать все числа.

Реализация

```cpp
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

  for (int i = 0; i < lines; ++i) {
    for (int j = 0; j < numbers_per_line; ++j) {
      int number = dis(gen);
      out << number;
      if (j != numbers_per_line - 1) {
        out << " ";
      }
    }
    out << "\n";
  }

  out.close();
  return true;
}

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
```

# Тестирование
<img width="293" height="159" alt="image" src="https://github.com/user-attachments/assets/f2127a19-d569-4efd-87a1-b26edcde2cee" />

# Задание 6
Переписать в другой файл строки, длина которых равна заданному числу m.

1. Открыть исходный файл для чтения и целевой для записи.
2. Читать файл построчно через std::getline.
3. Проверять длину каждой строки.
4. Если длина равна m, записывать в выходной файл.

Реализация

```cpp
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
```


# Тестирование
<img width="152" height="176" alt="image" src="https://github.com/user-attachments/assets/ef4723d9-0fb2-47b6-b19c-40b6b3c66db9" />
<img width="275" height="86" alt="image" src="https://github.com/user-attachments/assets/90b8e71c-ee7b-4a74-8002-56b8f71aea91" />
<img width="143" height="132" alt="image" src="https://github.com/user-attachments/assets/eee7bd71-7559-437e-9997-024586a4870f" />

