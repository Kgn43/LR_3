#include "generalFuncs.h"

using std::runtime_error;

void callHelp(){ //я слишком поздно понял, что можно было написать батник))) ну, пусть будет так

    std::cout << std::endl << std::endl << "add --file FileName --query 'your query'" << std::endl << std::endl << std::endl << std::endl;

    std::cout << "Array syntax:" << std::endl;

    std::cout << "push:" << std::endl;
    std::cout << "\t\'Apush arrayName index value\'  - insert value by index" <<std::endl;
    std::cout << "\t\tOR" << std::endl;
    std::cout << "\t\'Apush arrayName value\'  - insert value at the end" << std::endl;

    std::cout << "delete:" << std::endl;
    std::cout << "\t\'Adel arrayName index\'  - delete value by index" <<std::endl;

    std::cout << "get:" << std::endl;
    std::cout << "\t\'AGet arrayName index\'  - get value from array by index" <<std::endl;
    std::cout << std::endl;


    std::cout << "Stack syntax:" << std::endl;

    std::cout << "push:" << std::endl;
    std::cout << "\t\'Spush stackName value\'  - insert value at the end" <<std::endl;

    std::cout << "pop:" << std::endl;
    std::cout << "\t\'Spop stackName\'  - delete last inserted value" <<std::endl;

    std::cout << "get:" << std::endl;
    std::cout << "\t\'SGet stackName\'  - get last inserted value" <<std::endl;
    std::cout << std::endl;


    std::cout << "List syntax:" << std::endl;

    std::cout << "push:" << std::endl;
    std::cout << "\t\'Lpush listName begin/end value\'  - insert value at the begin/end of list" << std::endl;

    std::cout << "del:" << std::endl;
    std::cout << "\t\'Ldel listName value/begin/end\'  - delete element from begin/end or delete by value" << std::endl;

    std::cout << "get:" << std::endl;
    std::cout << "\t\'LGet listName searchedValue\'  - determine if there is an element with this value in the list" << std::endl;
    std::cout << std::endl;


    std::cout << "Queue syntax:" << std::endl;

    std::cout << "push:" << std::endl;
    std::cout << "\t\'Qpush queueName value\'  - insert value at the end of queue" << std::endl;

    std::cout << "pop:" << std::endl;
    std::cout << "\t\'Qpop queueName\'  - delete element from begin of the queue" << std::endl;

    std::cout << "get:" << std::endl;
    std::cout << "\t\'QGet queueName\'  - get first inserted value" << std::endl;
    std::cout << std::endl;


    std::cout << "HashMap syntax:" << std::endl;

    std::cout << "insert:" << std::endl;
    std::cout << "\t\'Hinsert hashMapName key value\'  - insert value" << std::endl;

    std::cout << "del:" << std::endl;
    std::cout << "\t\'Hdel hashMapName key\'  - delete element from hashMap by key" << std::endl;

    std::cout << "get:" << std::endl;
    std::cout << "\t\'HGet hashMapName\'  - get one pair key-value" << std::endl;
    std::cout << std::endl;
    std::cout << "\t\tOR" << std::endl;
    std::cout << "\t\'push hashMapName key\'  - get one pair value by key" << std::endl;
    std::cout << std::endl;


    std::cout << "Set syntax:" << std::endl;

    std::cout << "add:" << std::endl;
    std::cout << "\t\'SETadd setName value\'  - insert value" << std::endl;

    std::cout << "del:" << std::endl;
    std::cout << "\t\'SETdel setName value\'  - delete element from hashMap by key" << std::endl;

    std::cout << "at:" << std::endl;
    std::cout << "\t\'SETat setName value\'  - check is this value in set" << std::endl;
    std::cout << std::endl;
}


bool isFileExist(const std::string& fileName){
    std::ifstream file(fileName);
    if(!file.is_open()) return false;
    file.close();
    return true;
}


std::string delFirstLetter(const std::string &input){
    std::string output;
    bool z = false;
    for(auto ch : input){
        if(!z){
            z = true;
        }
        else {
            output += ch;
        }
    }
    return output;
}


commands commandRequest(const std::string& input){
    if (input == "push") return commands::push;
    if (input == "pop") return commands::pop;
    if (input == "del") return commands::del;
    if (input == "Get") return commands::Get;
    if (input == "set") return commands::set;
    if (input == "insert") return commands::insert;
    if (input == "add") return commands::add;
    if (input == "at") return commands::at;
    throw runtime_error("This command isn't exist");
}


structures structRequest(const std::string& input){
    if (input[0] == 'S' && input[1] == 'E' && input[2] == 'T') return structures::SET;
    if (input[0] == 'A') return structures::ARRAY;
    if (input[0] == 'L') return structures::LIST;
    if (input[0] == 'Q') return structures::QUEUE;
    if (input[0] == 'S') return structures::STACK;
    if (input[0] == 'H') return structures::HASHMAP;
    throw runtime_error("This structure is not exist");
}


structures getType(const std::string& typeInFile){
    if (typeInFile == "#ARRAY") return structures::ARRAY;
    if (typeInFile == "#LIST") return structures::LIST;
    if (typeInFile == "#QUEUE") return structures::QUEUE;
    if (typeInFile == "#STACK") return structures::STACK;
    if (typeInFile == "#HASHMAP") return structures::HASHMAP;
    if (typeInFile == "#SET") return structures::SET;
    throw runtime_error("This structure isn't exist");
}


request getRequest(int argc, char *argv[] ){
    request output;
    for (int i = 0; i < argc; ++i){
        if (static_cast<std::string>(argv[i]) == "--help") {
            output.isCallHelp = true;
            return output;
        }
        if (static_cast<std::string>(argv[i]) == "--file") {
            //если после флага ничего нет || если после флага другой флаг
            if (i + 1 == argc || argv[i + 1][0] == '-') { //Если первое условие выполняется - второе не приведёт к ошибке т.к. не будет проверяться
                throw runtime_error(("Error: empty query.\n Specify what to execute"));
            }
            output.file = argv[i + 1];
            continue;
        }
        if (static_cast<std::string>(argv[i]) == "--query") {
            if (i + 1 == argc || argv[i + 1][0] == '-') { //если после флага ничего нет || если после флага другой флаг
                throw runtime_error(("Error: empty query.\n Specify what to execute"));
            }
            output.query = splitToArr(argv[i + 1]);
        }
    }
    return output;
}


bool isItNumber(const std::string& str) {
    for (auto ch : str) {
        if (!isdigit(ch)) return false;
    }
    return true;
}


void nameToFile(const std::string &name, std::fstream &out) {
    size_t nameLen = name.size();
    out.write(reinterpret_cast<char*>(&nameLen), sizeof(nameLen)); //write name size
    out.write(name.c_str(), name.size()); //write name
}


std::string getVarName(std::fstream &stream) {
    size_t varNameLen;
    stream.read(reinterpret_cast<char*>(&varNameLen), sizeof(varNameLen)); //get nameLen
    if (stream.eof()) throw runtime_error("data is broken");
    std::string varName(varNameLen, ' '); //set buffer size
    stream.read(varName.data(), varNameLen); //get var name
    return varName;
}