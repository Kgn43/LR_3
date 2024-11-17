#include "list_funcs.h"


void listPush(const request& request){
//структура команды: push имяСписка кудаЗаписать чтоЗаписать
    fstream file(request.file, ios::in);
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 4) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //имя списка
    string place = request.query[2]; // начало/конец
    if (place != "begin" && place != "end") throw runtime_error("Wrong insert place");
    string value = request.query[3]; //что записать
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.getVarInfo(variableLine);
        if (var.name == name && !varIsExist && var.type == "#LIST"){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            List<string> currVar = splitToList(var.data); //определяем реальную переменную этого Типа данных
            if (place == "begin"){
                currVar.headInsert(value); //закидываем то, что просят в начало
            }
            else {
                currVar.backInsert(value);
            }
            variableLine = var.type + ";" + var.name + ';' + unSplitList(currVar);//превращаем переменную в текст
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new list" << endl;
        List<string> newVar;//да, делаем это всегда.
        newVar.headInsert(value);
        variableLine = "#LIST;" + name + ';' + unSplitList(newVar);//превращаем переменную в текст
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


void listDel(const request& request){
//команда: pop имяСписка откуда/поКакомуЗначению
    fstream file(request.file, ios::in);
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1];
    string wh = request.query[2]; //what/where
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.getVarInfo(variableLine);
        if (var.name == name && !varIsExist && var.type == "#LIST"){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            List<string> currVar = splitToList(var.data); //определяем реальную переменную этого Типа данных
            if (wh == "begin") {
                currVar.delFirst();
            }
            else if (wh == "end"){
                currVar.delLast();
            }
            else {
                currVar.delByVal(wh);
            }
            variableLine =var.type + ";" + var.name + ';' + unSplitList(currVar);//превращаем переменную в текст
            if (currVar.first != nullptr){
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
        cout << "Tis list doesn't exist" << endl;
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


void listGet(const request& request){
//структура команды: get имяСписка искомоеЗначение
    fstream file(request.file, ios::in);
    if (request.query.size != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //в каком списке искать
    string value = request.query[2]; //что ищем
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.getVarInfo(variableLine);
        if (var.name == name && var.type == "#LIST"){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            List<string> currVar = splitToList(var.data); //определяем реальную переменную этого Типа данных
            if (currVar.find(value)){
                cout << "value " << value << " is in the list " << name << endl;
            }
            else {
                cout << "value " << value << " isn't in the list " << name << endl;
            }
            break;
        }
    }
    if (!varIsExist){
        cout << "This list isn't exist" << endl;
    }
}