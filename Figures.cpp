//
// Created by Егор on 10/29/2025.
//
#include "Figures.h"
#include <iostream>

// --- Реализация Rhombus ---

template<Scalar T>
Rhombus<T>::Rhombus(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) {
    vertices[0] = std::make_unique<Point<T>>(p1);
    vertices[1] = std::make_unique<Point<T>>(p2);
    vertices[2] = std::make_unique<Point<T>>(p3);
    vertices[3] = std::make_unique<Point<T>>(p4);

    // Вычисляем центр как среднее арифметическое
    center_point.x = (p1.x + p2.x + p3.x + p4.x) / 4;
    center_point.y = (p1.y + p2.y + p3.y + p4.y) / 4;
}

template<Scalar T>
Point<T> Rhombus<T>::center() const {
    return center_point;
}

template<Scalar T>
double Rhombus<T>::area() const {
    // Площадь ромба через диагонали
    T d1_x = vertices[2]->x - vertices[0]->x;
    T d1_y = vertices[2]->y - vertices[0]->y;
    T d2_x = vertices[3]->x - vertices[1]->x;
    T d2_y = vertices[3]->y - vertices[1]->y;

    double len1 = std::sqrt(d1_x*d1_x + d1_y*d1_y);
    double len2 = std::sqrt(d2_x*d2_x + d2_y*d2_y);

    return (len1 * len2) / 2.0;
}

template<Scalar T>
void Rhombus<T>::print(std::ostream& os) const {
    os << "Rhombus:\n";
    os << "  Vertices: ";
    for (int i = 0; i < 4; ++i) {
        os << "(" << vertices[i]->x << ", " << vertices[i]->y << ") ";
    }
    os << "\n";
    os << "  Center: (" << center_point.x << ", " << center_point.y << ")\n";
    os << "  Area: " << area() << "\n";
}

template<Scalar T>
std::unique_ptr<Figure<T>> Rhombus<T>::clone() const {
    return std::make_unique<Rhombus<T>>(*vertices[0], *vertices[1], *vertices[2], *vertices[3]);
}

template<Scalar T>
bool Rhombus<T>::operator==(const Figure<T>& other) const {
    const auto* other_rhombus = dynamic_cast<const Rhombus<T>*>(&other);
    if (!other_rhombus) return false;
    for (int i = 0; i < 4; ++i) {
        if (*vertices[i] != *other_rhombus->vertices[i]) return false;
    }
    return true;
}

// --- Реализация Pentagon ---

template<Scalar T>
Pentagon<T>::Pentagon(Point<T> center, T radius) : center_point(center) {
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * M_PI * i / 5;
        T x = center.x + radius * static_cast<T>(std::cos(angle));
        T y = center.y + radius * static_cast<T>(std::sin(angle));
        vertices[i] = std::make_unique<Point<T>>(x, y);
    }
}

template<Scalar T>
Point<T> Pentagon<T>::center() const {
    return center_point;
}

template<Scalar T>
double Pentagon<T>::area() const {
    T dx = vertices[0]->x - center_point.x;
    T dy = vertices[0]->y - center_point.y;
    double r = std::sqrt(dx*dx + dy*dy);
    return 0.5 * 5 * r * r * std::sin(2 * M_PI / 5);
}

template<Scalar T>
void Pentagon<T>::print(std::ostream& os) const {
    os << "Pentagon:\n";
    os << "  Vertices: ";
    for (int i = 0; i < 5; ++i) {
        os << "(" << vertices[i]->x << ", " << vertices[i]->y << ") ";
    }
    os << "\n";
    os << "  Center: (" << center_point.x << ", " << center_point.y << ")\n";
    os << "  Area: " << area() << "\n";
}

template<Scalar T>
std::unique_ptr<Figure<T>> Pentagon<T>::clone() const {
    T dx = vertices[0]->x - center_point.x;
    T dy = vertices[0]->y - center_point.y;
    T radius = static_cast<T>(std::sqrt(dx*dx + dy*dy));
    return std::make_unique<Pentagon<T>>(center_point, radius);
}

template<Scalar T>
bool Pentagon<T>::operator==(const Figure<T>& other) const {
    const auto* other_pentagon = dynamic_cast<const Pentagon<T>*>(&other);
    if (!other_pentagon) return false;
    if (center_point != other_pentagon->center_point) return false;
    T dx1 = vertices[0]->x - center_point.x;
    T dy1 = vertices[0]->y - center_point.y;
    T dx2 = other_pentagon->vertices[0]->x - other_pentagon->center_point.x;
    T dy2 = other_pentagon->vertices[0]->y - other_pentagon->center_point.y;
    T r1 = static_cast<T>(std::sqrt(dx1*dx1 + dy1*dy1));
    T r2 = static_cast<T>(std::sqrt(dx2*dx2 + dy2*dy2));
    return r1 == r2;
}

// --- Реализация Hexagon ---

template<Scalar T>
Hexagon<T>::Hexagon(Point<T> center, T radius) : center_point(center) {
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * M_PI * i / 6;
        T x = center.x + radius * static_cast<T>(std::cos(angle));
        T y = center.y + radius * static_cast<T>(std::sin(angle));
        vertices[i] = std::make_unique<Point<T>>(x, y);
    }
}

template<Scalar T>
Point<T> Hexagon<T>::center() const {
    return center_point;
}

template<Scalar T>
double Hexagon<T>::area() const {
    T dx = vertices[0]->x - center_point.x;
    T dy = vertices[0]->y - center_point.y;
    double r = std::sqrt(dx*dx + dy*dy);
    return (3 * std::sqrt(3) / 2) * r * r;
}

template<Scalar T>
void Hexagon<T>::print(std::ostream& os) const {
    os << "Hexagon:\n";
    os << "  Vertices: ";
    for (int i = 0; i < 6; ++i) {
        os << "(" << vertices[i]->x << ", " << vertices[i]->y << ") ";
    }
    os << "\n";
    os << "  Center: (" << center_point.x << ", " << center_point.y << ")\n";
    os << "  Area: " << area() << "\n";
}

template<Scalar T>
std::unique_ptr<Figure<T>> Hexagon<T>::clone() const {
    T dx = vertices[0]->x - center_point.x;
    T dy = vertices[0]->y - center_point.y;
    T radius = static_cast<T>(std::sqrt(dx*dx + dy*dy));
    return std::make_unique<Hexagon<T>>(center_point, radius);
}

template<Scalar T>
bool Hexagon<T>::operator==(const Figure<T>& other) const {
    const auto* other_hexagon = dynamic_cast<const Hexagon<T>*>(&other);
    if (!other_hexagon) return false;
    if (center_point != other_hexagon->center_point) return false;
    T dx1 = vertices[0]->x - center_point.x;
    T dy1 = vertices[0]->y - center_point.y;
    T dx2 = other_hexagon->vertices[0]->x - other_hexagon->center_point.x;
    T dy2 = other_hexagon->vertices[0]->y - other_hexagon->center_point.y;
    T r1 = static_cast<T>(std::sqrt(dx1*dx1 + dy1*dy1));
    T r2 = static_cast<T>(std::sqrt(dx2*dx2 + dy2*dy2));
    return r1 == r2;
}

// Явная инстанцировка шаблонов для компиляции в отдельном файле
// Обычно в .cpp файле шаблона не инстанцируются, но если компилятор ругается
// на отсутствие определений при линковке, можно добавить явные инстанцировки.
// Пример для int:
template class Rhombus<int>;
template class Pentagon<int>;
template class Hexagon<int>;