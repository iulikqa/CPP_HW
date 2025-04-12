#include <iostream>
#include <string>
#include <algorithm> // Для сортировки
using namespace std;

// Определение структуры для автомобиля
struct Car {
    int number;          // Номер автомобиля
    string brand;        // Марка
    string model;        // Модель
    string color;        // Цвет
    string country;      // Страна
    double price;        // Цена
};

// Функция для вывода одного автомобиля
void printCar(const Car& car) {
    cout << "Number: " << car.number << ", Brand: " << car.brand 
         << ", Model: " << car.model << ", Color: " << car.color 
         << ", Country: " << car.country << ", Price: $" << car.price << endl;
}

int main() {
    const int MAX_CARS = 100; // Максимальный размер массива
    Car cars[MAX_CARS];       // Массив структур
    int carCount = 0;         // Текущее количество автомобилей
    int choice;

    do {
        // Вывод меню
        cout << "\n=== Car Dealership Menu ===\n";
        cout << "1. Create array of cars\n";
        cout << "2. Display all cars\n";
        cout << "3. Add a car\n";
        cout << "4. Edit a car\n";
        cout << "5. Sort cars by price\n";
        cout << "6. Search car by brand\n";
        cout << "7. Delete a car\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Очистка буфера

        switch (choice) {
            case 1: { // Создание массива
                cout << "Enter the number of cars to create: ";
                int n;
                cin >> n;
                cin.ignore();
                if (n <= 0 || n > MAX_CARS) {
                    cout << "Invalid number!" << endl;
                    break;
                }
                carCount = 0; // Сбрасываем массив
                for (int i = 0; i < n && carCount < MAX_CARS; i++) {
                    Car newCar;
                    newCar.number = carCount + 1;
                    cout << "Enter details for car " << newCar.number << ":\n";
                    cout << "Brand: ";
                    getline(cin, newCar.brand);
                    cout << "Model: ";
                    getline(cin, newCar.model);
                    cout << "Color: ";
                    getline(cin, newCar.color);
                    cout << "Country: ";
                    getline(cin, newCar.country);
                    cout << "Price: $";
                    cin >> newCar.price;
                    cin.ignore();
                    cars[carCount++] = newCar;
                }
                cout << "Array created with " << carCount << " cars.\n";
                break;
            }

            case 2: { // Вывод всех автомобилей
                if (carCount == 0) {
                    cout << "No cars in the array!\n";
                    break;
                }
                cout << "\nList of cars:\n";
                for (int i = 0; i < carCount; i++) {
                    printCar(cars[i]);
                }
                break;
            }

            case 3: { // Добавление автомобиля
                if (carCount >= MAX_CARS) {
                    cout << "Array is full!\n";
                    break;
                }
                Car newCar;
                newCar.number = carCount + 1;
                cout << "Enter details for new car:\n";
                cout << "Brand: ";
                getline(cin, newCar.brand);
                cout << "Model: ";
                getline(cin, newCar.model);
                cout << "Color: ";
                getline(cin, newCar.color);
                cout << "Country: ";
                getline(cin, newCar.country);
                cout << "Price: $";
                cin >> newCar.price;
                cin.ignore();
                cars[carCount++] = newCar;
                cout << "Car added successfully.\n";
                break;
            }

            case 4: { // Изменение данных автомобиля
                if (carCount == 0) {
                    cout << "No cars to edit!\n";
                    break;
                }
                int num;
                cout << "Enter car number to edit (1 to " << carCount << "): ";
                cin >> num;
                cin.ignore();
                if (num < 1 || num > carCount) {
                    cout << "Invalid car number!\n";
                    break;
                }
                Car& car = cars[num - 1];
                cout << "Editing car " << num << ":\n";
                cout << "Brand (" << car.brand << "): ";
                getline(cin, car.brand);
                cout << "Model (" << car.model << "): ";
                getline(cin, car.model);
                cout << "Color (" << car.color << "): ";
                getline(cin, car.color);
                cout << "Country (" << car.country << "): ";
                getline(cin, car.country);
                cout << "Price ($" << car.price << "): $";
                cin >> car.price;
                cin.ignore();
                cout << "Car updated successfully.\n";
                break;
            }

            case 5: { // Сортировка по цене
                if (carCount == 0) {
                    cout << "No cars to sort!\n";
                    break;
                }
                sort(cars, cars + carCount, [](const Car& a, const Car& b) {
                    return a.price < b.price;
                });
                cout << "Cars sorted by price. Sorted list:\n";
                cout << "\nList of cars:\n";
                for (int i = 0; i < carCount; i++) {
                    printCar(cars[i]);
                }
                break;
            }

            case 6: { // Поиск по марке
                if (carCount == 0) {
                    cout << "No cars to search!\n";
                    break;
                }
                string searchBrand;
                cout << "Enter brand to search: ";
                getline(cin, searchBrand);
                bool found = false;
                cout << "\nSearch results:\n";
                for (int i = 0; i < carCount; i++) {
                    if (cars[i].brand == searchBrand) {
                        printCar(cars[i]);
                        found = true;
                    }
                }
                if (!found) {
                    cout << "No cars found with brand '" << searchBrand << "'.\n";
                }
                break;
            }

            case 7: { // Удаление автомобиля
                if (carCount == 0) {
                    cout << "No cars to delete!\n";
                    break;
                }
                int num;
                cout << "Enter car number to delete (1 to " << carCount << "): ";
                cin >> num;
                cin.ignore();
                if (num < 1 || num > carCount) {
                    cout << "Invalid car number!\n";
                    break;
                }
                for (int i = num - 1; i < carCount - 1; i++) {
                    cars[i] = cars[i + 1];
                    cars[i].number = i + 1; // Обновляем номера
                }
                carCount--;
                cout << "Car deleted successfully.\n";
                break;
            }

            case 8: { // Выход
                cout << "Exiting program.\n";
                break;
            }

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}