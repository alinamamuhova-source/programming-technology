#include "Stack.h"

Stack::Stack() : top(nullptr), size(0) {
    std::cout << "Вызван конструктор по умолчанию класса Stack\n";
}

Stack::Stack(const Stack& other) : top(nullptr), size(0) {
    std::cout << "Вызван конструктор копирования класса Stack\n";
    int* temp = new int[other.size];
    Node* current = other.top;
    for (int i = other.size - 1; i >= 0; --i) {
        temp[i] = current->data;
        current = current->next;
    }
    for (int i = 0; i < other.size; ++i) {
        add(temp[i]);
    }
    delete[] temp;
}

Stack::~Stack() {
    std::cout << "Вызван деструктор класса Stack\n";
    while (top) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::add(int value) {
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
    size++;
}

void Stack::remove() {
    if (!top) throw std::runtime_error("Ошибка: Невозможно извлечь элемент из пустого стека (Stack)");
    Node* temp = top;
    top = top->next;
    delete temp;
    size--;
}

void Stack::print() const {
    std::cout << "Элементы стека (Stack, сверху вниз): ";
    Node* current = top;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}

void Stack::save(std::ofstream& out) const {
    out << size << "\n";
    Node* current = top;
    while (current) {
        out << current->data << " ";
        current = current->next;
    }
    out << "\n";
}

void Stack::load(std::ifstream& in) {
    int newSize;
    in >> newSize;
    for (int i = 0; i < newSize; ++i) {
        int val;
        in >> val;
        add(val);
    }
}

void Stack::setValue(int index, int value) {
    if (index < 0 || index >= size) throw std::out_of_range("Ошибка: Индекс вне диапазона в Stack::setValue");
    Node* current = top;
    for (int i = 0; i < index; ++i) current = current->next;
    current->data = value;
}

int Stack::getValue(int index) const {
    if (index < 0 || index >= size) throw std::out_of_range("Ошибка: Индекс вне диапазона в Stack::getValue");
    Node* current = top;
    for (int i = 0; i < index; ++i) current = current->next;
    return current->data;
}