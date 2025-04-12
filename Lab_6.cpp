#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Константа для конвертации евро в молдавские леи
const double EUR_TO_MDL = 19.0;

class Car {
private:
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

    // Метод для отображения всех полей
    void display() const {
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
};

int main() {
    // Демонстрация работы класса
    cout << "=== Car Dealership Demo ===\n";

    // Использование конструктора без параметров
    cout << "\nCar 1 (default constructor):\n";
    Car car1;
    car1.display();
    cout << "Price in MDL: " << car1.convertToMDL() << " MDL\n";

    // Использование конструктора со всеми параметрами
    cout << "\nCar 2 (full constructor):\n";
    Car car2(1, "Toyota", "Camry", "Black", "Japan", 25000.0);
    car2.display();
    cout << "Price in MDL: " << car2.convertToMDL() << " MDL\n";

    // Использование конструктора с некоторыми параметрами
    cout << "\nCar 3 (partial constructor):\n";
    Car car3(2, "Ford", "Focus", 20000.0);
    car3.display();
    cout << "Price in MDL: " << car3.convertToMDL() << " MDL\n";

    // Демонстрация сеттеров с проверкой ввода для цены
    cout << "\nModifying Car 1:\n";
    car1.setNumber(3);
    car1.setBrand("BMW");
    car1.setModel("X5");
    car1.setColor("White");
    car1.setCountry("Germany");
    car1.setPriceWithValidation(); // Используем метод с проверкой ввода
    car1.display();
    cout << "Price in MDL: " << car1.convertToMDL() << " MDL\n";

    // Демонстрация оператора ==
    cout << "\nComparing Car 2 and Car 3:\n";
    if (car2 == car3) {
        cout << "Cars are equal.\n";
    } else {
        cout << "Cars are not equal.\n";
    }

    // Демонстрация оператора +
    cout << "\nAdding 5000 EUR to Car 2's price:\n";
    Car car4 = car2 + 5000.0;
    car4.display();
    cout << "Price in MDL: " << car4.convertToMDL() << " MDL\n";

    return 0;
}