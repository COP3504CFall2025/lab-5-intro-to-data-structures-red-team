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
        T temp = this->list.getHead()->data;
        this->list.removeHead();
        return temp;
    }
    T popBack() override {
        T temp = this->list.getTail()->data;
        this->list.removeTail();
        return temp;
    }

    // Element Accessors
    const T& front() const override {
        return this->list.getHead()->data;
    }
    const T& back() const override {
        return this->list.getTail()->data;
    }

    // Getter
    [[nodiscard]] std::size_t getSize() const noexcept override {
        return this->list.getCount();
    }
};






