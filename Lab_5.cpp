#include <iostream>
#include <string>
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

// Узел линейного списка
struct Node {
    Car data;           // Данные об автомобиле
    Node* next;         // Указатель на следующий узел
};

// Функция для вывода одного автомобиля
void printCar(const Car& car) {
    cout << "Number: " << car.number 
         << ", Brand: " << car.brand 
         << ", Model: " << car.model 
         << ", Color: " << car.color 
         << ", Country: " << car.country 
         << ", Price: $" << car.price << endl;
}

// Функция для создания нового узла
Node* createNode(const Car& car) {
    Node* newNode = new Node;
    newNode->data = car;
    newNode->next = nullptr;
    return newNode;
}

// Функция для добавления узла в конец списка
void appendNode(Node*& head, const Car& car) {
    Node* newNode = createNode(car);
    if (!head) {
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

// Функция для очистки списка (освобождение памяти)
void clearList(Node*& head) {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

int main() {
    Node* head = nullptr; // Голова списка
    int choice;

    do {
        // Вывод меню
        cout << "\n=== Car Dealership Menu ===\n";
        cout << "1. Create list of cars\n";
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
            case 1: { // Создание списка
                clearList(head); // Очищаем существующий список
                cout << "Enter the number of cars to create: ";
                int n;
                cin >> n;
                cin.ignore();
                if (n <= 0) {
                    cout << "Invalid number!" << endl;
                    break;
                }
                int nextNumber = 1;
                for (int i = 0; i < n; i++) {
                    Car car;
                    car.number = nextNumber++;
                    cout << "Enter details for car " << car.number << ":\n";
                    cout << "Brand: ";
                    getline(cin, car.brand);
                    cout << "Model: ";
                    getline(cin, car.model);
                    cout << "Color: ";
                    getline(cin, car.color);
                    cout << "Country: ";
                    getline(cin, car.country);
                    cout << "Price: $";
                    cin >> car.price;
                    cin.ignore();
                    appendNode(head, car);
                }
                cout << "List created with " << n << " cars.\n";
                break;
            }

            case 2: { // Вывод всех автомобилей
                if (!head) {
                    cout << "List is empty!\n";
                    break;
                }
                cout << "\nList of cars:\n";
                Node* current = head;
                while (current) {
                    printCar(current->data);
                    current = current->next;
                }
                break;
            }

            case 3: { // Добавление автомобиля
                Car car;
                // Присваиваем номер на основе последнего элемента
                int nextNumber = 1;
                Node* current = head;
                while (current) {
                    nextNumber = current->data.number + 1;
                    current = current->next;
                }
                car.number = nextNumber;
                cout << "Enter details for new car:\n";
                cout << "Brand: ";
                getline(cin, car.brand);
                cout << "Model: ";
                getline(cin, car.model);
                cout << "Color: ";
                getline(cin, car.color);
                cout << "Country: ";
                getline(cin, car.country);
                cout << "Price: $";
                cin >> car.price;
                cin.ignore();
                appendNode(head, car);
                cout << "Car added successfully.\n";
                break;
            }

            case 4: { // Изменение данных автомобиля
                if (!head) {
                    cout << "List is empty!\n";
                    break;
                }
                int num;
                cout << "Enter car number to edit: ";
                cin >> num;
                cin.ignore();
                Node* current = head;
                bool found = false;
                while (current) {
                    if (current->data.number == num) {
                        cout << "Editing car " << num << ":\n";
                        cout << "Brand (" << current->data.brand << "): ";
                        getline(cin, current->data.brand);
                        cout << "Model (" << current->data.model << "): ";
                        getline(cin, current->data.model);
                        cout << "Color (" << current->data.color << "): ";
                        getline(cin, current->data.color);
                        cout << "Country (" << current->data.country << "): ";
                        getline(cin, current->data.country);
                        cout << "Price ($" << current->data.price << "): $";
                        cin >> current->data.price;
                        cin.ignore();
                        found = true;
                        cout << "Car updated successfully.\n";
                        break;
                    }
                    current = current->next;
                }
                if (!found) {
                    cout << "Car not found!\n";
                }
                break;
            }

            case 5: { // Сортировка по цене
                if (!head || !head->next) {
                    cout << (!head ? "List is empty!\n" : "Only one car, no sorting needed.\n");
                    break;
                }
                // Считаем количество узлов
                int count = 0;
                Node* temp = head;
                while (temp) {
                    count++;
                    temp = temp->next;
                }
                // Копируем данные в массив для сортировки
                Car* cars = new Car[count];
                temp = head;
                for (int i = 0; i < count; i++) {
                    cars[i] = temp->data;
                    temp = temp->next;
                }
                // Сортировка массива
                for (int i = 0; i < count - 1; i++) {
                    for (int j = 0; j < count - i - 1; j++) {
                        if (cars[j].price > cars[j + 1].price) {
                            swap(cars[j], cars[j + 1]);
                        }
                    }
                }
                // Обновляем номера и перестраиваем список
                clearList(head);
                for (int i = 0; i < count; i++) {
                    cars[i].number = i + 1; // Обновляем номера
                    appendNode(head, cars[i]);
                }
                delete[] cars;
                cout << "Cars sorted by price. Sorted list:\n";
                cout << "\nList of cars:\n";
                temp = head;
                while (temp) {
                    printCar(temp->data);
                    temp = temp->next;
                }
                break;
            }

            case 6: { // Поиск по марке
                if (!head) {
                    cout << "List is empty!\n";
                    break;
                }
                string searchBrand;
                cout << "Enter brand to search: ";
                getline(cin, searchBrand);
                bool found = false;
                cout << "\nSearch results:\n";
                Node* current = head;
                while (current) {
                    if (current->data.brand == searchBrand) {
                        printCar(current->data);
                        found = true;
                    }
                    current = current->next;
                }
                if (!found) {
                    cout << "No cars found with brand '" << searchBrand << "'.\n";
                }
                break;
            }

            case 7: { // Удаление автомобиля
                if (!head) {
                    cout << "List is empty!\n";
                    break;
                }
                int num;
                cout << "Enter car number to delete: ";
                cin >> num;
                cin.ignore();
                Node* current = head;
                Node* prev = nullptr;
                bool found = false;
                while (current) {
                    if (current->data.number == num) {
                        if (prev) {
                            prev->next = current->next;
                        } else {
                            head = current->next;
                        }
                        delete current;
                        found = true;
                        cout << "Car deleted successfully.\n";
                        break;
                    }
                    prev = current;
                    current = current->next;
                }
                if (!found) {
                    cout << "Car not found!\n";
                }
                // Обновляем номера
                current = head;
                int newNumber = 1;
                while (current) {
                    current->data.number = newNumber++;
                    current = current->next;
                }
                break;
            }

            case 8: { // Выход
                clearList(head);
                cout << "Exiting program.\n";
                break;
            }

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}