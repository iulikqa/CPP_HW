#include <iostream>
using namespace std;

int main() {
    int n;
    long long product = 1; // Используем long long для больших чисел

    // Ввод числа n
    cout << "Enter a number n :";
    cin >> n;

    // Проверка на корректность ввода
    if (n < 1) {
        cout << " The number must be positive!" << endl;
        return 1;
    }

    // Вычисление произведения нечетных чисел
    for (int i = 1; i <= n; i += 2) {
        product *= i;
    }

    // Вывод результата
    cout << "The product of odd numbers from 1 to " << n << " equal: " << product << endl;

    return 0;
}