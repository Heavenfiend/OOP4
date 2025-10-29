#include "Array.h"
#include "Figures.h"
#include <iostream>
#include <memory> // Для std::shared_ptr, std::make_shared
#include <limits> // Для std::numeric_limits

// Вспомогательная функция для очистки буфера ввода
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Array<std::shared_ptr<Figure<int>>> figures;

    // --- Ввод начальных фигур ---
    std::cout << "Enter number of figures to create initially: ";
    int n;
    while (!(std::cin >> n) || n < 0) {
        std::cout << "Invalid input. Please enter a non-negative integer: ";
        clearInputBuffer();
    }

    for (int i = 0; i < n; ++i) {
        std::string type;
        std::cout << "Enter figure type (Rhombus, Pentagon, Hexagon): ";
        std::cin >> type;

        if (type == "Rhombus") {
            int x1, y1, x2, y2, x3, y3, x4, y4;
            std::cout << "Enter 4 vertices (x1 y1 x2 y2 x3 y3 x4 y4): ";
            if (!(std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4)) {
                std::cout << "Invalid input for coordinates. Skipping this figure.\n";
                clearInputBuffer();
                --i;
                continue;
            }
            auto fig = std::make_shared<Rhombus<int>>(Point<int>(x1, y1), Point<int>(x2, y2), Point<int>(x3, y3), Point<int>(x4, y4));
            figures.push_back(fig);
        } else if (type == "Pentagon") {
            int cx, cy, r;
            std::cout << "Enter center (cx cy) and radius: ";
            if (!(std::cin >> cx >> cy >> r) || r < 0) {
                std::cout << "Invalid input for center or radius. Skipping this figure.\n";
                clearInputBuffer();
                --i;
                continue;
            }
            auto fig = std::make_shared<Pentagon<int>>(Point<int>(cx, cy), r);
            figures.push_back(fig);
        } else if (type == "Hexagon") {
            int cx, cy, r;
            std::cout << "Enter center (cx cy) and radius: ";
            if (!(std::cin >> cx >> cy >> r) || r < 0) {
                std::cout << "Invalid input for center or radius. Skipping this figure.\n";
                clearInputBuffer();
                --i;
                continue;
            }
            auto fig = std::make_shared<Hexagon<int>>(Point<int>(cx, cy), r);
            figures.push_back(fig);
        } else {
            std::cout << "Unknown figure type: " << type << ". Please try again.\n";
            --i;
        }
    }

    int choice;
    do {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Print all figures\n";
        std::cout << "2. Print total area\n";
        std::cout << "3. Remove a figure by index\n";
        std::cout << "4. Add a new figure\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                if (figures.size() == 0) {
                    std::cout << "No figures to display.\n";
                    break;
                }
                std::cout << "\n--- All Figures ---\n";
                for (size_t i = 0; i < figures.size(); ++i) {
                    std::cout << "Index [" << i << "]: ";
                    figures[i]->print(std::cout);
                    std::cout << "\n";
                }
                break;
            }
            case 2: {
                double total_area = 0.0;
                for (size_t i = 0; i < figures.size(); ++i) {
                    total_area += static_cast<double>(*figures[i]);
                }
                std::cout << "Total area: " << total_area << "\n";
                break;
            }
            case 3: {
                if (figures.size() == 0) {
                    std::cout << "No figures to remove.\n";
                    break;
                }
                std::cout << "Current number of figures: " << figures.size() << "\n";
                size_t index_to_remove;
                std::cout << "Enter index of figure to remove (0-" << figures.size()-1 << "): ";
                if (!(std::cin >> index_to_remove)) {
                    std::cout << "Invalid input for index.\n";
                    clearInputBuffer();
                    break;
                }
                try {
                    figures.remove(index_to_remove);
                    std::cout << "Figure removed successfully.\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 4: {
                std::string type;
                std::cout << "Enter figure type to add (Rhombus, Pentagon, Hexagon): ";
                std::cin >> type;

                if (type == "Rhombus") {
                    int x1, y1, x2, y2, x3, y3, x4, y4;
                    std::cout << "Enter 4 vertices (x1 y1 x2 y2 x3 y3 x4 y4): ";
                    if (!(std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4)) {
                        std::cout << "Invalid input for coordinates.\n";
                        clearInputBuffer();
                        break;
                    }
                    auto fig = std::make_shared<Rhombus<int>>(Point<int>(x1, y1), Point<int>(x2, y2), Point<int>(x3, y3), Point<int>(x4, y4));
                    figures.push_back(fig);
                    std::cout << "Rhombus added.\n";
                } else if (type == "Pentagon") {
                    int cx, cy, r;
                    std::cout << "Enter center (cx cy) and radius: ";
                    if (!(std::cin >> cx >> cy >> r) || r < 0) {
                        std::cout << "Invalid input for center or radius.\n";
                        clearInputBuffer();
                        break;
                    }
                    auto fig = std::make_shared<Pentagon<int>>(Point<int>(cx, cy), r);
                    figures.push_back(fig);
                    std::cout << "Pentagon added.\n";
                } else if (type == "Hexagon") {
                    int cx, cy, r;
                    std::cout << "Enter center (cx cy) and radius: ";
                    if (!(std::cin >> cx >> cy >> r) || r < 0) {
                        std::cout << "Invalid input for center or radius.\n";
                        clearInputBuffer();
                        break;
                    }
                    auto fig = std::make_shared<Hexagon<int>>(Point<int>(cx, cy), r);
                    figures.push_back(fig);
                    std::cout << "Hexagon added.\n";
                } else {
                    std::cout << "Unknown figure type: " << type << ".\n";
                }
                break;
            }
            case 0:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}