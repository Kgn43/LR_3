#include "list_funcs.h"


List<string> getList(fstream &stream) {
    size_t len;
    stream.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (stream.eof()) throw runtime_error("data is broken");
    List<string> outList(len);
    size_t size;
    for (int i = 0; i < outList.size; ++i) {
        stream.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (i != outList.size - 1 && stream.eof()) throw runtime_error("data is broken");
        string sDat(size, ' '); //set buffer size
        stream.read(sDat.data(), size);
        outList[i] = sDat;
    }
    return outList;
}


void listToFile(List<string> &list, fstream &out) {
    out.write(reinterpret_cast<char*>(&list.size), sizeof(list.size)); //write size of queue
    for (int i = 0; i < list.size; ++i) {
        auto dataSize = list[i].size(); //size of on element in queue
        out.write(reinterpret_cast<char*>(&dataSize), sizeof(size_t)); //write this size
        out.write(list[i].c_str(), list[i].size()); //write data
    }
}


void listPush(const request& request){
//структура команды: push имяСписка кудаЗаписать чтоЗаписать
    fstream file(request.file, ios::in);
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.get_size() != 4) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //имя списка
    string place = request.query[2]; // начало/конец
    if (place != "begin" && place != "end") throw runtime_error("Wrong insert place");
    string value = request.query[3]; //что записать
    bool varIsExist = false;
    char ch;
    string varName;
    List<string> var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == '/') { //check list flag
            varName = getVarName(file);
            var = getList(file);
            if (varName == name && !varIsExist) { //right var is found
                varIsExist = true; //don't update duplicate
                if (place == "begin"){
                    var.headInsert(value); //закидываем то, что просят в начало
                }
                else {
                    var.backInsert(value);
                }
            }
            tmpFile.put('/'); //put list flag
            nameToFile(varName, tmpFile); //put list name
            listToFile(var, tmpFile); //put list data
        }
        else {
            tmpFile.put(ch);
        }
    }
    if (!varIsExist){
        cout << "making new list" << endl;
        List<string> newVar;
        newVar.headInsert(value);
        tmpFile.put('/'); //put list flag
        nameToFile(name, tmpFile); //put list name
        listToFile(newVar, tmpFile); //put list data
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


void listDel(const request& request){
//команда: pop имяСписка откуда/поКакомуЗначению
    fstream file(request.file, ios::in);
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.get_size() != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1];
    string wh = request.query[2]; //what/where
    bool varIsExist = false;
    char ch;
    string varName;
    List<string> var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == '/') { //check list flag
            varName = getVarName(file);
            var = getList(file);
            if (varName == name && !varIsExist) { //right var is found
                varIsExist = true; //don't update duplicate
                if (wh == "begin") {
                    var.delFirst();
                }
                else if (wh == "end"){
                    var.delLast();
                }
                else {
                    var.delByVal(wh);
                }
            }
            if (var.size != 0) {
                tmpFile.put('/'); //put list flag
                nameToFile(varName, tmpFile); //put list name
                listToFile(var, tmpFile); //put list data
            }
        }
        else {
            tmpFile.put(ch);
        }
    }
    file.close();
    tmpFile.close();
    if (!varIsExist){
        cout << "Tis list doesn't exist" << endl;
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


void listGet(const request& request){
//структура команды: get имяСписка index
    fstream file(request.file, ios::in);
    if (request.query.get_size() != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //в каком списке искать
    auto index = stoi(request.query[2]); //index
    char ch;
    string varName;
    List<string> var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == '/') { //check list flag
            varName = getVarName(file);
            var = getList(file);
            if (varName == name) { //right var is found
                cout << var[index] << endl;
                return;
            }
        }
    }
    cout << "This list isn't exist" << endl;
}
