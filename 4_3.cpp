#include <iostream>
#include <cmath>

using namespace std;

// Проверка, является ли число простым
bool isPrime(int n) {
    if (n <= 1) return false;       // 1 и меньше не являются простыми
    if (n <= 3) return true;        // 2 и 3 - простые
    if (n % 2 == 0 || n % 3 == 0) return false;  // Исключаем четные и кратные 3
    
    // Проверяем делители до √n с шагом 6 (оптимизация)
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

//Проверка, что число ≡ 3 mod 4 (удовлетворяет условию для BBS)
 
bool isCongruent3Mod4(int n) {
    return (n % 4) == 3;
}

//Вычисляем наибольший общий делитель (НОД) двух чисел
int nod(int a, int b) {
    while (b != 0) {  // Алгоритм Евклида
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void bbsGenerator(int p, int q, int x, int count) {
    // Проверка условий для p и q
    if (!isPrime(p)) {
        cout << "Ошибка: p должно быть простым числом" << endl;
        return;
    }
    if (!isPrime(q)) {
        cout << "Ошибка: q должно быть простым числом" << endl;
        return;
    }
    if (!isCongruent3Mod4(p) || !isCongruent3Mod4(q)) {
        cout << "Ошибка: p и q должны быть ≡ 3 mod 4" << endl;
        return;
    }
    
    int M = p * q;  // Модуль для генерации
    
    // Проверка взаимной простоты x и M
    if (nod(x, M) != 1) {
        cout << "Ошибка: x должно быть взаимно просто с M (НОД(x, M) = 1)" << endl;
        return;
    }
    
    // Инициализация генератора
    cout << "Последовательность псевдослучайных чисел:" << endl;
    int current = (x * x) % M;  // x0 = x^2 mod M
    cout << current << " ";     // Выводим x0
    
    // Генерация последующих чисел
    for (int i = 1; i < count; ++i) {
        current = (current * current) % M;  // xn = xn-1 mod M
        cout << current << " ";
    }
    cout << endl;
}

int main() {
    int p, q, x, count;
    
    // Ввод параметров
    cout << "Введите простое число p (≡ 3 mod 4): ";
    cin >> p;
    
    cout << "Введите простое число q (≡ 3 mod 4): ";
    cin >> q;
    
    cout << "Введите начальное значение x (взаимно простое с p*q): ";
    cin >> x;
    
    cout << "Введите количество генерируемых чисел: ";
    cin >> count;
    
    // Генерация и вывод последовательности
    cout << "\nРезультат:" << endl;
    bbsGenerator(p, q, x, count);
    
    return 0;
}