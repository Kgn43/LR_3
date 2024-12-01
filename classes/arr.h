#ifndef ARR_H
#define ARR_H

#include <string>
#include <sstream>
using std::ostream, std::string, std::out_of_range;

template <typename T>
class arr {
protected:
    T* data;
    size_t size;
    size_t capacity;

    void realoc();
public:
    friend class Set;
    friend class hashMap;
    arr() : data(nullptr), size(0), capacity(0) {}

    arr(size_t length) : size(length), capacity(length) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = T();
        }
    }

    void push_back(const T& value);
    size_t get_size() const;
    void erase();
    void del(size_t index);
    void clear();

    friend ostream& operator<<(ostream& os, const arr& arr) {
        os << "[";
        for (size_t i = 0; i < arr.size; ++i) {
            os << arr.data[i];
            if (i < arr.size - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

};

template struct arr<int>;
template struct arr<string>;

arr<string> splitToArr(const string &input, char delimiter = ' ');

#endif // ARR_H
