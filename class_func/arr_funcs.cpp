#include "arr_funcs.h"


void arrPush(const request& request){
//структура команды1 (по индексу): push имяМассива куда что
//структура команды2 (в конец): push имяМассива что
    fstream file(request.file, ios::in);
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()){
        throw runtime_error("Tmp file doesn't exist");
    }
    string name; //куда записать
    string value; //что записать
    int index;
    string variableLine; //считываемая строка с файла
    fileData var;
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
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.getVarInfo(variableLine);
        if (var.name == name && !varIsExist && var.type == "#ARRAY"){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            arr<string> currVar = splitToArr(var.data); //определяем реальную переменную этого Типа данных
            currVar.push_back(value); //закидываем то, что просят в конец
            if (currVar.size - 1 != index && index != -1){
                string tmp;//третий стакан
                for(size_t i = currVar.size - 1; i > index; --i){ //и меняем местами до нужного индекса
                    tmp = currVar.data[i];
                    currVar.data[i] = currVar.data[i - 1];
                    currVar.data[i - 1] = tmp;
                }
            }
            variableLine = var.type + ";" + var.name + ';' + unsplit(currVar);//превращаем переменную в текст
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new array" << endl;
        if (index != 0 && index != -1){//попытка вставить на какой-либо индекс кроме нуля в несуществующую переменную. рука-лицо.
            throw runtime_error("Wrong index");
        }
        arr<string> newVar;//да, можно и не делать этого. но мы сделаем. потому, что можем.
        newVar.push_back(value);
        variableLine = "#ARRAY;" + name + ';' + unsplit(newVar);//превращаем переменную в текст
        tmpFile << variableLine;
        //newVar.clear();
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


void arrDel(const request& request){
//структура команды: del имяМассива индекс
    fstream file(request.file, ios::in);
    fstream tmpFile("data/tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("tmp.data file doesn't exist");
    if (request.query.size != 3 || !isItNumber(request.query[2])) throw runtime_error("wrong command syntax");
    string name = request.query[1]; //из какого массива удалять
    size_t index = stoi(request.query[2]); //с какой позиции
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.getVarInfo(variableLine);
        if (var.name == name && !varIsExist && var.type == "#ARRAY"){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            arr<string> currVar = splitToArr(var.data); //определяем реальную переменную этого Типа данных
            currVar.del(index);//удаление
            variableLine = var.type + ";" + var.name + ';' + unsplit(currVar);//превращаем переменную в текст
            if (currVar.size == 0) variableLine = "";
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    file.close();
    tmpFile.close();
    if (!varIsExist){
        cout << "This array isn't exist" << endl;
    }
    else{
        file.open(request.file, ios::out);
        tmpFile.open("data/tmp.data", ios::in);
        while (getline(tmpFile, variableLine)){
            file << variableLine << endl;
        }
        file.close();
        tmpFile.close();
    }
}


void arrGet(const request& request){
//структура команды: get имяМассива индекс
    fstream file(request.file, ios::in);
    if (request.query.size != 3 || !isItNumber(request.query[2])) throw runtime_error("wrong command syntax");
    string name = request.query[1]; //из какого массива считать
    size_t index = stoi(request.query[2]); //с какой позиции
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.getVarInfo(variableLine);
        if (var.name == name && var.type == "#ARRAY"){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            arr<string> currVar = splitToArr(var.data); //определяем реальную переменную этого Типа данных
            if (index < currVar.size) cout << currVar[index] << endl;
            else cout << "Index out of range" << endl;
            break;
        }
    }
    if (!varIsExist){
        cout << "This array isn't exist" << endl;
    }
}