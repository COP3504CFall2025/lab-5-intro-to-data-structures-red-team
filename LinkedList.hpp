#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
	T data;
    Node* prev;
    Node* next;
	Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
		Node<T>* i = this->head;
		while(i != nullptr) {
			std::cout << i->data << std::endl;
			i = i->next;
		}
	}
	void printReverse() const {
		Node<T>* i = this->tail;
		while(i != nullptr) {
			std::cout << i->data << std::endl;
			i = i->prev;
		}
	};

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return this->count;
	};
	Node<T>* getHead() {
		return this->head;
	}
	const Node<T>* getHead() const {
		return this->head;
	}
	Node<T>* getTail() {
		return this->tail;
	}
	const Node<T>* getTail() const {
		return this->tail;
	}

	// Insertion
	void addHead(const T& data) {
		Node<T>* temp = new Node<T>(data);
		temp->next = this->head;
		temp->prev = nullptr;
		if(this->head) // if it exists, heads prev needs to point to temp
			this->head->prev = temp;
		else { // if its first element and doesnt exist then it just equals temp
			this->tail = temp;
		}
		this->head = temp;
		temp = nullptr; // avoid double delete and dangling ptr
		this->count++;
	}
	void addTail(const T& data) {
		Node<T>* temp = new Node<T>(data);
		temp->prev = this->tail;
		temp->next = nullptr;
		if(this->tail)
			this->tail->next = temp;
		else {
			this->head = temp;
		}
		this->tail = temp;
		temp = nullptr; // avoid DD and dangling ptr
		this->count++;
	}

	// Removal
	bool removeHead() {
		if(this->count == 0) {
			return false;
		}
		if(this->count == 1) {
			// last element
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
			count = 0;
			return true;
		}
		// otherwise normal situation
		Node<T>* temp = this->head;
		this->head = this->head->next;
		this->head->prev = nullptr;
		delete temp;
		this->count -= 1;
		return true;
	}
	bool removeTail() {
		if(this->count == 0)
			return false;
		if(this->count == 1) {
			// last element
			delete this->tail;
			this->tail = nullptr;
			this->head = nullptr;
			count = 0;
			return true;
		}
		// otherwise normal situation
		Node<T>* temp = this->tail;
		this->tail = this->tail->prev;
		this->tail->next = nullptr;
		delete temp;
		this->count -= 1;
		return true;
	}
	void clear() {
		Node<T>* i = this->head;
		while(i != nullptr && i->next != nullptr) {
			Node<T>* j = i->next;
			delete i;
			i = j;
		}
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		this->clear();
		this->head = other.getHead();
		this->tail = other.getTail();
		this->count = other.getCount();
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if(&rhs == this) {
			return *this;
		}
		if(rhs.head == nullptr) {
			this->head = nullptr;
			this->tail = nullptr;
			this->count = 0;
			return *this;
		}
		else {
			Node<T>* otherTemp = rhs.head;
			this->clear();
			while(otherTemp != nullptr) {
				this->addTail(otherTemp->data);
				otherTemp = otherTemp->next;
			}
			return *this;
		}
	}

	// Construction/Destruction
	LinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}
	LinkedList(const LinkedList<T>& list): head(nullptr), tail(nullptr) {
		if(list.head == nullptr) {
			this->head = nullptr;
			this->tail = nullptr;
			this->count = 0;
		}
		else {
			Node<T>* otherTemp = list.head;
			while(otherTemp != nullptr) {
				this->addTail(otherTemp->data);
				otherTemp = otherTemp->next;
			}
		}

	}
	LinkedList(LinkedList<T>&& other) noexcept {
		this->head = other.head;
		other.head = nullptr;
		this->tail = other.tail;
		other.tail = nullptr;
		this->count = other.count;
		other.count = 0;
	}
	~LinkedList() {
		this->clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;

};