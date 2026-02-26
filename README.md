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


