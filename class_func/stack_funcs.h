#ifndef STACK_FUNCS_H
#define STACK_FUNCS_H

#include "generalFuncs.h"
#include "../classes/Stack.h"

using std::ifstream, std::ios, std::fstream, std::runtime_error;

void stackPush(const request& request);
void stackPop(const request& request);
void stackGet(const request& request);

#endif //STACK_FUNCS_H
