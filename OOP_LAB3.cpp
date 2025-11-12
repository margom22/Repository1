#include <iostream>
#include <string>
#include <stdexcept>
#include <locale>

// Базовый класс для всех ошибок
class ProgramError : public std::exception {
protected:
    std::string message;
public:
    explicit ProgramError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { //возврат информации об ошибке
        return message.c_str();
    }
};

// Ошибка доступа к памяти
class MemoryAccessError : public ProgramError {
public:
    explicit MemoryAccessError(const std::string& msg = "Ошибка доступа к памяти")
        : ProgramError(msg) {
    }
};

// Математическая ошибка
class MathError : public ProgramError {
public:
    explicit MathError(const std::string& msg = "Математическая ошибка")
        : ProgramError(msg) {
    }
};

// Деление на ноль
class DivisionByZeroError : public MathError {
public:
    explicit DivisionByZeroError(const std::string& msg = "Деление на ноль")
        : MathError(msg) {
    }
};

// Переполнение
class OverflowError : public MathError {
public:
    explicit OverflowError(const std::string& msg = "Переполнение")
        : MathError(msg) {
    }
};

// Шаблонный класс для хранения массива указателей на объекты
template<typename T>
class PointerArray {
private:
    T** data;        // массив указателей
    size_t size;     // текущий размер
    size_t capacity; // выделенная ёмкость

    // Метод для увеличения ёмкости массива
    void resize() {
        capacity *= 2;
        T** newData = new T * [capacity];

        // Копируем существующие указатели
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
    }

public:
    // Конструктор
    explicit PointerArray(size_t initialCapacity = 10)
        : size(0), capacity(initialCapacity) {
        data = new T * [capacity];
    }

    // Деструктор, освобождаем всю память
    ~PointerArray() {
        for (size_t i = 0; i < size; ++i) {
            delete data[i];  // удаляем объекты
        }
        delete[] data;       // удаляем массив указателей
    }

    // Проверка несуществующего индекса (из замечания к заданию)
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за границы массива");
        }
        return *data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за границы массива");
        }
        return *data[index];
    }

    // Добавление элемента в конец массива
    void push_back(T* ptr) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = ptr;
    }

    // Получение размера
    size_t getSize() const {
        return size;
    }

    // Удаление последнего элемента
    void pop_back() {
        if (size > 0) {
            delete data[size - 1];
            --size;
        }
    }

    // Очистка всех элементов
    void clear() {
        for (size_t i = 0; i < size; ++i) {
            delete data[i];
        }
        size = 0;
    }

    // Запрет копирования (чтобы избежать проблем с памятью)
    PointerArray(const PointerArray&) = delete;
    PointerArray& operator=(const PointerArray&) = delete;
};

// Пример класса для демонстрации
class SampleClass {
private:
    int value;
public:
    explicit SampleClass(int val) : value(val) {}
    int getValue() const { return value; }
    void setValue(int val) { value = val; }
};

// Ещё один пример класса
class DataContainer {
private:
    double data;
    std::string name;
public:
    DataContainer(double d, const std::string& n) : data(d), name(n) {}
    double getData() const { return data; }
    const std::string& getName() const { return name; }
};

int main() {
    setlocale(LC_ALL, "rus");
    try {
        // Создаём массивы указателей для разных типов
        PointerArray<SampleClass> intArray;
        PointerArray<DataContainer> dataArray;

        intArray.push_back(new SampleClass(10));
        intArray.push_back(new SampleClass(20));
        intArray.push_back(new SampleClass(30));

        dataArray.push_back(new DataContainer(3.14, "Pi"));
        dataArray.push_back(new DataContainer(2.71, "Euler"));

        std::cout << "Элементы intArray:\n";
        for (size_t i = 0; i < intArray.getSize(); ++i) {
            std::cout << "Элемент " << i << ": " << intArray[i].getValue() << "\n";
        }

        std::cout << "\nЭлементы dataArray:\n";
        for (size_t i = 0; i < dataArray.getSize(); ++i) {
            std::cout << "Элемент " << i << ": "
                << dataArray[i].getName() << " = "
                << dataArray[i].getData() << "\n";
        }

        // Проверяем обработку ошибок при выходе за границы
        try {
            auto& item = intArray[100];  // Этот индекс не существует !!!!!
            std::cout << item.getValue() << "\n";
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }

        // Демонстрация работы с исключениями
        try {
            throw DivisionByZeroError();
        }
        catch (const DivisionByZeroError& e) {
            std::cerr << "Поймана ошибка: " << e.what() << "\n";
        }

        try {
            throw MemoryAccessError("Попытка доступа к освобождённой памяти");
        }
        catch (const MemoryAccessError& e) {
            std::cerr << "Поймана ошибка: " << e.what() << "\n";
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Неожиданная ошибка: " << e.what() << "\n";
       // return 1;
    }

    std::cout << "Программа завершена. Память освобождена.\n";
    return 0;
}
