#pragma once
#include "Base.h"

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class List : public Base {
protected:
    Node* head;
    Node* tail;
    int size;
public:
    List();
    List(const List& other);
    ~List() override;

    void add(int value) override; // Добавление в конец
    void remove() override;       // Удаление из начала
    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    std::string getType() const override { return "List"; }
    void setValue(int index, int value) override;
    int getValue(int index) const override;
};