#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() {
        this->list = LinkedList<T>();
    }

    // Core Insertion Operations
    void pushFront(const T& item) override {
        this->list.addHead(item);
    }
    void pushBack(const T& item) override {
        this->list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if(this->list.getCount() == 0)
            throw std::runtime_error("");
        T temp = this->list.getHead()->data;
        this->list.removeHead();
        return temp;
    }
    T popBack() override {
        if(this->list.getCount() == 0)
            throw std::runtime_error("");
        T temp = this->list.getTail()->data;
        this->list.removeTail();
        return temp;
    }

    // Element Accessors
    const T& front() const override {
        if(this->list.getCount() == 0)
            throw std::runtime_error("");
        return this->list.getHead()->data;
    }
    const T& back() const override {
        if(this->list.getCount() == 0)
            throw std::runtime_error("");
        return this->list.getTail()->data;
    }

    // Getter
    [[nodiscard]] std::size_t getSize() const noexcept override {
        return this->list.getCount();
    }
};






