#ifndef HASHMAP_FUNCS_H
#define HASHMAP_FUNCS_H

#include "../classes/hashMap.h"
#include "generalFuncs.h"

using std::ios, std::fstream, std::runtime_error;

hashMap getHashMap(fstream &stream);
void hashMapToFile(const hashMap &hm, fstream &out);
void hashSetInsert(const request& request);
void hashSetDel(const request& request);
void hashSetGet(const request& request);


#endif //HASHMAP_FUNCS_H
