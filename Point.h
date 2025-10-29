//
// Created by Егор on 10/29/2025.
//

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <type_traits> // Для std::is_arithmetic_v

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<Scalar T>
class Point {
public:
    T x, y;

    Point(T x = 0, T y = 0) : x(x), y(y) {}

    // Операторы для сравнения
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

#endif // POINT_H