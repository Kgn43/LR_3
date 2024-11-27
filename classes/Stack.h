#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "Node.h"
using std::ostream, std::string, std::cout, std::endl;

template <typename T>
class Stack{
public:
    Node<T>* head;
    size_t size;

    Stack() : head(nullptr), size(0) {}
    Stack(size_t len) : head(nullptr), size(0) {
        for (size_t i = 0; i < len; ++i) {
            this->push(T());
        }
    }

    friend ostream& operator<<(ostream& os, const Stack<T>& st) {
        auto curr = st.head;
        while (curr != nullptr){
            os << "[" << curr->value << "]";
            if (curr->next != nullptr) {
                os << " -> ";
            }
            curr = curr->next;
        }
        return os;
    }

    T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        auto tmp = this->head;
        for (int i = 0; i != index; ++i) {
            tmp = tmp->next;
        }
        return tmp->value;
    }

    void push(T val);
    void pop();
    T getLast();

};


template struct Stack<int>;
template struct Stack<char>;
template struct Stack<string>;


Stack<string> splitToStack(const string &input, char delimiter = ' ');
string unSplitStack(const Stack<string> &input, char delimiter = ' ');

#endif // STACK_H
