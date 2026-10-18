#include "Stack.h"

Stack::Stack() : top(nullptr), size(0) {
    std::cout << "Stack default constructor called\n";
}

Stack::Stack(const Stack& other) : top(nullptr), size(0) {
    std::cout << "Stack copy constructor called\n";
    // Для копирования стека сохраняем элементы во временный массив
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
    std::cout << "Stack destructor called\n";
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
    if (!top) throw std::runtime_error("Cannot pop from empty Stack");
    Node* temp = top;
    top = top->next;
    delete temp;
    size--;
}

void Stack::print() const {
    std::cout << "Stack elements (top to bottom): ";
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
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range in Stack::setValue");
    Node* current = top;
    for (int i = 0; i < index; ++i) current = current->next;
    current->data = value;
}

int Stack::getValue(int index) const {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range in Stack::getValue");
    Node* current = top;
    for (int i = 0; i < index; ++i) current = current->next;
    return current->data;
}