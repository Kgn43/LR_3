#include "set_funcs.h"


void setAdd(const request& request) {
    //структура команды: insert setName value
    fstream file(request.file, ios::in);
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1];
    string value = request.query[2]; //значение
    if (!isItNumber(value)) {
        throw runtime_error("Wrong inserted value");
    }
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.getVarInfo(variableLine);
        if (var.name == name && !varIsExist && var.type == "#SET"){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            Set currVar = setFromStr(var.data); //определяем реальную переменную этого Типа данных
            currVar.insert(stoi(value)); //закидываем то, что просят
            variableLine = var.type + ';' + var.name + ';' + strFromSet(currVar);//превращаем переменную в текст
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new set" << endl;
        Set newVar;//да, делаем это всегда.
        newVar.insert(stoi(value));
        variableLine = "#SET;" + name + ';' + strFromSet(newVar);//превращаем переменную в текст
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

void setDel(const request& request) {
    //команда: del SetName value
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    fstream file(request.file, ios::in);
    if (request.query.size != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //имя очереди
    if (!isItNumber(request.query[2])) {
        throw runtime_error("Wrong inserted value");
    }
    int value = stoi(request.query[2]);
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.getVarInfo(variableLine);
        if (var.name == name && !varIsExist && var.type == "#SET"){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            Set currVar = setFromStr(var.data); //определяем реальную переменную этого Типа данных
            currVar.del(value);
            variableLine = var.type + ';' + var.name + ';' + strFromSet(currVar);//превращаем переменную в текст
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
        cout << "Tis set doesn't exist" << endl;
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
void setAt(const request& request) {
    //структура команды: at setName value
    fstream file(request.file, ios::in);
    if (request.query.size != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1];
    if (!isItNumber(request.query[2])) {
        throw runtime_error("Wrong inserted value");
    }
    int value = stoi(request.query[2]);
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.getVarInfo(variableLine);
        if (var.name == name && var.type == "#SET"){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            Set currVar = setFromStr(var.data); //определяем реальную переменную этого Типа данных
            if (currVar.at(value)){
                cout << "value " << value << " is in the set " << name << endl;
            }
            else {
                cout << "value " << value << " isn't in the set " << name << endl;
            }
            break;
        }
    }
    if (!varIsExist){
        cout << "This set isn't exist" << endl;
    }
}