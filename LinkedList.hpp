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
		Node<T>* i = this->getHead();
		while(i != nullptr) {
			std::cout << i->data << std::endl;
			i = i->next;
		}
	}
	void printReverse() const {
		Node<T>* i = this->getTail();
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
		temp->data = data;
		if(this->head) // if it exists, heads prev needs to point to temp
			this->head->prev = temp;
		else { // if its first element and doesnt exist then it just equals temp
			this->head = temp;
			this->tail = temp;
		}
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
			this->tail = temp;
			this->head = temp;
		}
		temp = nullptr; // avoid DD and dangling ptr
		this->count++;
	}

	// Removal
	bool removeHead() {
		if(this->head == nullptr)
			return false;
		this->head = this->head->next;
		delete this->head->prev;
		this->head->prev = nullptr;
		if(this->head == nullptr)
			this->tail = nullptr;
		this->count--;
		return true;
	}
	bool removeTail() {
		if(this->tail == nullptr)
			return false;
		this->tail = this->tail->prev;
		delete this->tail->next;
		this->tail->next = nullptr;
		if(this->tail == nullptr)
			this->head = nullptr;
		this->count--;
		return true
	}
	void clear() {
		Node<T>* i = this->head;
		while(i != nullptr) {
			delete i;
			i = i->next;
		}
		this->count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		this->head = other.getHead();
		this->tail = other.getTail();
		this->count = other.getCount();
		other.head = nullptr;
		other.tail = nullptr;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if(&rhs == this) {
			return *this;
		}
		if(rhs.head == nullptr) {
			this->head = nullptr;
			this->tail = nullptr;
			this->count = 0;
		}
		else {
			this->head = new Node(rhs.getHead()->data);
			this->count = rhs.getCount();

			Node* thisTemp = this->head->next;
			Node* otherTemp = rhs.head->next;
			while(otherTemp != nullptr) {
				thisTemp = new Node(rhs.data);
				thisTemp = thisTemp->next;
				otherTemp = otherTemp->next;
			}
			this->tail = thisTemp;
			return *this;
		}
	}

	// Construction/Destruction
	LinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}
	LinkedList(const LinkedList<T>& list) {
		if(list.head == nullptr) {
			this->head = nullptr;
			this->tail = nullptr;
			this->count = 0;
		}
		else {
			this->head = new Node<T>(list.getHead()->data);
			this->count = list.getCount();
			Node<T>* otherTemp = list.head->next;
			Node<T>* thisTemp = this->head->next;

			while(otherTemp != nullptr) {
				thisTemp = new Node(otherTemp->data);
				thisTemp = thisTemp->next;
				otherTemp = otherTemp->next;
			}
			this->tail = thisTemp;
		}

	}
	LinkedList(LinkedList<T>&& other) noexcept {
		this->head = other.head;
		other.head = nullptr;
		this->tail = other.tail;
		other.tail = nullptr;
		this->count = other.count;
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