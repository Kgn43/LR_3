#ifndef SET_H
#define SET_H

#include "list.h"
#include "arr.h"
#include <iostream>

#define BUCKETS 10

using std::cout, std::endl, std::ostream, std::to_string;


struct Set {
    arr<List<int>> buckets;
    size_t bucketCount;
    size_t pairCount;

    Set(): pairCount(0), bucketCount(BUCKETS), buckets(BUCKETS){} //создаёт BUCKETS бакет
    explicit Set(size_t num): pairCount(0), bucketCount(num), buckets(num){} //создаёт num бакетов

    void insert(const int& value);
    void del(const int& value);
    bool at(const int& value) const;

    friend ostream& operator<<(ostream& os, const Set& set) {
        os << "{";
        bool z = true;
        for (size_t i = 0; i < set.bucketCount; i++){
            if (set.buckets[i].first == nullptr) continue;
            auto node = set.buckets[i].first;
            if (z) {
                z = false;
            }
            else {
                os << ", ";
            }
            while (node != nullptr) {
                os << node->value;
                if (node->next != nullptr ) {
                    os << ", ";
                }
                node = node->next;
            }
        }
        os << "}" << endl;
        return os;
    }



    size_t hash(const int& value) const;
    void coliseum();
    int Get() const {
        for (size_t i = 0; i < this->buckets.size; ++i){
            if (this->buckets[i].first != nullptr) return this->buckets[i].first->value;
        }
        //error
        return 0;
    }
};

Set setFromStr(const string& line);
string strFromSet(Set input);



#endif //SET_H
