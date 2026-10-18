#pragma once
#include "Base.h"
#include "List.h"

class Deque : public Base {
private:
    Node* head;
    Node* tail;
    int size;
public:
    Deque();
    Deque(const Deque& other);
    ~Deque() override;

    void add(int value) override;
    void remove() override;
    void addFront(int value);
    void removeBack();
    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    std::string getType() const override { return "Deque"; }
    void setValue(int index, int value) override;
    int getValue(int index) const override;
};