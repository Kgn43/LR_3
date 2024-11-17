#ifndef LIST_FUNCS_H
#define LIST_FUNCS_H

#include "generalFuncs.h"
#include "../structures/list.h"

using std::cout, std::endl, std::ios, std::runtime_error, std::ifstream, std::fstream;

void listPush(const request& request);
void listDel(const request& request);
void listGet(const request& request);

#endif //LIST_FUNCS_H
