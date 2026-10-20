#include "Container.h"
#include "List.h"
#include "Deque.h"
#include "Stack.h"

Container::Container() : count(0), capacity(10) {
    items = new Base*[capacity];
    std::cout << "Вызван конструктор по умолчанию класса Container\n";
}

Container::Container(const Container& other) : count(other.count), capacity(other.capacity) {
    std::cout << "Вызван конструктор копирования класса Container\n";
    items = new Base*[capacity];
    for (int i = 0; i < count; ++i) {
        if (other.items[i]->getType() == "List") items[i] = new List(*dynamic_cast<List*>(other.items[i]));
        else if (other.items[i]->getType() == "Deque") items[i] = new Deque(*dynamic_cast<Deque*>(other.items[i]));
        else if (other.items[i]->getType() == "Stack") items[i] = new Stack(*dynamic_cast<Stack*>(other.items[i]));
    }
}

Container::~Container() {
    std::cout << "Вызван деструктор класса Container\n";
    for (int i = 0; i < count; ++i) {
        delete items[i];
    }
    delete[] items;
}

void Container::addObject(Base* obj) {
    if (count >= capacity) {
        capacity *= 2;
        Base** newItems = new Base*[capacity];
        for (int i = 0; i < count; ++i) newItems[i] = items[i];
        delete[] items;
        items = newItems;
    }
    items[count++] = obj;
}

void Container::removeObject(int index) {
    if (index < 0 || index >= count) throw std::out_of_range("Ошибка: Индекс вне диапазона в Container::removeObject");
    delete items[index];
    for (int i = index; i < count - 1; ++i) {
        items[i] = items[i + 1];
    }
    count--;
}

void Container::printAll() const {
    if (count == 0) {
        std::cout << "Контейнер пуст.\n";
        return;
    }
    for (int i = 0; i < count; ++i) {
        std::cout << i << ": " << items[i]->getType() << " -> ";
        items[i]->print();
    }
}

void Container::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Ошибка: Невозможно открыть файл для записи");
    out << count << "\n";
    for (int i = 0; i < count; ++i) {
        out << items[i]->getType() << "\n";
        items[i]->save(out);
    }
    out.close();
}

void Container::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) throw std::runtime_error("Ошибка: Невозможно открыть файл для чтения");
    
    for (int i = 0; i < count; ++i) delete items[i];
    delete[] items;
    
    count = 0;
    capacity = 10;
    items = new Base*[capacity];

    int newCount;
    in >> newCount;
    for (int i = 0; i < newCount; ++i) {
        std::string type;
        in >> type;
        Base* obj = nullptr;
        if (type == "List") obj = new List();
        else if (type == "Deque") obj = new Deque();
        else if (type == "Stack") obj = new Stack();
        else throw std::runtime_error("Ошибка: Неизвестный тип объекта в файле");
        
        obj->load(in);
        addObject(obj);
    }
    in.close();
}

Base* Container::getObject(int index) {
    if (index < 0 || index >= count) throw std::out_of_range("Ошибка: Индекс вне диапазона в Container::getObject");
    return items[index];
}

int Container::getCount() const { return count; }