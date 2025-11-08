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
        this->list = std::move(LinkedList<T>());
    }

    // Insertion
    void push(const T& item) override {
        this->list.addTail(item);
    }

    // Deletion
    T pop() override {
        if(this->list.getCount() == 0)
            throw std::runtime_error("");
        T temp = this->list.getTail()->data;
        this->list.removeTail();
        return temp;
    }

    // Access
    T peek() const override {
        if(this->list.getCount() == 0)
            throw std::runtime_error("");
        return this->list.getTail()->data;
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return this->list.getCount();
    }
};