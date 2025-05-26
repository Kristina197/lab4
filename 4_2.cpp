#include <iostream>
#include <vector>
#include <algorithm>
#include <random>       
#include <iomanip>      

using namespace std;

// Генератор случайных чисел (использует аппаратный генератор для инициализации)
minstd_rand generator(random_device{}());

// Функция для генерации случайного целого числа в диапазоне [min, max]
int randomInt(int min, int max) {
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

// Создает и выводит массив из n случайных чисел
vector<int> mas(int n) {
    vector<int> arr(n);
    // Заполнение массива случайными числами
    for (int i = 0; i < n; ++i) {
        arr[i] = randomInt(10, 100);
    }

    // Вывод массива с форматированием (8 чисел в строке)
    cout << "1. Исходный массив (" << n << " элементов):\n";
    for (int i = 0; i < n; ++i) {
        cout << setw(4) << arr[i];
        if ((i + 1) % 8 == 0 || i == n - 1) cout << endl;
    }
    return arr;
}

// Находит два наименьших элемента и сумму остатков от деления всех элементов на минимальный
void min_elements(const vector<int>& arr) {
    int min1 = 101, min2 = 101; // Инициализация 101, тк в массиве числа в диапозоне до 100
    
    // Поиск двух наименьших элементов
    for (int num : arr) {
        if (num < min1) {
            min2 = min1;
            min1 = num;
        } else if (num < min2 && num != min1) {
            min2 = num;
        }
    }

    // Вычисление суммы остатков от деления на минимальный элемент
    int sum = 0;
    for (int num : arr) {
        sum += num % min1;
    }

    cout << "\n2. Два наименьших элемента: " << min1 << " и " << min2 << endl;
    cout << "   Сумма остатков от деления на " << min1 << ": " << sum << endl;
}

// Находит самую длинную возрастающую последовательность в массиве
void longest_sequence(const vector<int>& arr) {
    vector<int> longest, current; // Текущая и самая длинная последовательности
    
    for (size_t i = 0; i < arr.size(); ++i) {
        // Если последовательность продолжает расти
        if (i == 0 || arr[i] > arr[i-1]) {
            current.push_back(arr[i]);
        } else {
            // Если текущая последовательность длиннее найденной
            if (current.size() > longest.size()) longest = current;
            current = {arr[i]}; // Начинаем новую последовательность
        }
    }
    // Проверка последней последовательности
    if (current.size() > longest.size()) longest = current;

    // Вывод результата
    cout << "\n3. Самая длинная возрастающая последовательность (" 
         << longest.size() << " элементов):\n";
    for (size_t i = 0; i < longest.size(); ++i) {
        cout << setw(4) << longest[i];
        if ((i + 1) % 8 == 0 || i == longest.size() - 1) cout << endl;
    }
}

// Выводит числа по специальному шаблону
void special_print(int N) {
    const int start = 2000;      // Начальное значение
    const int step = 10;         // Шаг между элементами
    const int el_line = 8;       // Элементов в строке
    const int totalElements = N * el_line; // Всего элементов
    
    // Создание массива чисел
    vector<int> arr(totalElements);
    for (int i = 0; i < totalElements; ++i) {
        arr[i] = start + i * step;
    }

    cout << "\n4. Вывод по специальному шаблону (N = " << N << "):\n";

    // Первый вариант вывода
    cout << "Вывод 1:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < el_line; ++j) {
            cout << setw(5) << arr[i * el_line + j];
        }
        cout << endl;
    }

    // Второй вариант вывода 
    cout << "\nВывод 2:\n";
    vector<int> sortedArr = arr;
    // Сортировка по убыванию
    sort(sortedArr.begin(), sortedArr.end(), greater<int>());
    
    for (int i = 0; i < N; ++i) {
        if (i % 2 == 1) { // Четные строки (индексация с 0) - по возрастанию
            for (int j = 0; j < el_line; ++j) {
                cout << setw(5) << sortedArr[i * el_line + j];
            }
        } else { // Нечетные строки - по убыванию
            for (int j = el_line - 1; j >= 0; --j) {
                cout << setw(5) << sortedArr[i * el_line + j];
            }
        }
        cout << endl;
    }
}

int main() {
    // Ввод длины массива с проверкой (n >= 10)
    int n;
    do {
        cout << "Введите длину массива (n >= 10): ";
        cin >> n;
    } while (n < 10);

    // Создание и обработка массива
    vector<int> arr = mas(n);
    min_elements(arr);
    longest_sequence(arr);

    // Дополнительное задание с выводом по шаблону
    int N;
    cout << "\nВведите N для задания 4: ";
    cin >> N;
    special_print(N);

    return 0;
}