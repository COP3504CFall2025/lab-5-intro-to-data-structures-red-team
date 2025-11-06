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
        this->list = new LinkedList<T>();
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
        this->list.removeHead();
    }
    T popBack() override {
        this->list.removeTail();
    }

    // Element Accessors
    const T& front() const override {
        return this->list.getHead();
    }
    const T& back() const override {
        return this->list.getTail();
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return this->list.getCount();
    }
};






