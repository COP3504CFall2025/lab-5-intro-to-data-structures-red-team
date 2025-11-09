#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() {
        this->capacity_ = 1;
        this->curr_size_ = 0;
        this->array_ = new T[this->capacity_];
    }
    explicit ABQ(const size_t capacity) {
        this->capacity_ = capacity;
        this->curr_size_ = 0;
        this->array_ = new T[this->capacity_];
    }
    ABQ(const ABQ& other) {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->array_ = new T[this->capacity_];

        // copy array
        for(size_t i = 0; i < this->curr_size_; i++) {
            this->array_[i] = other.array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs) {
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
            this->array[i] = rhs.array_[i];
        }
        return *this;
    }
    ABQ(ABQ&& other) noexcept {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->array_ = other.array_;
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
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
    ~ABQ() noexcept override {
        delete[] this->array_;
        this->array_ = nullptr;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return this->curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return this->capacity_;
    }
    [[nodiscard]] T* getData() const noexcept {
        return this->array_;
    }

    // Insertion
    void enqueue(const T& data) override {
        if(curr_size_ + 1 > capacity_) {
            // resize array
            this->capacity_ *= scale_factor_;
            T* newArr = new T[this->capacity_];
            
            // copy over to new array
            for(size_t i = 0; i < this->curr_size_; i++) {
                newArr[i] =  this->array_[i];
            }
            delete[] this->array_;
            this->array_ = newArr;
            newArr = nullptr;
        }
        this->array_[curr_size_++] = data;
    }

    // Access
    T peek() const override {
        if(this->curr_size_ == 0)
            throw std::runtime_error("");
        return this->array_[this->curr_size_ - 1];
    }

    // Deletion
    T dequeue() override {
        if(this->curr_size_ == 0) {
            throw std::runtime_error("");
        }

        this->curr_size_--;
        T* newArr = new T[this->capacity_];
        for(size_t i = 0; i < this->curr_size_; i++) {
            newArr[i] = this->array_[i + 1];
        }
        T front = this->array_[0];
        delete[] this->array_;
        this->array_ = newArr;
        newArr = nullptr;

        return front;
    }

};
