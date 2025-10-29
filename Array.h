//
// Created by Егор on 10/29/2025.
//
#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>

template<typename T>
class Array {
private:
    std::unique_ptr<T[]> data;
    size_t size_{0};
    size_t capacity_{0};

    void resize(size_t new_capacity) {
        if (new_capacity <= capacity_) return;

        auto new_data = std::make_unique<T[]>(new_capacity);

        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data[i]);
        }

        data = std::move(new_data);
        capacity_ = new_capacity;
    }

public:
    Array() = default;

    explicit Array(size_t initial_capacity) {
        if (initial_capacity > 0) {
            data = std::make_unique<T[]>(initial_capacity);
            capacity_ = initial_capacity;
        }
    }

    void push_back(const T& item) {
        if (size_ >= capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            resize(new_cap);
        }
        data[size_++] = item;
    }

    void remove(size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < size_ - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size_;
    }

    T& operator[](size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
};

#endif