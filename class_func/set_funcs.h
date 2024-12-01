#ifndef SET_FUNCS_H
#define SET_FUNCS_H

#include "generalFuncs.h"
#include "../classes/Set.h"

using std::ios, std::ifstream, std::fstream, std::runtime_error;

Set getSet(fstream &stream);
void setToFile(const Set &set, fstream &out);
void setAdd(const request& request);
void setDel(const request& request);
void setAt(const request& request);

#endif //SET_FUNCS_H
