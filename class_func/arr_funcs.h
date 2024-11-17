#ifndef ARR_FUNCS_H
#define ARR_FUNCS_H

#include "../structures/arr.h"
#include "generalFuncs.h"

using std::ifstream, std::ios, std::cout, std::endl, std::fstream, std::runtime_error;

void arrPush(const request& request);
void arrDel(const request& request);
void arrGet(const request& request);

#endif //ARR_FUNCS_H
