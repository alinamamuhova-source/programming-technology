#pragma once
#include "Base.h"
#include "List.h"

class Stack : public Base {
private:
    Node* top;
    int size;
public:
    Stack();
    Stack(const Stack& other);
    ~Stack() override;

    void add(int value) override;
    void remove() override;
    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    std::string getType() const override { return "Stack"; }
    void setValue(int index, int value) override;
    int getValue(int index) const override;
};