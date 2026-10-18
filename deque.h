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

    void add(int value) override; // Добавление в конец
    void remove() override;       // Удаление из начала
    void addFront(int value);     // Добавление в начало
    void removeBack();            // Удаление с конца
    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    std::string getType() const override { return "Deque"; }
    void setValue(int index, int value) override;
    int getValue(int index) const override;
};