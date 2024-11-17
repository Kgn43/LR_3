#include "hashMap_funcs.h"


void hashSetInsert(const request& request){
//структура команды: insert имяТаблицы ключ значение
    fstream file(request.file, ios::in);
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 4) throw runtime_error("Wrong command syntax");
    string name = request.query[1];
    string key = request.query[2]; //ключ
    string value = request.query[3]; //значение
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.getVarInfo(variableLine);
        if (var.name == name && !varIsExist && var.type == "#HASHMAP"){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
            currVar.insert(key, value); //закидываем то, что просят
            variableLine = var.type + ";" + var.name + ';' + strFromHM(currVar);//превращаем переменную в текст
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new HashMap" << endl;
        hashMap newVar;//да, делаем это всегда.
        newVar.insert(key, value);
        variableLine = "#HASHMAP;" + name + ';' + strFromHM(newVar);//превращаем переменную в текст
        tmpFile << variableLine;
    }
    file.close();
    tmpFile.close();
    file.open(request.file, ios::out);
    tmpFile.open("data/tmp.data", ios::in);
    while (getline(tmpFile, variableLine)){
        file << variableLine << endl;
    }
    file.close();
    tmpFile.close();
}


void hashSetDel(const request& request){
    //команда: del имяТаблицы ключ
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    fstream file(request.file, ios::in);
    if (request.query.size != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //имя очереди
    string key = request.query[2];
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.getVarInfo(variableLine);
        if (var.name == name && var.type == "#HASHMAP"){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
            currVar.del(key);
            variableLine = var.type + ";" + var.name + ';' + strFromHM(currVar);//превращаем переменную в текст
            if (currVar.pairCount != 0){
                tmpFile << variableLine << endl;
            }
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    file.close();
    tmpFile.close();
    if (!varIsExist){
        cout << "Tis hashMap doesn't exist" << endl;
    } else {
        file.open(request.file, ios::out);
        tmpFile.open("data/tmp.data", ios::in);
        while (getline(tmpFile, variableLine)){
            file << variableLine << endl;
        }
        file.close();
        tmpFile.close();
    }
}


void hashSetGet(const request& request){
//структура команды: Get имяТаблицы [ключ]
    fstream file(request.file, ios::in);
    if (request.query.size == 2) {
        string name = request.query[1];
        string variableLine; //считываемая строка с файла
        fileData var;
        bool varIsExist = false;
        while (getline(file, variableLine)){ //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.getVarInfo(variableLine);
            if (var.name == name && var.type == "#HASHMAP") { //если такая переменная существует
                varIsExist = true; //закрываем защёлку
                hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
                cout << currVar.Get() << endl;
            }
        }
        if (!varIsExist){
            cout << "This hashMap isn't exist" << endl;
        }
    }
    else if (request.query.size == 3){
        string name = request.query[1];
        string key = request.query[2];
        string variableLine; //считываемая строка с файла
        fileData var;
        bool varIsExist = false;
        while (getline(file, variableLine)){ //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.getVarInfo(variableLine);
            if (var.name == name && var.type == "#HASHMAP"){ //если такая переменная существует
                varIsExist = true; //закрываем защёлку
                hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
                if (currVar.pairCount == 0) cout << "this HashMap is empty" << endl;
                else {
                    if (currVar.Get(key).key.empty()){
                        cout << "there is no value for this key" << endl;
                    }
                    else {
                        cout << currVar.Get(key) << endl;
                    }
                }
                break;
            }
        }
        if (!varIsExist){
            cout << "This hashMap isn't exist" << endl;
        }
    }
    else throw runtime_error("Wrong command syntax");

}

