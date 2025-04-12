#include <iostream>
using namespace std;

// Код ошибки для случая, когда элемент не найден
const int NOT_FOUND = -1;

// a. Шаблонная функция поиска первого подходящего элемента
template <typename T>
int findFirst(const T* arr, int size, const T& key) {
    if (size <= 0) {
        return NOT_FOUND; // Проверка на некорректный размер массива
    }
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            return i; // Возвращаем индекс первого подходящего элемента
        }
    }
    return NOT_FOUND; // Элемент не найден
}

// b. Параметризованный класс Queue (очередь)
template <typename T>
class Queue {
private:
    T* data;        // Массив для хранения элементов
    int capacity;   // Максимальная вместимость
    int length;     // Текущая длина очереди
    int front;      // Индекс начала очереди
    int rear;       // Индекс конца очереди

public:
    // Конструктор без параметров (по умолчанию)
    Queue() : capacity(10), length(0), front(0), rear(-1) {
        data = new T[capacity];
    }

    // Конструктор с параметром (задает начальную вместимость)
    Queue(int cap) : capacity(cap > 0 ? cap : 10), length(0), front(0), rear(-1) {
        data = new T[capacity];
    }

    // Деструктор
    ~Queue() {
        delete[] data;
    }

    // Функция добавления элемента в конец очереди
    void add(const T& value) {
        if (length == capacity) {
            // Увеличиваем массив, если он заполнен
            T* temp = new T[capacity * 2];
            for (int i = 0; i < length; i++) {
                temp[i] = data[(front + i) % capacity];
            }
            delete[] data;
            data = temp;
            front = 0;
            rear = length - 1;
            capacity *= 2;
        }
        rear = (rear + 1) % capacity;
        data[rear] = value;
        length++;
    }

    // Функция проверки, пустая ли очередь
    bool isEmpty() const {
        return length == 0;
    }

    // Функция получения первого элемента с удалением
    T get() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty!");
        }
        T value = data[front];
        front = (front + 1) % capacity;
        length--;
        return value;
    }

    // Функция получения длины очереди
    int getLength() const {
        return length;
    }

    // Перегрузка оператора []
    T& operator[](int index) {
        if (index < 0 || index >= length) {
            throw out_of_range("Index out of range!");
        }
        return data[(front + index) % capacity];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= length) {
            throw out_of_range("Index out of range!");
        }
        return data[(front + index) % capacity];
    }

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const Queue<T>& queue) {
        os << "Queue: [";
        for (int i = 0; i < queue.length; i++) {
            os << queue[i];
            if (i < queue.length - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    // Перегрузка оператора ввода
    friend istream& operator>>(istream& is, Queue<T>& queue) {
        T value;
        is >> value;
        queue.add(value);
        return is;
    }
};

int main() {
    // Демонстрация работы шаблонной функции findFirst
    cout << "=== Testing findFirst Function ===\n";

    // Пример с массивом целых чисел
    int intArr[] = {0, 2, 3, 4, 3, 6};
    int size = sizeof(intArr) / sizeof(intArr[0]);
    int key = 2;
    int result = findFirst(intArr, size, key);
    cout << "Array: ";
    for (int i = 0; i < size; i++) {
        cout << intArr[i] << " ";
    }
    cout << "\nSearching for " << key << ": Position = " << result << endl;

    // Пример с отсутствующим элементом
    key = 5;
    result = findFirst(intArr, size, key);
    cout << "Searching for " << key << ": Position = " << result << " (Not found)\n";

    // Пример с массивом строк
    string strArr[] = {"apple", "banana", "cherry", "apple"};
    size = sizeof(strArr) / sizeof(strArr[0]);
    string strKey = "apple";
    result = findFirst(strArr, size, strKey);
    cout << "\nArray: ";
    for (int i = 0; i < size; i++) {
        cout << strArr[i] << " ";
    }
    cout << "\nSearching for " << strKey << ": Position = " << result << endl;

    // Демонстрация работы класса Queue
    cout << "\n=== Testing Queue Class ===\n";

    // Создание очереди для целых чисел
    Queue<int> intQueue;
    cout << "Adding elements to intQueue: 1, 2, 3\n";
    intQueue.add(1);
    intQueue.add(2);
    intQueue.add(3);
    cout << intQueue << endl;
    cout << "Length: " << intQueue.getLength() << endl;

    // Использование оператора []
    cout << "Element at index 1: " << intQueue[1] << endl;

    // Удаление элемента
    cout << "Removing first element: " << intQueue.get() << endl;
    cout << intQueue << endl;
    cout << "Length: " << intQueue.getLength() << endl;

    // Использование оператора ввода
    cout << "Enter a number to add to intQueue: ";
    cin >> intQueue;
    cout << intQueue << endl;

    // Создание очереди для строк
    Queue<string> strQueue;
    cout << "\nAdding elements to strQueue: apple, banana, cherry\n";
    strQueue.add("apple");
    strQueue.add("banana");
    strQueue.add("cherry");
    cout << strQueue << endl;
    cout << "Length: " << strQueue.getLength() << endl;

    // Использование оператора []
    cout << "Element at index 0: " << strQueue[0] << endl;

    // Удаление элемента
    cout << "Removing first element: " << strQueue.get() << endl;
    cout << strQueue << endl;

    return 0;
}