#include "stack_funcs.h"


Stack<string> getStack(fstream &stream) {
    size_t len;
    stream.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (stream.eof()) throw runtime_error("data is broken");
    Stack<string> outStack(len);
    size_t size;
    for (int i = 0; i < outStack.get_size(); ++i) {
        stream.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (i != outStack.get_size() - 1 && stream.eof()) throw runtime_error("data is broken");
        string sDat(size, ' '); //set buffer size
        stream.read(sDat.data(), size);
        outStack[i] = sDat;
    }
    return outStack;
}


void stackToFile(const Stack<string> &stack, fstream &out) {
    auto size = stack.get_size();
    out.write(reinterpret_cast<char*>(&size), sizeof(size)); //write size of stack
    for (int i = 0; i < stack.get_size(); ++i) {
        auto dataSize = stack[i].size(); //size of on element in stack
        out.write(reinterpret_cast<char*>(&dataSize), sizeof(size_t)); //write this size
        out.write(stack[i].c_str(), stack[i].size()); //write data
    }
}


void stackPush(const request& request){
//структура команды: push имяСтека чтоЗаписать
    fstream file(request.file, ios::in);
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.get_size() != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1];
    string value = request.query[2]; //что записать
    bool varIsExist = false;
    char ch;
    string varName;
    Stack<string> var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == ']') { //check stack flag
            varName = getVarName(file);
            var = getStack(file);
            if (varName == name && !varIsExist) { //right var is found
                varIsExist = true; //don't update duplicate
                var.push(value);
            }
            tmpFile.put(']'); //put stack flag
            nameToFile(varName, tmpFile); //put stack name
            stackToFile(var, tmpFile); //put stack data
        }
        else {
            tmpFile.put(ch);
        }
    }
    if (!varIsExist){
        cout << "making new Stack" << endl;
        Stack<string> newVar;
        newVar.push(value);
        tmpFile.put(']'); //put stack flag
        nameToFile(name, tmpFile); //put stack name
        stackToFile(newVar, tmpFile); //put stack data
    }
    file.close();
    tmpFile.close();
    file.open(request.file, ios::out);
    tmpFile.open("data/tmp.data", ios::in);
    while (true){
        ch = tmpFile.get();
        if (tmpFile.eof()) break; //exit if file is fully read
        file << ch;
    }
    file.close();
    tmpFile.close();
}


void stackPop(const request& request){
//команда: pop имяСтека
    fstream file(request.file, ios::in);
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.get_size() != 2) throw runtime_error("Wrong command syntax");
    string name = request.query[1];
    bool varIsExist = false;
    char ch;
    string varName;
    Stack<string> var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == ']') { //check stack flag
            varName = getVarName(file);
            var = getStack(file);
            if (varName == name && !varIsExist) { //right var is found
                varIsExist = true; //don't update duplicate
                var.pop();
            }
            if (var.get_size() != 0) {
                tmpFile.put(']'); //put stack flag
                nameToFile(varName, tmpFile); //put stack name
                stackToFile(var, tmpFile); //put stack data
            }
        }
        else {
            tmpFile.put(ch);
        }
    }
    file.close();
    tmpFile.close();
    if (!varIsExist){
        cout << "Tis stack doesn't exist" << endl;
    } else {
        file.open(request.file, ios::out);
        tmpFile.open("data/tmp.data", ios::in);
        while (true){
            ch = tmpFile.get();
            if (tmpFile.eof()) break; //exit if file is fully read
            file << ch;
        }
        file.close();
        tmpFile.close();
    }
}


void stackGet(const request& request){
//структура команды: get имяСтека
    fstream file(request.file, ios::in);
    if (request.query.get_size() != 2) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //из какого стека считать
    bool varIsExist = false;
    char ch;
    string varName;
    Stack<string> var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == ']') { //check stack flag
            varName = getVarName(file);
            var = getStack(file);
            if (varName == name && !varIsExist) { //right var is found
                varIsExist = true; //don't update duplicate
                cout << var.getLast() << endl;
                break;
            }
        }
    }
    if (!varIsExist){
        cout << "This stack isn't exist" << endl;
    }
}