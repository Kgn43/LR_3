#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Node.h"
using namespace std;

template<typename T>
class Queue{
public:
    Node<T>* head;
    Node<T>* tail;
    size_t size;

    Queue() : head(nullptr), tail(nullptr), size(0) {}

    Queue(size_t len) : head(nullptr), tail(nullptr), size(0) {
        for (size_t i = 0; i < len; ++i) {
            this->push(T());
        }
    }

    void push(T val);
    void pop();
    T getFirst();

    friend ostream& operator<<(ostream& os, const Queue& que) {
        Node<T>* curr = que.head;
        while (curr != nullptr){
            os << "[" << curr->value << "]";
            if (curr->next != nullptr) {
                os << " -> ";
            }
            curr = curr->next;
        }
        return os;
    }

    T& operator[](const size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        auto tmp = this->head;
        for (int i = 0; i != index; ++i) {
            tmp = tmp->next;
        }
        return tmp->value;
    }

};


template struct Queue<int>;
template struct Queue<string>;

Queue<string> splitToQueue(const string &input, char delimiter = ' ');
string unSplitQueue(const Queue<string>& input, char delimiter = ' ');

#endif // QUEUE_H
