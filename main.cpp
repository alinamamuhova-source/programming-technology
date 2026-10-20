#include <iostream>
#include <limits>
#include <clocale>
#include "Container.h"
#include "List.h"
#include "Deque.h"
#include "Stack.h"

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    setlocale(LC_ALL, "Russian"); // Включаем поддержку русского языка в консоли

    Container container;
    int choice;

    do {
        std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
        std::cout << "1. Добавить Список (List)\n";
        std::cout << "2. Добавить Дек (Deque)\n";
        std::cout << "3. Добавить Стек (Stack)\n";
        std::cout << "4. Удалить объект по индексу\n";
        std::cout << "5. Вывести все объекты\n";
        std::cout << "6. Работа с конкретным объектом\n";
        std::cout << "7. Сохранить в файл\n";
        std::cout << "8. Загрузить из файла\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            clearInput();
            std::cout << "Ошибка ввода! Введите число.\n";
            continue;
        }

        try {
            switch (choice) {
                case 1: container.addObject(new List()); break;
                case 2: container.addObject(new Deque()); break;
                case 3: container.addObject(new Stack()); break;
                case 4: {
                    int idx;
                    std::cout << "Введите индекс для удаления: ";
                    std::cin >> idx;
                    container.removeObject(idx);
                    std::cout << "Объект успешно удален.\n";
                    break;
                }
                case 5: container.printAll(); break;
                case 6: {
                    int idx;
                    std::cout << "Введите индекс объекта: ";
                    std::cin >> idx;
                    Base* obj = container.getObject(idx);
                    int action;
                    do {
                        std::cout << "\n-- Работа с объектом: " << obj->getType() << " --\n";
                        std::cout << "1. Добавить число\n";
                        std::cout << "2. Удалить число\n";
                        std::cout << "3. Вывести на экран\n";
                        std::cout << "4. Установить значение по индексу\n";
                        std::cout << "5. Получить значение по индексу\n";
                        if (obj->getType() == "Deque") std::cout << "6. Добавить в начало\n7. Удалить с конца\n";
                        std::cout << "0. Назад в главное меню\n";
                        std::cout << "Выберите действие: ";
                        std::cin >> action;

                        if (std::cin.fail()) { clearInput(); std::cout << "Ошибка ввода!\n"; continue; }

                        switch (action) {
                            case 1: {
                                int val;
                                std::cout << "Введите значение: ";
                                std::cin >> val;
                                obj->add(val);
                                break;
                            }
                            case 2: obj->remove(); break;
                            case 3: obj->print(); break;
                            case 4: {
                                int i, v;
                                std::cout << "Введите индекс и значение: ";
                                std::cin >> i >> v;
                                obj->setValue(i, v);
                                break;
                            }
                            case 5: {
                                int i;
                                std::cout << "Введите индекс: ";
                                std::cin >> i;
                                std::cout << "Значение: " << obj->getValue(i) << "\n";
                                break;
                            }
                            case 6:
                                if (obj->getType() == "Deque") {
                                    int val;
                                    std::cout << "Введите значение: ";
                                    std::cin >> val;
                                    dynamic_cast<Deque*>(obj)->addFront(val);
                                } else std::cout << "Действие не поддерживается для этого типа\n";
                                break;
                            case 7:
                                if (obj->getType() == "Deque") {
                                    dynamic_cast<Deque*>(obj)->removeBack();
                                } else std::cout << "Действие не поддерживается для этого типа\n";
                                break;
                            case 0: break;
                            default: std::cout << "Неверный пункт меню!\n";
                        }
                    } while (action != 0);
                    break;
                }
                case 7: container.saveToFile("data.txt"); std::cout << "Данные сохранены в файл.\n"; break;
                case 8: container.loadFromFile("data.txt"); std::cout << "Данные загружены из файла.\n"; break;
                case 0: std::cout << "Выход из программы...\n"; break;
                default: std::cout << "Неверный пункт меню!\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Перехвачено исключение: " << e.what() << "\n";
        }

    } while (choice != 0);

    return 0;
}