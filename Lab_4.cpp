#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // Для сортировки
#include <cstring>  // Для strncpy
using namespace std;

// Определение структуры для автомобиля
struct Car {
    int number;          // Номер автомобиля
    char brand[50];     // Марка
    char model[50];     // Модель
    char color[30];     // Цвет
    char country[50];   // Страна
    double price;       // Цена
};

// Функция для ввода данных об автомобиле
Car inputCar(int num) {
    Car car;
    car.number = num;
    string temp;
    cout << "Enter details for car " << num << ":\n";
    cout << "Brand: ";
    getline(cin, temp);
    strncpy(car.brand, temp.c_str(), sizeof(car.brand) - 1);
    car.brand[sizeof(car.brand) - 1] = '\0';
    cout << "Model: ";
    getline(cin, temp);
    strncpy(car.model, temp.c_str(), sizeof(car.model) - 1);
    car.model[sizeof(car.model) - 1] = '\0';
    cout << "Color: ";
    getline(cin, temp);
    strncpy(car.color, temp.c_str(), sizeof(car.color) - 1);
    car.color[sizeof(car.color) - 1] = '\0';
    cout << "Country: ";
    getline(cin, temp);
    strncpy(car.country, temp.c_str(), sizeof(car.country) - 1);
    car.country[sizeof(car.country) - 1] = '\0';
    cout << "Price: $";
    cin >> car.price;
    cin.ignore();
    return car;
}

// Функция для вывода одного автомобиля
void printCar(const Car& car) {
    cout << "Number: " << car.number
         << ", Brand: " << car.brand
         << ", Model: " << car.model
         << ", Color: " << car.color
         << ", Country: " << car.country
         << ", Price: $" << car.price << endl;
}

// Функция для чтения всех автомобилей из файла в вектор
vector<Car> readCarsFromFile(const string& filename) {
    vector<Car> cars;
    ifstream file(filename, ios::binary);
    if (!file) {
        return cars; // Файл не существует или пуст
    }
    Car car;
    while (file.read((char*)&car, sizeof(Car))) {
        cars.push_back(car);
    }
    file.close();
    return cars;
}

// Функция для записи вектора автомобилей в файл
void writeCarsToFile(const string& filename, const vector<Car>& cars) {
    ofstream file(filename, ios::binary);
    for (const auto& car : cars) {
        file.write((char*)&car, sizeof(Car));
    }
    file.close();
}

int main() {
    const string filename = "cars.dat"; // Имя бинарного файла
    int choice;

    do {
        // Вывод меню
        cout << "\n=== Car Dealership Menu ===\n";
        cout << "1. Create file with cars\n";
        cout << "2. Display all cars from file\n";
        cout << "3. Add a car to file\n";
        cout << "4. Edit a car in file\n";
        cout << "5. Sort cars by price in file\n";
        cout << "6. Search car by brand in file\n";
        cout << "7. Delete a car from file\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Очистка буфера

        switch (choice) {
            case 1: { // Создание файла
                cout << "Enter the number of cars to create: ";
                int n;
                cin >> n;
                cin.ignore();
                if (n <= 0) {
                    cout << "Invalid number!" << endl;
                    break;
                }
                vector<Car> cars;
                for (int i = 0; i < n; i++) {
                    cars.push_back(inputCar(i + 1));
                }
                writeCarsToFile(filename, cars);
                cout << "File created with " << n << " cars.\n";
                break;
            }

            case 2: { // Вывод содержимого файла
                vector<Car> cars = readCarsFromFile(filename);
                if (cars.empty()) {
                    cout << "File is empty or does not exist!\n";
                    break;
                }
                cout << "\nList of cars:\n";
                for (const auto& car : cars) {
                    printCar(car);
                }
                break;
            }

            case 3: { // Добавление автомобиля
                vector<Car> cars = readCarsFromFile(filename);
                int newNumber = cars.empty() ? 1 : cars.back().number + 1;
                cars.push_back(inputCar(newNumber));
                writeCarsToFile(filename, cars);
                cout << "Car added successfully.\n";
                break;
            }

            case 4: { // Изменение данных автомобиля
                vector<Car> cars = readCarsFromFile(filename);
                if (cars.empty()) {
                    cout << "File is empty!\n";
                    break;
                }
                int num;
                cout << "Enter car number to edit (1 to " << cars.back().number << "): ";
                cin >> num;
                cin.ignore();
                bool found = false;
                for (auto& car : cars) {
                    if (car.number == num) {
                        car = inputCar(num);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Car not found!\n";
                    break;
                }
                writeCarsToFile(filename, cars);
                cout << "Car updated successfully.\n";
                break;
            }

            case 5: { // Сортировка по цене
                vector<Car> cars = readCarsFromFile(filename);
                if (cars.empty()) {
                    cout << "File is empty!\n";
                    break;
                }
                sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
                    return a.price < b.price;
                });
                // Обновляем номера после сортировки
                for (size_t i = 0; i < cars.size(); i++) {
                    cars[i].number = i + 1;
                }
                writeCarsToFile(filename, cars);
                cout << "Cars sorted by price. Sorted list:\n";
                cout << "\nList of cars:\n";
                for (const auto& car : cars) {
                    printCar(car);
                }
                break;
            }

            case 6: { // Поиск по марке
                vector<Car> cars = readCarsFromFile(filename);
                if (cars.empty()) {
                    cout << "File is empty!\n";
                    break;
                }
                string searchBrand;
                cout << "Enter brand to search: ";
                getline(cin, searchBrand);
                bool found = false;
                cout << "\nSearch results:\n";
                for (const auto& car : cars) {
                    if (string(car.brand) == searchBrand) {
                        printCar(car);
                        found = true;
                    }
                }
                if (!found) {
                    cout << "No cars found with brand '" << searchBrand << "'.\n";
                }
                break;
            }

            case 7: { // Удаление автомобиля
                vector<Car> cars = readCarsFromFile(filename);
                if (cars.empty()) {
                    cout << "File is empty!\n";
                    break;
                }
                int num;
                cout << "Enter car number to delete (1 to " << cars.back().number << "): ";
                cin >> num;
                cin.ignore();
                vector<Car> newCars;
                bool found = false;
                for (const auto& car : cars) {
                    if (car.number != num) {
                        newCars.push_back(car);
                    } else {
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Car not found!\n";
                    break;
                }
                // Обновляем номера
                for (size_t i = 0; i < newCars.size(); i++) {
                    newCars[i].number = i + 1;
                }
                writeCarsToFile(filename, newCars);
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