#include "Stack.h"

template <typename T>
void Stack<T>::push(T val) {
    Node<T>* newElement = new Node{val, this->head};
    this->head = newElement;
    ++this->size;
}

template <typename T>
void Stack<T>::pop() {
    Node<T>* tmp = this->head;
    this->head = head->next;
    delete tmp;
    --this->size;
}

template <typename T>
T Stack<T>::getLast() {
    return this->head->value;
}

Stack<string> splitToStack(const string &input, char delimiter){
    string word;
    Stack<string> output;
    for (auto ch : input){
        if (ch == delimiter) {
            output.push(word);
            word = "";
        }
        else{
            word += ch;
        }
    }
    if (word != ""){
        output.push(word);
    }
    return output;
}

string unSplitStack(const Stack<string>& input, char delimiter){
    Node<string>* curr = input.head;
    string output;
    while (curr != nullptr){
        output = curr->value + delimiter + output;
        curr = curr->next;
    }
    return output;
}
