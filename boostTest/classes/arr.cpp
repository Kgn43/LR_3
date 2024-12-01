#include "arr.h"

template <typename T>
void arr<T>::realoc(){
    size_t newCapacity;
    if (capacity == 0){
        newCapacity = 1;
    }
    else {
        newCapacity = capacity * 2;
    }
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    if (data) {
        delete[] data;
    }
    data = newData;
    capacity = newCapacity;
}

template <typename T>
void arr<T>::push_back(const T& value) {
    if (size >= capacity) {
        realoc(); // Увеличиваем вместимость, если нужно
    }
    data[size++] = value; // Добавляем значение и увеличиваем размер
}

template <typename T>
size_t arr<T>::get_size() const  {
    return size;
}

template <typename T>
void arr<T>::erase() {
    if (size == 0) {
        throw std::out_of_range("Array is empty");
    }
    --size;
}

template <typename T>
void arr<T>::del(const size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1]; // Сдвигаем элементы влево
    }
    size--;
}


arr<string> splitToArr(const string &input, const char delimiter){
    string word;
    arr<string> output;
    for (auto ch : input){
        if (ch == delimiter) {
            output.push_back(word);
            word = "";
        }
        else{
            word += ch;
        }
    }
    if (word != ""){
        output.push_back(word);
    }
    return output;
}