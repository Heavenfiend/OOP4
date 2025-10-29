#include <iostream>
#include <memory>
#include "Array.h"
#include "Figures.h"
// очистка буфера ввода

void clearInput() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

// функция добавления новой фигуры
void addFigure(Array<std::shared_ptr<Figure<double>>>& figures) {
    std::cout << "введите тип фигуры (Rhombus/Pentagon/Hexagon): ";
    std::string type;
    std::cin >> type;

    std::cout << "введите центр (x y) и радиус: ";
    double x, y, r;
    if(std::cin >> x >> y >> r) {
        Point<double> center(x, y);

        if(type == "Rhombus") {
            figures.push_back(std::make_shared<Rhombus<double>>(center, r));
            std::cout << "ромб добавлен!\n";
        } else if(type == "Pentagon") {
            figures.push_back(std::make_shared<Pentagon<double>>(center, r));
            std::cout << "пятиугольник добавлен!\n";
        } else if(type == "Hexagon") {
            figures.push_back(std::make_shared<Hexagon<double>>(center, r));
            std::cout << "шестиугольник добавлен!\n";
        } else {
            std::cout << "неизвестный тип! доступно: Rhombus, Pentagon, Hexagon\n";
        }
    } else {
        std::cout << "неверный ввод!\n";
        clearInput();
    }
}

int main() {
    system("chcp 65001");
    Array<std::shared_ptr<Figure<double>>> figures;

    std::cout << "сколько фигур создать изначально? ";
    int n;
    std::cin >> n;

    // создание начальных фигур
    for(int i = 0; i < n; ++i) {
        std::cout << "фигура " << i+1 << " - введите тип (Rhombus/Pentagon/Hexagon): ";
        std::string type;
        std::cin >> type;

        std::cout << "введите центр (x y) и радиус: ";
        double x, y, r;
        if(std::cin >> x >> y >> r) {
            Point<double> center(x, y);

            if(type == "Rhombus") {
                figures.push_back(std::make_shared<Rhombus<double>>(center, r));
            } else if(type == "Pentagon") {
                figures.push_back(std::make_shared<Pentagon<double>>(center, r));
            } else if(type == "Hexagon") {
                figures.push_back(std::make_shared<Hexagon<double>>(center, r));
            } else {
                std::cout << "неизвестный тип! доступно: Rhombus, Pentagon, Hexagon\n";
                --i;
            }
        } else {
            std::cout << "неверный ввод!\n";
            clearInput();
            --i;
        }
    }

    int choice;
    do {
        std::cout << "\n=== меню ===\n";
        std::cout << "1. показать все фигуры\n";
        std::cout << "2. вычислить общую площадь\n";
        std::cout << "3. удалить фигуру по индексу\n";
        std::cout << "4. добавить новую фигуру\n";
        std::cout << "0. выход\n";
        std::cout << "выбор: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                if(figures.size() == 0) {
                    std::cout << "нет фигур для отображения.\n";
                } else {
                    std::cout << "\n--- все фигуры ---\n";
                    for(size_t i = 0; i < figures.size(); ++i) {
                        std::cout << "[" << i << "]: " << *figures[i] << std::endl;
                    }
                }
                break;

            case 2:
                if(figures.size() == 0) {
                    std::cout << "нет фигур для вычисления площади.\n";
                } else {
                    double total = 0;
                    for(size_t i = 0; i < figures.size(); ++i) {
                        total += static_cast<double>(*figures[i]);
                    }
                    std::cout << "общая площадь всех фигур: " << total << std::endl;
                }
                break;

            case 3:
                if(figures.size() == 0) {
                    std::cout << "нет фигур для удаления.\n";
                } else {
                    std::cout << "текущее количество фигур: " << figures.size() << std::endl;
                    std::cout << "введите индекс для удаления (0-" << figures.size()-1 << "): ";
                    size_t idx;
                    if(std::cin >> idx && idx < figures.size()) {
                        figures.remove(idx);
                        std::cout << "фигура удалена!\n";
                    } else {
                        std::cout << "неверный индекс!\n";
                        clearInput();
                    }
                }
                break;

            case 4:
                addFigure(figures);
                break;

            case 0:
                std::cout << "выход из программы. пока!\n";
                break;

            default:
                std::cout << "неверный выбор! попробуйте снова.\n";
                break;
        }
    } while(choice != 0);

    // демонстрация работы с разными массивами
    std::cout << "\n--- тестирование array с разными типами ---\n";

    Array<std::shared_ptr<Figure<double>>> figure_ptrs;
    figure_ptrs.push_back(std::make_shared<Rhombus<double>>(Point<double>(0,0), 5));
    figure_ptrs.push_back(std::make_shared<Pentagon<double>>(Point<double>(1,1), 3));

    std::cout << "array<std::shared_ptr<figure<double>>> содержимое:\n";
    for(size_t i = 0; i < figure_ptrs.size(); ++i) {
        std::cout << "[" << i << "]: " << *figure_ptrs[i] << std::endl;
    }

    Array<std::shared_ptr<Rhombus<double>>> rhombus_array;
    rhombus_array.push_back(std::make_shared<Rhombus<double>>(Point<double>(2,2), 4));
    rhombus_array.push_back(std::make_shared<Rhombus<double>>(Point<double>(3,3), 2));

    std::cout << "\narray<std::shared_ptr<rhombus<double>>> содержимое:\n";
    for(size_t i = 0; i < rhombus_array.size(); ++i) {
        std::cout << "[" << i << "]: " << *rhombus_array[i] << std::endl;
    }

    std::cout << "программа завершена успешно!" << std::endl;
    return 0;
}