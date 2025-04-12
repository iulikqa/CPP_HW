#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Константа для конвертации евро в молдавские леи
const double EUR_TO_MDL = 19.0;

// Базовый класс Car (из предыдущей лабораторной работы)
class Car {
protected: // Делаем поля доступными для производных классов
    int number;          // Номер автомобиля
    string brand;        // Марка
    string model;        // Модель
    string color;        // Цвет
    string country;      // Страна
    double price;        // Цена в евро

public:
    // Конструктор без параметров
    Car() : number(0), brand("Unknown"), model("Unknown"), color("Unknown"), country("Unknown"), price(0.0) {}

    // Конструктор со всеми параметрами
    Car(int num, const string& br, const string& mod, const string& col, const string& cnt, double pr)
        : number(num), brand(br), model(mod), color(col), country(cnt), price(pr) {}

    // Конструктор с некоторыми параметрами (номер, марка, модель, цена; цвет и страна по умолчанию)
    Car(int num, const string& br, const string& mod, double pr)
        : number(num), brand(br), model(mod), color("Unknown"), country("Unknown"), price(pr) {}

    // Методы для чтения полей (геттеры)
    int getNumber() const { return number; }
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    string getColor() const { return color; }
    string getCountry() const { return country; }
    double getPrice() const { return price; }

    // Методы для установки полей (сеттеры)
    void setNumber(int num) { number = num; }
    void setBrand(const string& br) { brand = br; }
    void setModel(const string& mod) { model = mod; }
    void setColor(const string& col) { color = col; }
    void setCountry(const string& cnt) { country = cnt; }
    void setPrice(double pr) { price = pr; }

    // Метод для установки цены с проверкой ввода
    void setPriceWithValidation() {
        double pr;
        bool validInput = false;
        do {
            cout << "Price (EUR): ";
            if (cin >> pr && pr >= 0) {
                validInput = true;
                price = pr;
            } else {
                cout << "Invalid input! Please enter a non-negative number.\n";
                cin.clear(); // Очищаем состояние ошибки
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер
            }
        } while (!validInput);
    }

    // Виртуальный метод для отображения (для полиморфизма)
    virtual void display() const {
        cout << "Number: " << number
             << ", Brand: " << brand
             << ", Model: " << model
             << ", Color: " << color
             << ", Country: " << country
             << ", Price: " << price << " EUR" << endl;
    }

    // Метод для конвертации цены из евро в молдавские леи
    double convertToMDL() const {
        return price * EUR_TO_MDL;
    }

    // Перегрузка оператора == (сравнение автомобилей по всем полям)
    bool operator==(const Car& other) const {
        return number == other.number &&
               brand == other.brand &&
               model == other.model &&
               color == other.color &&
               country == other.country &&
               price == other.price;
    }

    // Перегрузка оператора + (добавление суммы к цене)
    Car operator+(double amount) const {
        Car result = *this;
        result.price += amount;
        return result;
    }

    // Виртуальный деструктор для корректного удаления объектов производных классов
    virtual ~Car() {}
};

// Производный класс AutomaticCar (автомобили с автоматической коробкой передач)
class AutomaticCar : public Car {
protected:
    int numGears;        // Количество передач
    int numReverseGears; // Количество передач заднего хода

public:
    // Конструктор без параметров
    AutomaticCar() : Car(), numGears(0), numReverseGears(0) {}

    // Конструктор со всеми параметрами
    AutomaticCar(int num, const string& br, const string& mod, const string& col, const string& cnt, double pr, int gears, int reverseGears)
        : Car(num, br, mod, col, cnt, pr), numGears(gears), numReverseGears(reverseGears) {}

    // Конструктор с некоторыми параметрами (номер, марка, модель, цена, количество передач; цвет, страна и передачи заднего хода по умолчанию)
    AutomaticCar(int num, const string& br, const string& mod, double pr, int gears)
        : Car(num, br, mod, pr), numGears(gears), numReverseGears(1) {}

    // Геттеры и сеттеры для новых полей
    int getNumGears() const { return numGears; }
    int getNumReverseGears() const { return numReverseGears; }
    void setNumGears(int gears) { numGears = gears; }
    void setNumReverseGears(int reverseGears) { numReverseGears = reverseGears; }

    // Переопределение метода display
    void display() const override {
        Car::display();
        cout << "Transmission: Automatic, Number of Gears: " << numGears
             << ", Number of Reverse Gears: " << numReverseGears << endl;
    }

    // Виртуальный деструктор
    virtual ~AutomaticCar() {}
};

// Производный класс GPSAutomaticCar (автомобили с GPS и автоматической коробкой передач)
class GPSAutomaticCar : public AutomaticCar {
private:
    string gpsType;      // Тип GPS

public:
    // Конструктор без параметров
    GPSAutomaticCar() : AutomaticCar(), gpsType("Unknown") {}

    // Конструктор со всеми параметрами
    GPSAutomaticCar(int num, const string& br, const string& mod, const string& col, const string& cnt, double pr, int gears, int reverseGears, const string& gps)
        : AutomaticCar(num, br, mod, col, cnt, pr, gears, reverseGears), gpsType(gps) {}

    // Конструктор с некоторыми параметрами (номер, марка, модель, цена, количество передач, тип GPS; цвет, страна и передачи заднего хода по умолчанию)
    GPSAutomaticCar(int num, const string& br, const string& mod, double pr, int gears, const string& gps)
        : AutomaticCar(num, br, mod, pr, gears), gpsType(gps) {}

    // Геттер и сеттер для нового поля
    string getGpsType() const { return gpsType; }
    void setGpsType(const string& gps) { gpsType = gps; }

    // Переопределение метода display
    void display() const override {
        AutomaticCar::display();
        cout << "GPS Type: " << gpsType << endl;
    }

    // Деструктор
    ~GPSAutomaticCar() {}
};

int main() {
    // Демонстрация работы классов
    cout << "=== Car Dealership Demo ===\n";

    // Создание объекта базового класса Car
    cout << "\nCar (base class):\n";
    Car car1(1, "Toyota", "Camry", "Black", "Japan", 25000.0);
    car1.display();
    cout << "Price in MDL: " << car1.convertToMDL() << " MDL\n";

    // Создание объекта класса AutomaticCar
    cout << "\nAutomaticCar (derived from Car):\n";
    AutomaticCar car2(2, "Ford", "Focus", "Blue", "USA", 20000.0, 6, 1);
    car2.display();
    cout << "Price in MDL: " << car2.convertToMDL() << " MDL\n";

    // Создание объекта класса GPSAutomaticCar
    cout << "\nGPSAutomaticCar (derived from AutomaticCar):\n";
    GPSAutomaticCar car3(3, "BMW", "X5", "White", "Germany", 40000.0, 8, 1, "Built-in Navigation");
    car3.display();
    cout << "Price in MDL: " << car3.convertToMDL() << " MDL\n";

    // Демонстрация конструктора с частичными параметрами
    cout << "\nGPSAutomaticCar (partial constructor):\n";
    GPSAutomaticCar car4(4, "Mercedes", "C-Class", 35000.0, 7, "Portable GPS");
    car4.display();
    cout << "Price in MDL: " << car4.convertToMDL() << " MDL\n";

    // Демонстрация полиморфизма
    cout << "\nPolymorphism demo (using pointers to base class):\n";
    Car* cars[] = { &car1, &car2, &car3 };
    for (int i = 0; i < 3; i++) {
        cout << "Car " << (i + 1) << ":\n";
        cars[i]->display();
        cout << endl;
    }

    return 0;
}