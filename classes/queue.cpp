#include "queue.h"

template<typename T>
void Queue<T>::push(T val) {// вставляем в хвост
    Node<T>* newElement = new Node{val};
    if (this->head == nullptr) {
        this->head = newElement;
        this->tail = newElement;
        ++this->size;
    }
    else {
        this->tail->next = newElement;
        this->tail = newElement;
        ++this->size;
    }
}

template<typename T>
void Queue<T>::pop() { //удаляем с головы
    if (this->head == nullptr) return;
    auto tmpHead = this->head;
    this->head = this->head->next;
    delete tmpHead;
    --this->size;
}

template<typename T>
T Queue<T>::getFirst() {
    return this->head->value;
}

Queue<string> splitToQueue(const string &input, char delimiter){
    string word;
    Queue<string> output;
    for (auto ch : input){
        if (ch == delimiter) {
            output.push(word);
            word = "";
        }
        else{
            word += ch;
        }
    }
    if (!word.empty()){
        output.push(word);
    }
    return output;
}

string unSplitQueue(const Queue<string>& input, const char delimiter){
    Node<string>* curr = input.head;
    string output;
    while (curr != nullptr){
        output += curr->value + delimiter;
        curr = curr->next;
    }
    return output;
}