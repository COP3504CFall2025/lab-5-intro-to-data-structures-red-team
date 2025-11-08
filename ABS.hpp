#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() {
        this->curr_size_ = 0;
        this->capacity_ = 4;
        this->array_ = new T[this->capacity_];
    }
    explicit ABS(const size_t capacity) {
        this->curr_size_ = 0;
        this->capacity_ = capacity;
        this->array_ = new T[this->capacity_];
    }
    ABS(const ABS& other) {
        this->curr_size_ = other.curr_size_;
        this->capacity_ = other.capacity_;
        this->array_ = new T[this->capacity_];

        // copy array
        for(int i = 0; i < this->curr_size_; i++) {
            this->array[i] = other.array_[i];
        }
    }
    ABS& operator=(const ABS& rhs) {
        if(this == &rhs) {
            return *this;
        }
        if(this->array_)
            delete[] this->array_;

        this->curr_size_ = rhs.curr_size_;
        this->capacity_ = rhs.capacity_;
        this->array_ = new T[this->capacity_];

        // copy array
        for(int i = 0; i < this->curr_size_; i++) {
            this->array[i] = rhs.array_[i];
        }
    }
    ABS(ABS&& other) noexcept {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.size;
        this->array_ = other.array_;
        other.array_ = nullptr;
    }
    ABS& operator=(ABS&& rhs) noexcept {
        if(this == &rhs)
            return *this;
        if(this->array_)
            delete[] this->array_;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.size;
        this->array_ = rhs.array_;
        rhs.array_ = nullptr;
    }
    ~ABS() noexcept override {
        delete[] this->array_;
        this->array_ = nullptr;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return this->curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return this->capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return this->array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if(curr_size_ + 1 > capacity_) {
            // resize array
            this->capacity_ *= this->scale_factor_;
            T* newArr = new T[this->capacity_];
            
            // copy over to new array
            for(int i = 0; i < this->curr_size_; i++) {
                newArr[i] =  this->array_[i];
            }
            delete[] this->array_;
            this->array_ = newArr;
            newArr = nullptr;
        }
        this->array_[curr_size_++] = data;
    }

    T peek() const override {
        if(this->curr_size_ == 0)
            throw std::runtime_error("Empty");
        return this->array_[this->curr_size_ - 1];
    }

    T pop() override {
        if(this->curr_size_ == 0)
            throw std::runtime_error("Empty");
        return this->array_[--this->curr_size_];
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
