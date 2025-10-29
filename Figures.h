//
// Created by Егор on 10/29/2025.
//
#ifndef FIGURES_H
#define FIGURES_H

#include "Figure.h" // Зависимость от базового класса
#include <memory> // Для std::unique_ptr
#include <cmath> // Для M_PI и тригонометрии

template<Scalar T>
class Rhombus : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertices[4];
    Point<T> center_point;

public:
    Rhombus(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
    Point<T> center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    std::unique_ptr<Figure<T>> clone() const override;
    bool operator==(const Figure<T>& other) const override;
};

template<Scalar T>
class Pentagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertices[5];
    Point<T> center_point;

public:
    Pentagon(Point<T> center, T radius);
    Point<T> center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    std::unique_ptr<Figure<T>> clone() const override;
    bool operator==(const Figure<T>& other) const override;
};

template<Scalar T>
class Hexagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertices[6];
    Point<T> center_point;

public:
    Hexagon(Point<T> center, T radius);
    Point<T> center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    std::unique_ptr<Figure<T>> clone() const override;
    bool operator==(const Figure<T>& other) const override;
};

#endif // FIGURES_H