#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

class Base {
public:
    Base() { std::cout << "Base constructor called\n"; }
    Base(const Base& other) { std::cout << "Base copy constructor called\n"; }
    virtual ~Base() { std::cout << "Base destructor called\n"; }

    virtual void add(int value) = 0;
    virtual void remove() = 0;
    virtual void print() const = 0;
    virtual void save(std::ofstream& out) const = 0;
    virtual void load(std::ifstream& in) = 0;
    virtual std::string getType() const = 0;
    virtual void setValue(int index, int value) = 0;
    virtual int getValue(int index) const = 0;
};