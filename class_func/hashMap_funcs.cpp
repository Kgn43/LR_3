#include "hashMap_funcs.h"


hashMap getHashMap(fstream &stream) {
    size_t len;
    stream.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (stream.eof()) throw runtime_error("data is broken");
    hashMap outHashMaap;
    size_t keySize;
    size_t valueSize;
    for (int i = 0; i < len; ++i) {
        stream.read(reinterpret_cast<char*>(&keySize), sizeof(keySize));
        if (i != len - 1 && stream.eof()) throw runtime_error("data is broken");
        string key(keySize, ' '); //set buffer size
        stream.read(key.data(), keySize);
        stream.read(reinterpret_cast<char*>(&valueSize), sizeof(valueSize));
        if (i != len - 1 && stream.eof()) throw runtime_error("data is broken");
        string value(valueSize, ' '); //set buffer size
        stream.read(value.data(), valueSize);
        outHashMaap.insert(key, value);
    }
    return outHashMaap;
}


void hashMapToFile(const hashMap &hm, fstream &out) {
    auto size = hm.get_size();
    out.write(reinterpret_cast<char*>(&size), sizeof(size)); //write size of hm
    for (int i = 0; i < hm.get_bucketsCount(); ++i) {
        for (int j = 0; j < hm[i].size; ++j) {
            Pair dat = hm[i][j];
            size_t keySize = dat.key.size();
            out.write(reinterpret_cast<char*>(&keySize), sizeof(keySize)); //write one key len
            out.write(dat.key.c_str(), keySize); //write one key
            size_t valueSize = dat.value.size();
            out.write(reinterpret_cast<char*>(&valueSize), sizeof(valueSize)); //write one value len
            out.write(dat.value.c_str(), valueSize); //write one value
        }
    }
}


void hashSetInsert(const request& request){
//структура команды: insert имяТаблицы ключ значение
    fstream file(request.file, ios::in | ios::binary);
    fstream tmpFile("data/tmp.data", ios::out | ios::binary);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.get_size() != 4) throw runtime_error("Wrong command syntax");
    string name = request.query[1];
    string key = request.query[2]; //ключ
    string value = request.query[3]; //значение
    bool varIsExist = false;
    char ch;
    string varName;
    hashMap var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == '#') { //check hm flag
            varName = getVarName(file);
            var = getHashMap(file);
            if (varName == name && !varIsExist) { //right var is found
                varIsExist = true; //don't update duplicate
                var.insert(key, value);
            }
            tmpFile.put('#'); //put hm flag
            nameToFile(varName, tmpFile); //put hm name
            hashMapToFile(var, tmpFile); //put hm data
        }
        else {
            tmpFile.put(ch);
        }
    }
    if (!varIsExist){
        cout << "making new HashMap" << endl;
        hashMap newVar;
        newVar.insert(key, value);
        tmpFile.put('#'); //put hm flag
        nameToFile(name, tmpFile); //put hm name
        hashMapToFile(newVar, tmpFile); //put hm data
    }
    file.close();
    tmpFile.close();
    file.open(request.file, ios::out | ios::binary);
    tmpFile.open("data/tmp.data", ios::in | ios::binary);
    while (true){
        ch = tmpFile.get();
        if (tmpFile.eof()) break; //exit if file is fully read
        file << ch;
    }
    file.close();
    tmpFile.close();
}


void hashSetDel(const request& request){
    //команда: del имяТаблицы ключ
    fstream tmpFile("data/tmp.data", ios::out | ios::binary);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    fstream file(request.file, ios::in);
    if (request.query.get_size() != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //имя очереди
    string key = request.query[2];
    bool varIsExist = false;
    char ch;
    string varName;
    hashMap var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == '#') { //check hm flag
            varName = getVarName(file);
            var = getHashMap(file);
            if (varName == name && !varIsExist) { //right var is found
                varIsExist = true; //don't update duplicate
                var.del(key);
            }
            if (var.get_size() != 0) {
                tmpFile.put('#'); //put hm flag
                nameToFile(varName, tmpFile); //put hm name
                hashMapToFile(var, tmpFile); //put hm data
            }
        }
        else {
            tmpFile.put(ch);
        }
    }
    file.close();
    tmpFile.close();
    if (!varIsExist){
        cout << "This hashMap doesn't exist" << endl;
    } else {
        file.open(request.file, ios::out | ios::binary);
        tmpFile.open("data/tmp.data", ios::in | ios::binary);
        while (true){
            ch = tmpFile.get();
            if (tmpFile.eof()) break; //exit if file is fully read
            file << ch;
        }
        file.close();
        tmpFile.close();
    }
}


void hashSetGet(const request& request){
//структура команды: Get имяТаблицы ключ
    fstream file(request.file, ios::in | ios::binary);
    if (request.query.get_size() == 3){
        string name = request.query[1];
        string key = request.query[2];
        char ch;
        string varName;
        hashMap var;
        while (true){
            ch = file.get();
            if (file.eof()) break; //exit if file is fully read
            if (ch == '#') { //check hm flag
                varName = getVarName(file);
                var = getHashMap(file);
                if (varName == name) { //right var is found
                    if (var.Get(key).key.empty()){ //kringe
                        cout << "there is no value for this key" << endl;
                    }
                    else {
                        cout << var.Get(key) << endl;
                    }
                    return;
                }
            }
        }
        cout << "This hashMap isn't exist" << endl;
    }
    else throw runtime_error("Wrong command syntax");
}

