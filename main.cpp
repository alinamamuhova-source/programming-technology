#include <iostream>
#include <limits>
#include "Container.h"
#include "List.h"
#include "Deque.h"
#include "Stack.h"

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Container container;
    int choice;

    do {
        std::cout << "\n=== MENU ===\n";
        std::cout << "1. Add List\n";
        std::cout << "2. Add Deque\n";
        std::cout << "3. Add Stack\n";
        std::cout << "4. Remove object by index\n";
        std::cout << "5. Print all objects\n";
        std::cout << "6. Work with an object\n";
        std::cout << "7. Save to file\n";
        std::cout << "8. Load from file\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            clearInput();
            std::cout << "Invalid input!\n";
            continue;
        }

        try {
            switch (choice) {
                case 1: container.addObject(new List()); break;
                case 2: container.addObject(new Deque()); break;
                case 3: container.addObject(new Stack()); break;
                case 4: {
                    int idx;
                    std::cout << "Enter index to remove: ";
                    std::cin >> idx;
                    container.removeObject(idx);
                    std::cout << "Removed.\n";
                    break;
                }
                case 5: container.printAll(); break;
                case 6: {
                    int idx;
                    std::cout << "Enter object index: ";
                    std::cin >> idx;
                    Base* obj = container.getObject(idx);
                    int action;
                    do {
                        std::cout << "\n-- Working with " << obj->getType() << " --\n";
                        std::cout << "1. Add number\n";
                        std::cout << "2. Remove number\n";
                        std::cout << "3. Print\n";
                        std::cout << "4. Set value by index\n";
                        std::cout << "5. Get value by index\n";
                        if (obj->getType() == "Deque") std::cout << "6. Add to front\n7. Remove from back\n";
                        std::cout << "0. Back to main menu\n";
                        std::cout << "Choose: ";
                        std::cin >> action;

                        if (std::cin.fail()) { clearInput(); std::cout << "Invalid input!\n"; continue; }

                        switch (action) {
                            case 1: {
                                int val;
                                std::cout << "Enter value: ";
                                std::cin >> val;
                                obj->add(val);
                                break;
                            }
                            case 2: obj->remove(); break;
                            case 3: obj->print(); break;
                            case 4: {
                                int i, v;
                                std::cout << "Enter index and value: ";
                                std::cin >> i >> v;
                                obj->setValue(i, v);
                                break;
                            }
                            case 5: {
                                int i;
                                std::cout << "Enter index: ";
                                std::cin >> i;
                                std::cout << "Value: " << obj->getValue(i) << "\n";
                                break;
                            }
                            case 6:
                                if (obj->getType() == "Deque") {
                                    int val;
                                    std::cout << "Enter value: ";
                                    std::cin >> val;
                                    dynamic_cast<Deque*>(obj)->addFront(val);
                                } else std::cout << "Not supported\n";
                                break;
                            case 7:
                                if (obj->getType() == "Deque") {
                                    dynamic_cast<Deque*>(obj)->removeBack();
                                } else std::cout << "Not supported\n";
                                break;
                            case 0: break;
                            default: std::cout << "Invalid choice!\n";
                        }
                    } while (action != 0);
                    break;
                }
                case 7: container.saveToFile("data.txt"); std::cout << "Saved.\n"; break;
                case 8: container.loadFromFile("data.txt"); std::cout << "Loaded.\n"; break;
                case 0: std::cout << "Exiting...\n"; break;
                default: std::cout << "Invalid choice!\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << "\n";
        }

    } while (choice != 0);

    return 0;
}