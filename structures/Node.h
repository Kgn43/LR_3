#ifndef NODE_H
#define NODE_H
#include <string>

using std::string;

template <typename T>
struct Node {
    T value;
    Node* next;

    //конструкторы
    Node(T val, Node* following) : value(val), next(following) {}
    Node(T val) : value(val), next(nullptr) {}
    Node() : value(T()), next(nullptr){} //не уверен, но тут могут возникать ошибки, если нет конструктора по умолчанию для АТД
};

template struct Node<int>;
template struct Node<string>;

#endif //NODE_H
