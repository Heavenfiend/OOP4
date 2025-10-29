//
// Created by Егор on 10/29/2025.
//
#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <memory> // Для std::unique_ptr

template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;

    // Чисто виртуальные методы
    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;

    // Операторы
    virtual std::unique_ptr<Figure> clone() const = 0;
    virtual bool operator==(const Figure& other) const = 0;
    virtual operator double() const { return area(); }
};

#endif // FIGURE_H