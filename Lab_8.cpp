#include <iostream>
#include <string>
using namespace std;

// Константы для курса обмена
const double MDL_TO_EUR = 0.053; // 1 MDL = 0.053 EUR
const double EUR_TO_MDL = 19.0;  // 1 EUR = 19 MDL

// Абстрактный базовый класс CurrencyExchange
class CurrencyExchange {
protected:
    double amount;      // Сумма
    string currency;    // Валюта

public:
    // Конструктор с параметрами
    CurrencyExchange(double amt, const string& curr) : amount(amt), currency(curr) {}

    // Геттеры
    double getAmount() const { return amount; }
    string getCurrency() const { return currency; }

    // Сеттеры
    void setAmount(double amt) { amount = amt; }
    void setCurrency(const string& curr) { currency = curr; }

    // Абстрактный метод для конвертации (чистый виртуальный метод)
    virtual double convert() const = 0;

    // Виртуальный метод для отображения информации
    virtual void display() const {
        cout << "Amount: " << amount << " " << currency << endl;
    }

    // Виртуальный деструктор для корректного удаления объектов производных классов
    virtual ~CurrencyExchange() {}
};

// Производный класс MDLtoEUR (обмен леев в евро)
class MDLtoEUR : public CurrencyExchange {
public:
    // Конструктор
    MDLtoEUR(double amt) : CurrencyExchange(amt, "MDL") {}

    // Реализация метода конвертации
    double convert() const override {
        return amount * MDL_TO_EUR;
    }

    // Переопределение метода отображения
    void display() const override {
        CurrencyExchange::display();
        cout << "Converted to EUR: " << convert() << " EUR" << endl;
    }
};

// Производный класс EURtoMDL (обмен евро в леи)
class EURtoMDL : public CurrencyExchange {
public:
    // Конструктор
    EURtoMDL(double amt) : CurrencyExchange(amt, "EUR") {}

    // Реализация метода конвертации
    double convert() const override {
        return amount * EUR_TO_MDL;
    }

    // Переопределение метода отображения
    void display() const override {
        CurrencyExchange::display();
        cout << "Converted to MDL: " << convert() << " MDL" << endl;
    }
};

int main() {
    // Демонстрация работы классов
    cout << "=== Currency Exchange Demo ===\n";

    // Создание объектов производных классов
    MDLtoEUR mdlExchange(1000.0); // 1000 леев
    EURtoMDL eurExchange(50.0);   // 50 евро

    // Вывод информации об объектах
    cout << "\nMDL to EUR Exchange:\n";
    mdlExchange.display();

    cout << "\nEUR to MDL Exchange:\n";
    eurExchange.display();

    // Демонстрация полиморфизма
    cout << "\nPolymorphism Demo (using pointers to base class):\n";
    CurrencyExchange* exchanges[] = { &mdlExchange, &eurExchange };
    for (int i = 0; i < 2; i++) {
        cout << "Exchange " << (i + 1) << ":\n";
        exchanges[i]->display();
        cout << endl;
    }

    return 0;
}