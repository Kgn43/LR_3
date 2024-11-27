#include "classesInterface.h"


int main(int argc, char *argv[]) {
    try {
        request request = getRequest(argc, argv);
        if (argc == 1){
            cout << "0 arguments were entered." << endl << "add --help for more information" << endl;
            return 1;
        }
        if (request.isCallHelp){
            callHelp();
            return 1;
        }
        if (request.query.size == 0){
            cout << "An empty query was given: add --help" << endl;
            return 1;
        }
        if (!isFileExist(request.file) || request.file.empty()){ //проверяем доступ указанного файла/указан ли файл
            throw runtime_error(("Error: wrong file name or file doesn't exist"));
        }
        if (request.query[0] == "print"){
            ultimatePrint(request);
        }
        else {
            structures strucType = structRequest(request.query[0]); //определяем по букве структуру
            request.query[0] = delFirstLetter(request.query[0]); //убираем букву для упрощения чтения команды
            switch (strucType) {
                case SET:
                    request.query[0] = delFirstLetter(request.query[0]); //-e
                    request.query[0] = delFirstLetter(request.query[0]); //-t
                    switch (commandRequest(request.query[0])) {
                        case add:
                            setAdd(request);
                        break;
                        case del:
                            setDel(request);
                        break;
                        case at:
                            setAt(request);
                        break;
                        default:
                            cout << "There is no such Set processing command" << endl;
                    }
                break;
                case ARRAY:
                    switch (commandRequest(request.query[0])) {
                        case push:
                            arrPush(request);
                            break;
                        case del:
                            arrDel(request);
                            break;
                        case Get:
                            arrGet(request);
                            break;
                        default:
                            cout << "There is no such Array processing command" << endl;
                    }
                    break;
                case STACK:
                    switch (commandRequest(request.query[0])) {
                        case push:
                            stackPush(request);
                            break;
                        case pop:
                            stackPop(request);
                            break;
                        case Get:
                            stackGet(request);
                            break;
                        default:
                            cout << "There is no such Stack processing command" << endl;
                    }
                    break;
                case LIST:
                    switch (commandRequest(request.query[0])) {
                        case push:
                            listPush(request);
                            break;
                        case del:
                            listDel(request);
                            break;
                        case Get:
                            listGet(request);
                            break;
                        default:
                            cout << "There is no such List processing command" << endl;
                    }
                    break;
                case QUEUE:
                    switch (commandRequest(request.query[0])) {
                        case push:
                            queuePush(request);
                            break;
                        case pop:
                            queuePop(request);
                            break;
                        case Get:
                            queueGet(request);
                            break;
                        default:
                            cout << "There is no such Queue processing command" << endl;
                    }
                    break;
                case HASHMAP:
                    switch (commandRequest(request.query[0])) {
                        case insert:
                            hashSetInsert(request);
                            break;
                        case del:
                            hashSetDel(request);
                            break;
                        case Get:
                            hashSetGet(request);
                            break;
                        default:
                            cout << "There is no such HashSet processing command" << endl;
                    }
                    break;
            }
        }
    }
    catch (exception &ex) {
        cout << ex.what() << endl;
        return -1;
    }
}


void ultimatePrint(const request& request) {
    fstream file(request.file, ios::in | ios::binary); //откуда читаем
    if (request.query.size == 1){ //вывести все переменные
        char ch;
        string varName;
        while (true){
            ch = file.get();
            if (file.eof()) break; //exit if file is fully read
            if (ch == '@') { //check array flag
                varName = getVarName(file);
                arr<string> var = getArr(file);
                cout << varName << ": " << var << '\n';
            }
            else if (ch == ']') { //check stack flag
                varName = getVarName(file);
                Stack<string> var = getStack(file);
                cout << varName << ": " << var << '\n';
            }
        }
    }
    else if (request.query.size == 2) { //вывести одну переменную
        string name = request.query[1]; //имя искомой переменной
        char ch;
        string varName;
        bool varIsExist = false;
        while (true){
            ch = file.get();
            if (file.eof()) break; //exit if file is fully read
            if (ch == '@') { //check array flag
                varName = getVarName(file);
                arr<string> var = getArr(file);
                if (varName == name) {
                    varIsExist = true;
                    cout << varName << ": " << var << '\n';
                }
            }
            else if (ch == ']') { //check stack flag
                varName = getVarName(file);
                Stack<string> var = getStack(file);
                if (varName == name) {
                    varIsExist = true;
                    cout << varName << ": " << var << '\n';
                }
            }
        }
        if (!varIsExist){
            cout << "Wrong variable name" << endl;
        }
    }
    else {
        cout << "Wrong syntax" << endl;
    }
    file.close();
}