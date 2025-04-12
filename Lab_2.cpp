#include <iostream>
using namespace std;

int main() {
    int m, n;
    
    // Ввод размеров матрицы
    cout << "Enter the number of rows (m): ";
    cin >> m;
    cout << "Enter the number of columns (n): ";
    cin >> n;
    
    // Проверка корректности ввода
    if (m <= 0 || n <= 0) {
        cout << "Matrix dimensions must be positive!" << endl;
        return 1;
    }
    
    // Создание матрицы
    int matrix[100][100]; // Ограничим размер для простоты, можно использовать динамическую память
    
    // Ввод элементов матрицы
    cout << "Enter the matrix elements:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << "matrix[" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
    
    // Вычисление суммы нечетных элементов
    long long sum = 0; // Используем long long для больших сумм
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] % 2 != 0) { // Проверка на нечетность
                sum += matrix[i][j];
            }
        }
    }
    
    // Вывод результата
    cout << "Sum of odd elements in the matrix: " << sum << endl;
    
    return 0;
}