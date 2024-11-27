#include "queue_funcs.h"


Queue<string> getQueue(fstream &stream) {
    size_t len;
    stream.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (stream.eof()) throw runtime_error("data is broken");
    Queue<string> outQueue(len);
    size_t size;
    for (int i = 0; i < outQueue.size; ++i) {
        stream.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (i != outQueue.size - 1 && stream.eof()) throw runtime_error("data is broken");
        string sDat(size, ' '); //set buffer size
        stream.read(sDat.data(), size);
        outQueue[i] = sDat;
    }
    return outQueue;
}


void queueToFile(Queue<string> &queue, fstream &out) {
    out.write(reinterpret_cast<char*>(&queue.size), sizeof(queue.size)); //write size of queue
    for (int i = 0; i < queue.size; ++i) {
        auto dataSize = queue[i].size(); //size of on element in queue
        out.write(reinterpret_cast<char*>(&dataSize), sizeof(size_t)); //write this size
        out.write(queue[i].c_str(), queue[i].size()); //write data
    }
}


void queuePush(const request& request){
//структура команды: push имяОчереди чтоЗаписать
    fstream file(request.file, ios::in);
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error( "Tmp file doesn't exist");
    if (request.query.size != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //имя очереди
    string value = request.query[2]; //что записать
    bool varIsExist = false;
    char ch;
    string varName;
    Queue<string> var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == '\\') { //check queue flag
            varName = getVarName(file);
            var = getQueue(file);
            if (varName == name && !varIsExist) { //right var is found
                varIsExist = true; //don't update duplicate
                var.push(value);
            }
            tmpFile.put('\\'); //put queue flag
            nameToFile(varName, tmpFile); //put queue name
            queueToFile(var, tmpFile); //put queue data
        }
        else {
            tmpFile.put(ch);
        }
    }
    if (!varIsExist){
        cout << "making new queue" << endl;
        Queue<string> newVar;
        newVar.push(value);
        tmpFile.put('\\'); //put queue flag
        nameToFile(name, tmpFile); //put queue name
        queueToFile(newVar, tmpFile); //put queue data
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


void queuePop(const request& request){
//команда: pop имяОчереди
    fstream file(request.file, ios::in);
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 2) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //имя очереди
    bool varIsExist = false;
    char ch;
    string varName;
    Queue<string> var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == '\\') { //check queue flag
            varName = getVarName(file);
            var = getQueue(file);
            if (varName == name && !varIsExist) { //right var is found
                varIsExist = true; //don't update duplicate
                var.pop();
            }
            if (var.size != 0) {
                tmpFile.put('\\'); //put queue flag
                nameToFile(varName, tmpFile); //put queue name
                queueToFile(var, tmpFile); //put queue data
            }
        }
        else {
            tmpFile.put(ch);
        }
    }
    file.close();
    tmpFile.close();
    if (!varIsExist){
        cout << "Tis queue doesn't exist" << endl;
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


void queueGet(const request& request){
//структура команды: get имяОчереди
    fstream file(request.file, ios::in);
    if (request.query.size != 2) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //в какой очереди искать
    char ch;
    string varName;
    Queue<string> var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == '\\') { //check queue flag
            varName = getVarName(file);
            var = getQueue(file);
            if (varName == name) { //right var is found
                cout << var.getFirst() << endl;
                return;
            }
        }
    }
    cout << "This queue isn't exist" << endl;
}