#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Функция уравнения: f(x) = x * ln(x + 2) - 2
double f(double x) {
    return x * log(x + 2) - 2;
}

// Производная функции: f'(x) = ln(x + 2) + x / (x + 2)
double df(double x) {
    return log(x + 2) + x / (x + 2);
}

// Метод половинного деления для нахождения корня уравнения на интервале [a, b]
void bisection(double a, double b, double e) {
    cout << "Метод половинного деления:\n";
    cout << "N\t a_n\t\t b_n\t\t b_n - a_n\n";
    int n = 0;          // Счетчик итераций
    double c;           // Точка деления интервала
    
    // Продолжаем, пока длина интервала больше заданной точности
    while (b - a > e) {
        c = (a + b) / 2;  // Находим середину интервала
        cout << n << "\t " << fixed << setprecision(6) << a << "\t " << b << "\t " << b - a << endl;
        
        // Если значение функции в точке c равно 0, корень найден
        if (f(c) == 0) break;
        
        // Выбираем новый интервал в зависимости от знака функции
        if (f(a) * f(c) < 0) b = c;  // Корень в левой половине
        else a = c;                   // Корень в правой половине
        n++;
    }
    cout << "Корень: " << c << endl << endl;
}

// Метод Ньютона
void newton(double x0, double e) {
    cout << "Метод Ньютона:\n";
    cout << "N\t X_n\t\t X_{n+1}\t\t X_{n+1} - X_n\n";
    int n = 0;          // Счетчик итераций
    double x1;          // Новое приближение
    
    do {
        // Формула метода Ньютона: x_{n+1} = x_n - f(x_n)/f'(x_n)
        x1 = x0 - f(x0) / df(x0);
        cout << n << "\t " << fixed << setprecision(6) << x0 << "\t " << x1 << "\t " << abs(x1 - x0) << endl;
        
        // Проверяем условие выхода (достижение заданной точности)
        if (abs(x1 - x0) < e) break;
        
        x0 = x1;        // Обновляем текущее приближение
        n++;
    } while (n < 1000); // Защита от бесконечного цикла
    cout << "Корень: " << x1 << endl << endl;
}

// Метод простых итераций 
// Уравнение x = 2 / ln(x + 2)
void simpleIteration(double x0, double e) {
    cout << "Метод простых итераций:\n";
    cout << "N\t X_n\t\t X_{n+1}\t\t X_{n+1} - X_n\n";
    int n = 0;          // Счетчик итераций
    double x1;          // Новое приближение
    
    const int max_iter = 100; // Максимальное число итераций
    
    do {
        double denom = log(x0 + 2); // Знаменатель: ln(x0 + 2)
        
        // Проверка на деление на ноль или очень маленькое значение
        if (abs(denom) < 1e-10) {
            cerr << "Ошибка: Деление на ноль или почти ноль (x_n = " << x0 << ")\n";
            return;
        }
        
        // Итерационная формула: x_{n+1} = 2 / ln(x_n + 2)
        x1 = 2 / denom;
        cout << n << "\t " << fixed << setprecision(6) << x0 << "\t " << x1 << "\t " << abs(x1 - x0) << endl;
        
        // Проверяем условие выхода (достижение заданной точности)
        if (abs(x1 - x0) < e) break;
        
        x0 = x1;        // Обновляем текущее приближение
        n++;
        
        // Защита от бесконечного цикла
        if (n >= max_iter) {
            cerr << "Ошибка: Превышено максимальное число итераций\n";
            return;
        }
    } while (true);
    cout << "Корень: " << x1 << endl << endl;
}

// Метод простых итераций для отрицательного корня
void simpleIterationN(double x0, double e) {
    cout << "Метод простых итераций (отрицательный корень):\n";
    cout << "N\t X_n\t\t X_{n+1}\t\t X_{n+1} - X_n\n";
    int n = 0;          // Счетчик итераций
    double x1;          // Новое приближение
    
    const int max_iter = 100; // Максимальное число итераций
    
    do {
        // Итерационная формула: x_{n+1} = exp(2 / x_n) - 2
        x1 = exp(2 / x0) - 2;
        
        cout << n << "\t " << fixed << setprecision(6) << x0 << "\t " << x1 << "\t " << abs(x1 - x0) << endl;
        
        // Проверяем условие выхода (достижение заданной точности)
        if (abs(x1 - x0) < e) break;
        
        x0 = x1;        // Обновляем текущее приближение
        n++;
        
        // Защита от бесконечного цикла
        if (n >= max_iter) {
            cerr << "Ошибка: Превышено максимальное число итераций\n";
            return;
        }
    } while (true);
    cout << "Корень: " << x1 << endl << endl;
}
int main() {
    double e = 1e-4;  // Точность вычислений

    // Метод половинного деления на интервале [1, 2] и [-2, -1]
    bisection(1.0, 2.0, e);
    bisection(-2.0, -1.0, e);

    // Метод Ньютона с начальным приближением x0 = 1.5 и x0 = 1.5
    newton(1.5, e);
    newton(-1.5, e);

    // Метод простых итераций с начальным приближением x0 = 1.5
    simpleIteration(1.5, e);
    simpleIterationN(-1.5, e); 

    return 0;
}