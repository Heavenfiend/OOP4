// Made by egor 29 10 2025
//
//
#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include <utility>

// шаблонный динамический массив
template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data;  // сам массив
    size_t size_ = 0;           // текущий размер
    size_t capacity_ = 0;       // вместимость

    // увеличиваем размер массива
    void resize(size_t new_capacity) {
        if (new_capacity <= capacity_) return;

        // создаем новый массив побольше
        auto new_data = std::shared_ptr<T[]>(new T[new_capacity]);

        // перемещаем старые элементы
        for(size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data[i]);  // перемещаем а не копируем
        }

        data = std::move(new_data);  // заменяем старый массив
        capacity_ = new_capacity;
    }

public:
    Array() = default;

    // конструктор с начальной вместимостью
    explicit Array(size_t initial_capacity) {
        if (initial_capacity > 0) {
            data = std::shared_ptr<T[]>(new T[initial_capacity]);
            capacity_ = initial_capacity;
        }
    }

    // добавление в конец по константной ссылке
    void push_back(const T& item) {
        if(size_ >= capacity_) {
            resize(capacity_ == 0 ? 2 : capacity_ * 2);  // увеличиваем если надо
        }
        data[size_++] = item;
    }

    // добавление с перемещением
    void push_back(T&& item) {
        if(size_ >= capacity_) {
            resize(capacity_ == 0 ? 2 : capacity_ * 2);
        }
        data[size_++] = std::move(item);  // перемещаем
    }

    // удаление по индексу
    void remove(size_t index) {
        if(index >= size_) throw std::out_of_range("Index out of range");

        // сдвигаем элементы
        for(size_t i = index; i < size_ - 1; ++i) {
            data[i] = std::move(data[i + 1]);  // перемещаем при сдвиге
        }
        --size_;
    }

    // доступ по индексу
    T& operator[](size_t index) {
        if(index >= size_) throw std::out_of_range("Index out of range");
        return data[index];
    }

    // константный доступ
    const T& operator[](size_t index) const {
        if(index >= size_) throw std::out_of_range("Index out of range");
        return data[index];
    }

    // геттеры
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
};

#endif