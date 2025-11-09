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
        this->capacity_ = 1;
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
        for(size_t i = 0; i < this->curr_size_; i++) {
            this->array_[i] = other.array_[i];
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
        for(size_t i = 0; i < this->curr_size_; i++) {
            this->array_[i] = rhs.array_[i];
        }
        return *this;
    }
    ABS(ABS&& other) noexcept {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->array_ = other.array_;
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
    }
    ABS& operator=(ABS&& rhs) noexcept {
        if(this == &rhs)
            return *this;
        if(this->array_)
            delete[] this->array_;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        this->array_ = rhs.array_;
        rhs.array_ = nullptr;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;
        return *this;
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
        if(this->curr_size_ + 1 > this->capacity_) {
            // resize array
            T* newArr = new T[this->capacity_ * scale_factor_];
            
            // copy over to new array
            for(size_t i = 0; i < this->curr_size_; i++) {
                newArr[i] =  this->array_[i];
            }
            this->capacity_ *= scale_factor_;
            delete[] this->array_;
            this->array_ = newArr;
            newArr = nullptr;
        }
        this->array_[curr_size_++] = data;
    }

    T peek() const override {
        if(this->curr_size_ == 0)
            throw std::runtime_error("");
        return this->array_[this->curr_size_ - 1];
    }

    T pop() override {
        if(this->curr_size_ == 0)
            throw std::runtime_error("");
        this->curr_size_--;
        if (static_cast<double>(this->capacity_) / static_cast<double>(scale_factor_) <= static_cast<double>(this->curr_size_)) {
            this->capacity_ /= scale_factor_;
        }
        return this->array_[this->curr_size_];
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
