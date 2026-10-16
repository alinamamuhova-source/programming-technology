#include "List.h"

List::List() : head(nullptr), tail(nullptr), size(0) {
    std::cout << "List default constructor called\n";
}

List::List(const List& other) : head(nullptr), tail(nullptr), size(0) {
    std::cout << "List copy constructor called\n";
    Node* current = other.head;
    while (current) {
        add(current->data);
        current = current->next;
    }
}

List::~List() {
    std::cout << "List destructor called\n";
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void List::add(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void List::remove() {
    if (!head) throw std::runtime_error("Cannot remove from empty List");
    Node* temp = head;
    head = head->next;
    if (!head) tail = nullptr;
    delete temp;
    size--;
}

void List::print() const {
    std::cout << "List elements: ";
    Node* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}

void List::save(std::ofstream& out) const {
    out << size << "\n";
    Node* current = head;
    while (current) {
        out << current->data << " ";
        current = current->next;
    }
    out << "\n";
}

void List::load(std::ifstream& in) {
    int newSize;
    in >> newSize;
    for (int i = 0; i < newSize; ++i) {
        int val;
        in >> val;
        add(val);
    }
}

void List::setValue(int index, int value) {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range in List::setValue");
    Node* current = head;
    for (int i = 0; i < index; ++i) current = current->next;
    current->data = value;
}

int List::getValue(int index) const {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range in List::getValue");
    Node* current = head;
    for (int i = 0; i < index; ++i) current = current->next;
    return current->data;
}