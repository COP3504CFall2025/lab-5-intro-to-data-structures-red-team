#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
        this->size_ = 0;
        this->capacity_ = 4;
        this->data_ = new T[this->capacity_];
        this->front_ = 0;
        this->back_ = 0;
    }
    explicit ABDQ(std::size_t capacity) {
        this->size_ = 0;
        this->capacity_ = capacity;
        this->data_ = new T[this->capacity_];
        this->front_ = 0;
        this->back_ = 0;
    }
    ABDQ(const ABDQ& other) {
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        this->data_ = new T[this->capacity_];
        this->front_ = 0;
        this->back_ = this->size_ - 1;

        // copy in new order
        for(size_t i = 0; i < this->size_; i++) {
            this->data_[i] = other.data_[(other.front_ + i) % this->capacity_];
        }
    }
    ABDQ(ABDQ&& other) noexcept {
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        this->data_ = other.data_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        other.data_ = nullptr;
    }
    ABDQ& operator=(const ABDQ& other) {
        if(this == &other) {
            return *this;
        }
        if(this->data_)
            delete[] this->data_;
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        this->data_ = new T[this->capacity_];
        this->front_ = 0;
        this->back_ = this->size_ - 1;

        // copy in new order
        for(size_t i = 0; i < this->size_; i++) {
            this->data_[i] = other.data_[(other.front_ + i) % this->capacity_];
        }
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if(this == &other)
            return *this;
        if(this->data_)
            delete[] this->data_;
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        this->data_ = other.data_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        other.data_ = nullptr;
    }
    ~ABDQ() override {
        delete[] this->data_;
    }

    // Insertion
    void pushFront(const T& item) override { // push to the left of front_
        if(this->size_ + 1 > capacity_) {
            // resize to fit new item and reorder
            T* newArr = new T[this->capacity_ * SCALE_FACTOR];

            // copy in new order
            for(size_t i = 0; i < this->size_; i++) {
                newArr[i] = this->data_[(this->front_ + i) % capacity_];
            }
            this->front_ = 0;
            this->back_ = this->size_ - 1;
            this->capacity_ *= SCALE_FACTOR;
            delete[] this->data_;
            this->data_ = newArr;
            newArr = nullptr;
        }
        this->front_ = ((this->front_ - 1) + this->capacity_) % this->capacity_; // move front back one
        if(this->size_ == 0) { // first element will become both the front and back
            this->back_ = this->front_;
        }
        this->data_[this->front_] = item;
        this->size_++;
    }
    void pushBack(const T& item) override {
        if(this->size_ + 1 > capacity_) {
            // resize to fit new item and reorder
            T* newArr = new T[this->capacity_ * SCALE_FACTOR];

            // copy in new order
            for(size_t i = 0; i < this->size_; i++) {
                newArr[i] = this->data_[(this->front_ + i) % capacity_];
            }
            this->front_ = 0;
            this->back_ = this->size_ - 1;
            this->capacity_ *= SCALE_FACTOR;
            delete[] this->data_;
            this->data_ = newArr;
            newArr = nullptr;
        }
        this->back_ = (this->back_ + 1) % this->capacity_;
        if(this->size_ == 0) { // first element will become both the front and back
            this->front_ = this->back_;
        }
        this->data_[this->back_] = item;
        this->size_++;
    }

    // Deletion
    // is it okay to leave the data in the array and just create the illusion that it's inaccessible garbage outside of this class?
    T popFront() override {
        if(this->size_ == 0)
            throw std::runtime_error("");
        T front = this->data_[this->front_];
        this->front_ = (this->front_ + 1) % this->capacity_;
        this->size_--;
        return front;
    }
    T popBack() override {
        if(this->size_ == 0)
            throw std::runtime_error("");
        T back = this->data_[this->back_];
        this->back_ = (this->back_ - 1 + this->capacity_) % this->capacity_;
        this->size_--;
        return back;
    }

    // Access
    const T& front() const override {
        if(this->size_ == 0)
            throw std::runtime_error("");
        return this->data_[this->front_];
    }
    const T& back() const override {
        if(this->size_ == 0)
            throw std::runtime_error("");
        return this->data_[this->back_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return this->size_;
    }

};
