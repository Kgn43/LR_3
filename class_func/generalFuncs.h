#ifndef GENERAL_FUNCS_H
#define GENERAL_FUNCS_H


#include <iostream>
#include <fstream>
#include <utility>
#include "../classes/arr.h"



enum commands{
    Get,
    push,
    pop,
    del,
    insert,
    set,
    add,
    at
};


enum structures{
    ARRAY,
    LIST,
    QUEUE,
    STACK,
    HASHMAP,
    SET
};


struct request{
    arr<string> query;
    string file;
    bool isCallHelp = false; //проиграли бит, но выиграли больше на обработке запроса
};


struct fileData{
    string type;
    string name;
    string data;

    fileData () = default;
    fileData (string t, string n, string d) : type(t), name(n), data(d) {};

    void getVarInfo(const string &input) {
        arr<string> split;
        split = splitToArr(input, ';');
        if(split.size != 3 || split[0][0] != '#') {
            throw std::runtime_error("Error in fileData: data is broken");
        }
        this->type = split[0];
        this->name = split[1];
        this->data = split[2];
    }
};


void callHelp();
bool isFileExist(const std::string& fileName);
bool isItNumber(const std::string& str);

#endif //GENERAL_FUNCS_H
