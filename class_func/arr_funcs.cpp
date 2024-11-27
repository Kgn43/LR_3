#include "arr_funcs.h"


arr<string> getArr(fstream &stream) {
    size_t len;
    size_t cap;
    stream.read(reinterpret_cast<char*>(&cap), sizeof(cap));
    stream.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (stream.eof()) throw runtime_error("data is broken");
    arr<string> outArr(len);
    size_t size;
    for (int i = 0; i < outArr.size; ++i) {
        stream.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (i != outArr.size - 1 && stream.eof()) throw runtime_error("data is broken");
        string sDat(size, ' '); //set buffer size
        stream.read(sDat.data(), size);
        outArr.data[i] = sDat;
    }
    return outArr;
}


void arrToFile(arr<string> &array, fstream &out) {
    out.write(reinterpret_cast<char*>(&array.capacity), sizeof(array.capacity)); //write capacity
    out.write(reinterpret_cast<char*>(&array.size), sizeof(array.size)); //write size of array
    for (int i = 0; i < array.size; ++i) {
        auto dataSize = array[i].size(); //size of on element in arr
        out.write(reinterpret_cast<char*>(&dataSize), sizeof(size_t)); //write this size
        out.write(array[i].c_str(), array[i].size()); //write data
    }
}


void arrPush(const request& request){
//структура команды1 (по индексу): push имяМассива куда что
//структура команды2 (в конец): push имяМассива что
    fstream file(request.file, ios::in | ios::binary);
    fstream tmpFile("data/tmp.data", ios::out | ios::binary);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    string name; //куда записать
    string value; //что записать
    int index;
    if (request.query.size == 3) {
        name = request.query[1];
        index = -1;
        value = request.query[2];
    }
    else if (request.query.size == 4){
        name = request.query[1];
        index = stoi(request.query[2]);
        value = request.query[3];
    }
    else throw runtime_error("Wrong command syntax");
    bool varIsExist = false;
    char ch;
    string varName;
    arr<string> var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == '@') { //check array flag
            varName = getVarName(file);
            var = getArr(file);
            if (varName == name && !varIsExist) { //right var is found
                varIsExist = true; //don't update duplicate
                var.push_back(value);
                if (var.size - 1 != index && index != -1){ //move to right place if needed
                    string tmp;
                    for(size_t i = var.size - 1; i > index; --i){
                        tmp = var.data[i];
                        var.data[i] = var.data[i - 1];
                        var.data[i - 1] = tmp;
                    }
                }
            }
            tmpFile.put('@'); //put array flag
            nameToFile(varName, tmpFile); //put array name
            arrToFile(var, tmpFile); //put arr data
        }
        else {
            tmpFile.put(ch);
        }
    }
    if (!varIsExist){
        cout << "making new array" << endl;
        if (index != 0 && index != -1){//попытка вставить на какой-либо индекс кроме нуля в несуществующую переменную. рука-лицо.
            throw runtime_error("Wrong index");
        }
        arr<string> newVar;
        newVar.push_back(value);
        tmpFile.put('@'); //put array flag
        nameToFile(name, tmpFile); //put array name
        arrToFile(newVar, tmpFile); //put arr data
    }
    file.close();
    tmpFile.close();
    file.open(request.file, ios::out | ios::binary);
    tmpFile.open("data/tmp.data", ios::in  | ios::binary);
    while (true){
        ch = tmpFile.get();
        if (tmpFile.eof()) break; //exit if file is fully read
        file << ch;
    }
    file.close();
    tmpFile.close();
}


void arrDel(const request& request){
//структура команды: del имяМассива индекс
    fstream file(request.file, ios::in | ios::binary);
    fstream tmpFile("data/tmp.data", ios::out | ios::binary);
    if(!tmpFile.is_open()) throw runtime_error("tmp.data file doesn't exist");
    if (request.query.size != 3 || !isItNumber(request.query[2])) throw runtime_error("wrong command syntax");
    string name = request.query[1]; //из какого массива удалять
    size_t index = stoi(request.query[2]); //с какой позиции
    bool varIsExist = false;
    char ch;
    string varName;
    arr<string> var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == '@') { //check array flag
            varName = getVarName(file);
            var = getArr(file);
            if (varName == name && !varIsExist) { //right var is found
                varIsExist = true; //don't update duplicate
                var.del(index);
            }
            if (var.size != 0) {
                tmpFile.put('@'); //put array flag
                nameToFile(varName, tmpFile); //put array name
                arrToFile(var, tmpFile); //put arr data
            }
        }
        else {
            tmpFile.put(ch);
        }
    }
    file.close();
    tmpFile.close();
    if (!varIsExist){
        cout << "This array isn't exist" << endl;
    }
    else{
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


void arrGet(const request& request){
//структура команды: get имяМассива индекс
    fstream file(request.file, ios::in | ios::binary);
    if (request.query.size != 3 || !isItNumber(request.query[2])) throw runtime_error("wrong command syntax");
    string name = request.query[1]; //из какого массива считать
    size_t index = stoi(request.query[2]); //с какой позиции
    bool varIsExist = false;
    char ch;
    string varName;
    arr<string> var;
    while (true){
        ch = file.get();
        if (file.eof()) break; //exit if file is fully read
        if (ch == '@') { //check array flag
            varName = getVarName(file);
            var = getArr(file);
            if (varName == name && !varIsExist) { //right var is found
                varIsExist = true; //don't update duplicate
                if (index < var.size) cout << var[index] << endl;
                else cout << "Index out of range" << endl;
                break;
            }
        }
    }
    if (!varIsExist){
        cout << "This array isn't exist" << endl;
    }
}