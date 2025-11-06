#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() {
        this->list = new LinkedList<T>();
    }

    // Insertion
    void push(const T& item) override {
        this->list.addTail(item);
    }

    // Deletion
    T pop() override {
        T temp = this->list.getTail();
        this->list.removeTail();
        return temp;
    }

    // Access
    T peek() const override {
        return this->list.getTail();
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return this->list.getCount();
    }
};