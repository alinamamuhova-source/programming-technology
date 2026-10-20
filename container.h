#pragma once
#include "Base.h"

class Container {
private:
    Base** items;
    int count;
    int capacity;
    
public:
    Container();
    Container(const Container& other);
    ~Container();

    void addObject(Base* obj);
    void removeObject(int index);
    void printAll() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    Base* getObject(int index);
    int getCount() const;
};