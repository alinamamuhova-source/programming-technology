#include "Deque.h"

Deque::Deque() : head(nullptr), tail(nullptr), size(0) {
    std::cout << "Вызван конструктор по умолчанию класса Deque\n";
}

Deque::Deque(const Deque& other) : head(nullptr), tail(nullptr), size(0) {
    std::cout << "Вызван конструктор копирования класса Deque\n";
    Node* current = other.head;
    while (current) {
        add(current->data);
        current = current->next;
    }
}

Deque::~Deque() {
    std::cout << "Вызван деструктор класса Deque\n";
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void Deque::add(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void Deque::remove() {
    if (!head) throw std::runtime_error("Ошибка: Невозможно удалить элемент из пустого дека (Deque)");
    Node* temp = head;
    head = head->next;
    if (!head) tail = nullptr;
    delete temp;
    size--;
}

void Deque::addFront(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

void Deque::removeBack() {
    if (!head) throw std::runtime_error("Ошибка: Невозможно удалить элемент из пустого дека (Deque)");
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node* current = head;
        while (current->next != tail) current = current->next;
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    size--;
}

void Deque::print() const {
    std::cout << "Элементы дека (Deque): ";
    Node* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}

void Deque::save(std::ofstream& out) const {
    out << size << "\n";
    Node* current = head;
    while (current) {
        out << current->data << " ";
        current = current->next;
    }
    out << "\n";
}

void Deque::load(std::ifstream& in) {
    int newSize;
    in >> newSize;
    for (int i = 0; i < newSize; ++i) {
        int val;
        in >> val;
        add(val);
    }
}

void Deque::setValue(int index, int value) {
    if (index < 0 || index >= size) throw std::out_of_range("Ошибка: Индекс вне диапазона в Deque::setValue");
    Node* current = head;
    for (int i = 0; i < index; ++i) current = current->next;
    current->data = value;
}

int Deque::getValue(int index) const {
    if (index < 0 || index >= size) throw std::out_of_range("Ошибка: Индекс вне диапазона в Deque::getValue");
    Node* current = head;
    for (int i = 0; i < index; ++i) current = current->next;
    return current->data;
}