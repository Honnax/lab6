#include "parser.h"
#include <stack>
#include <fstream>

omfl::__NameMe_ parse(std::string str){
    omfl::__NameMe_ done_parse;
    done_parse.parse(str);
    return done_parse;
}
bool check_correct_brackets_sequence (const std::string& get) {//правильное колво скобок(и все)
    std::string command = "";
    std::stack <char> top;
    bool into_string = false;
    bool error = false;
    for (int i = 0; i < get.length(); i++) {
        if (!into_string and get[i] == '"') {
            into_string = true;
        }
        if (into_string and get[i] == '"') {
            into_string = false;
        }

        if (error) break;
        if (!into_string and get[i] != '"') {
            if (get[i] == '[' or get[i] == ']') {
                char add;
                for (long y = 0; y < command.length(); y++) {
                    add = command[y];
                    if (add != '[' and add != ']') {
                        error = true;
                        break;
                    }
                    if (command[y] == '[')  {
                        top.push('[');
                    } else {
                        if (top.empty()) {
                            error = true;
                            break;
                        } else {
                            if (top.top() == '[' and add == ']') {
                                top.pop();
                            } else {
                                error = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    if (!top.empty()) {
        error = true;
    }
    if (error) {
        return false;
    }
    return true;
}


bool bool_values_check (std::string arg) {
    int runner = arg.size()-1;
    for (runner; runner > -1; --runner) {
        if (arg[runner] != ' '){
            arg = arg.substr(0, runner + 1);
            break;
        }
    }//  конец справа
    if (arg == "true" or arg == "false") { //ответ
        return true;
    }
    return false;
}

bool integer_values_check (std::string arg) {
    int runner = arg.size()-1;
    for (runner; runner > -1; --runner) {
        if (arg[runner] != ' '){
            arg = arg.substr(0, runner + 1);
            break;
        }
    }//  конец справа
    char value[arg.length()];//массив чаров по размеру строчки
    for (int i = 0; i < arg.length(); i++) {
        value[i] = arg[i];
    }//заполнение
    int try_to_make_integer = atoi(value); //даст инт который сможет
    std::string try_to_make_string_back;
    try_to_make_string_back = std::to_string(try_to_make_integer);//нэйминг
    if (arg[0] == '-' or arg[0] == '+') {
        try_to_make_string_back = arg[0] + try_to_make_integer;
    }

    if (try_to_make_string_back == arg) {
        return true;
    }
    return false;
}
bool float_values_check (std::string arg) {
    int runner = arg.size() - 1;
    for (runner; runner > -1; --runner) {
        if (arg[runner] != ' '){
            arg = arg.substr(0, runner + 1);
            break;
        }
    }//  конец справа

    std::string value = arg;
    float try_to_make_float = std::atof(value.c_str());
    std::string try_to_make_string_back;

    try_to_make_string_back = std::to_string(try_to_make_float);

    if (arg[0] == '-' or arg[0] == '+') {
        try_to_make_string_back = arg[0] + try_to_make_string_back;
    }
    if (try_to_make_string_back == value) {
        return true;
    }
    return false;
}
bool string_valuescheck (std::string arg) {
    if (std::count(arg.begin(), arg.end(), '"') != 2) {
        return false;
    }
    for (int i = arg.size()-1; i > -1; --i) {
        if (arg[i] != ' '){
            if (arg[0] != '"' or arg[i] != '"') {//последний символ всегда "
                return false;
            }
        }
    }
    return true;
}
bool mass_values_check (std::string arg) {
    std::vector<std::string> for_check;
    std::string to_add;
    for (int i = 1; i < arg.length()-1; i++) {
        if (arg[i] != ',') {
            to_add += arg[i];
        } else {
            for_check.emplace_back(to_add);
            to_add = "";
        }
    }
    for (int i = 0; i < for_check.size(); i++) {
        bool some_correct = false;
        if (bool_values_check(for_check[i])) {
            some_correct = true;
        }
        if (float_values_check(for_check[i])) {
            some_correct = true;
        }
        if (string_valuescheck(for_check[i])) {
            some_correct = true;
        }
        if (mass_values_check(for_check[i])) {
            some_correct = true;
        }
        if (integer_values_check(for_check[i])) {
            some_correct = true;
        }
        if (!some_correct) {
            return false;
        }
    }
    return true;
}
bool key_and_section_check (std::string arg, bool is_section) { //ключ "asd     "= asd

    if (is_section){
        for (int i = arg.size()-1; i > -1; --i) {
            if (arg[i] != ' '){
                if (arg[i] != ']' or arg[0] != '['){//если последний символ не ] - невалид
                    return false;
                }
                arg = arg.substr(1, i-1);
                break;
            }
        } //теперь здесь толко секция
        if (arg.size() == 0) return false;//пустая секцмя
        for (int i = 0; i < arg.size(); i++) {// валидность и ключа и секции
            if (!((arg[i] >= 48 and arg[i] <= 57) or (arg[i] >= 65 and arg[i] <= 91) or
                  (arg[i] >= 97 and arg[i] <= 122) or arg[i] == '_' or arg[i] == '.' or arg[i] == '-')) {
                return false;
            }
        }//корректные символы
        if (arg[0] == '.' or arg[arg.size()-1] == '.') return false; //точка в начале или в конце
        for (int i = 0; i < arg.size()-1; i++) {//две точки подряд
            if ((arg[i] == arg[i+1]) and arg[i] == '.') {
                return false;
            }
        }
        return true;

    } else {
        for (int i = arg.size()-1; i > -1; --i) {
            if (arg[i] != ' '){
                arg = arg.substr(0, i+1);
                break;
            }
        } //теперь здесь толко ключ
        if (arg.size() == 0){
            return false;
        }
        for (int i = 0; i < arg.size(); ++i) {
            if (!((arg[i] >= 48 and arg[i] <= 57) or (arg[i] >= 65 and arg[i] <= 91) or
                 (arg[i] >= 97 and arg[i] <= 122) or arg[i] == '_' or arg[i] == '-')) {
                return false;
            }
        }
        return true;
    }
}

bool omfl::__NameMe_::valid_string (std::string get) {
    int comment_index = get.size();
    for (int i = 0; i < get.size(); ++i) {
        if (get[i] == '#') {
            comment_index = i;
            break;
        }
    }
    int index_first_not_space = 0;
    for (int i = 0; i < get.size(); ++i) {
        if (get[i] != ' '){
            index_first_not_space = i;
            break;
        }
    }
    std::string get_without_comment = get.substr(index_first_not_space, comment_index - index_first_not_space + 1); // вид    "asd     =   asd "#asdadsd
        if (get_without_comment.size() != 0) {
            if (!check_correct_brackets_sequence(get)) {
                return false;
            }
            if (get_without_comment[0] == '[') {//секция
                if (!key_and_section_check(get, true)) {
                    return false;
                }
            } else {
                int runner = 0;
                std::string one_arg;
                while (runner < get_without_comment.length() and get_without_comment[runner] != '=') { //вытаскиваем ключ(не секцию)
                    one_arg += get[runner];
                    runner++;
                }
                if (one_arg.size() == 0) {//значит ключа нет
                    return false;
                }
                if (!key_and_section_check(one_arg, false)) { //проверяем ключ на валидность
                    return false;
                }
                if (runner+1 < get_without_comment.length()) { //обрезаем значение
                    ++runner;
                    while(runner < get_without_comment.length() and get_without_comment[runner] != ' '){
                        ++runner;
                    }
                    get_without_comment = get_without_comment.substr(runner+1);//убрали пробелы в начале
                } else {
                    return false;
                }
                if (bool_values_check(get_without_comment)) { return true;
                } else if (float_values_check(get_without_comment)) { return true;
                } else if (string_valuescheck(get_without_comment)) { return true;
                } else if (mass_values_check(get_without_comment)) { return true;
                } else if (integer_values_check(get_without_comment)) { return true;
                } else return false;
            }
        } return true;
    }
bool omfl::__NameMe_::valid() const{
    return valid_parse;
};
std::vector<std::string> omfl::__NameMe_::makeSectionNameVector(const std::string& sectionName){// получили название без скобок
    std::vector<std::string> theVector;
    std::string pod_section_Name;
    int sectionNameIndexStart = 0;
    for (int i = 1; i < sectionName.size(); ++i) { // проходим по всему длинному названию
        if (sectionName[i] != '.'){// наращиваем имя
            pod_section_Name += sectionName[i];
        } else { //попали на точку
            theVector.push_back(sectionName.substr(sectionNameIndexStart, i - sectionNameIndexStart)); //добавили название подсекции
            sectionNameIndexStart = i + 1; // меняем место старта нового имени (начинается после точки)
        }
        if (i == sectionName.size() - 1 ){ //прочекали в конце
            theVector.push_back(sectionName.substr(sectionNameIndexStart, i + 1 - sectionNameIndexStart));
        }
    }
    return theVector;
}

bool omfl::__NameMe_::isSectionExist(const std::string& sectionName){//получили название без скобок
    std::vector<std::string> sectionNameVector = makeSectionNameVector(sectionName);
    bool isExist = true;
    bool stepDeeperWasMade;
    for (int i = 0; i < sectionNameVector.size(); ++i) {
        stepDeeperWasMade = false;//проверяем шагнули ли глубже
        for (int j = 0; j < head_section->current_section->pod_section_.size(); ++j) {
            if (sectionNameVector[i] == head_section->current_section->pod_section_[j].first){
                stepDeeperWasMade = true;
                head_section->current_section = head_section->current_section->pod_section_[j].second; // спустились ниже
                break;
            }
        }
        if (!stepDeeperWasMade){ // шаг глубже не был сделвн - значит не существует
            isExist = false;
            break;
        }
    }
    return isExist;//возвращаем либо существование(и мы в нем находимся), либо несуществование и current опущенный до этапа несуществования
}
omfl::__NameMe_::massiveStruct omfl::__NameMe_::makeItMassiveStruct(const std::string& oneLine, int& index){//в индексе находиться символ'['
    massiveStruct toAdd;
    ++index;//переходим внутрь массива
    for (index; index < oneLine.size(); ++index) {// key4 = [[1,2],[2,["3",4,5]]]
        if (oneLine[index] == '['){//если начался другой массив
            massiveStruct podMassive;
            podMassive = makeItMassiveStruct(oneLine, index);
            std::pair<char, int> massKey;
            massKey.first = 'm';
            massKey.second = toAdd.massives.size();//получаем нужный индекс
            toAdd.massKeys.push_back(massKey);
            toAdd.massives.push_back(podMassive);
        } else if(oneLine[index] == ']'){//структура закончилась
            ++index;//чтобы не закрыть все массивы сразу
            return toAdd;
        } else if(oneLine[index] == '\"'){//строчка
            std::pair<char, int> massKey;
            massKey.first = 's';
            massKey.second = toAdd.stringMassValues.size();
            toAdd.massKeys.push_back(massKey);
            std::string stringValue;
            while(oneLine[index] != '\"'){
                stringValue += oneLine[index];
            }
            toAdd.stringMassValues.push_back(stringValue);
        } else if (oneLine.substr(index,4) == "true" or oneLine.substr(index,5) == "false"){// bool
            std::pair<char, int> massKey;
            massKey.first = 'b';
            massKey.second = toAdd.boolMassValues.size();
            toAdd.massKeys.push_back(massKey);
            if (oneLine.substr(index,4) == "true"){
                toAdd.boolMassValues.push_back(true);
            } else toAdd.boolMassValues.push_back(false);
        } else if (oneLine[index] == ','){
            ++index;
        } else { // числа
            std::pair<char,int>massKey;
            std::string intOrFloat;
            while(oneLine[index] != ',' or oneLine[index] != ']'){
                intOrFloat += oneLine[index];
            }
            bool isFloat = false;
            for (int i = 0; i < intOrFloat.size(); ++i) {
                if (intOrFloat[i] == '.'){
                    isFloat = true;
                }
            }
            if (isFloat){
                massKey.first = 'f';
                massKey.second = toAdd.floatMassValues.size();
                toAdd.floatMassValues.push_back(std::stof(intOrFloat));
                toAdd.massKeys.push_back(massKey);
            } else {
                massKey.first = 'i';
                massKey.second = toAdd.intMassValues.size();
                toAdd.intMassValues.push_back(std::stoi(intOrFloat));
                toAdd.massKeys.push_back(massKey);
            }

        }
    } return toAdd;
}
std::string makeItOneLine(const std::string& str){
    std::string oneLine;
    bool ifInString = false;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '#') break;
        if (str[i] == '\"' and ifInString){//значит строка закончилась
            ifInString = false;
        } else if(str[i] == '\"' and !ifInString){
            ifInString = true; // строка началась
        }


        if (ifInString){//если строка то добавляем все значения
            oneLine += str[i];
        } else if (str[i] != ' ') {//иначе пропускаем пробелы
            oneLine += str[i];
        }
    }
    return oneLine;
}
omfl::__NameMe_ omfl::__NameMe_::parse_this_string(const std::string &str){
    std::string oneLine = makeItOneLine(str);
    if(oneLine.size() == 0){
        return *head_section;
    } else if (str[0] == '['){//значит это секция
        //теперь либо найдем существующую секцию, либо создадим новую
        std::string sectionName = oneLine.substr(1, str.size()-2);//обрезанный вариант, без скобок
        if(isSectionExist(sectionName)){// существует
            // значит существует и current находиться в ней -> все готово для добавления
        } else { // несуществует - создаем
            std::vector<std::string> sectionsNameVector = makeSectionNameVector(sectionName);
            head_section->current_section = head_section;// приводим в дефолт
            int whereSectionNameVectorEnded = -1;
            for (int i = 0; i < sectionsNameVector.size(); ++i) {
                bool stepDeeperWasMade = false;
                for (int j = 0; j < head_section->current_section->pod_section_.size(); ++j) {
                    if (head_section->current_section->pod_section_[j].first == sectionsNameVector[i]){
                        head_section->current_section = head_section->current_section->pod_section_[j].second;
                        whereSectionNameVectorEnded = i;//теперь мы знаем на какой секции мы остановились
                        stepDeeperWasMade = true;
                        break;
                    }
                }
                if (!stepDeeperWasMade){
                    break;
                }
            }
            for (int i = whereSectionNameVectorEnded + 1; i < sectionsNameVector.size(); ++i) {
                std::pair<std::string, __NameMe_*> toAdd;
                __NameMe_ newpod_section_;
                newpod_section_.head_section = head_section;
                toAdd.first = sectionsNameVector[i];
                toAdd.second = &newpod_section_;
                head_section->current_section->pod_section_.push_back(toAdd);// добавили
                head_section->current_section = head_section->current_section->pod_section_[head_section->current_section->pod_section_.size()-1].second;// спустились в последний добавленныый
            }//так мы должны добавить все подсекции и спуститься в нижнюю
        }
        return *head_section;
    } else { //ключ и значение
        int i = 0;
        std::string keyName;
        while(oneLine[i] != '='){ // собираем ключ
            keyName += oneLine[i];
            ++i;
        }
        i += 1; //уходим за "="
        for (i; i < oneLine.size(); ++i) {// собираем значение
            if (oneLine[i] == '\"'){ // если строчка
                std::pair<std::string, std::string> toAdd;
                toAdd.first = keyName;
                std::string stringValue;
                for (int j = i+1; j < oneLine.size()-1; ++j) {
                    stringValue += oneLine[j];
                }
                toAdd.second = stringValue;
                head_section->current_section->string_values.push_back(toAdd);
            } else if (oneLine.substr(i, 4) == "true" or oneLine.substr(i, 5) == "false"){ // если bool
                std::pair<std::string, bool> toAdd;
                toAdd.first = keyName;
                if (oneLine.substr(i, 4) == "true"){
                    toAdd.second = true;
                } else toAdd.second = false;
                head_section->current_section->bool_values.push_back(toAdd);
            } else if (oneLine[i] == '['){// массив
                std::pair<std::string, massiveStruct> toAdd;
                toAdd.first = keyName;
                toAdd.second = makeItMassiveStruct(oneLine, i);
                head_section->current_section->massive_values.push_back(toAdd);
            } else { //значит числа
                std::string intOrFloat;
                while(oneLine[i] != ','){
                    intOrFloat += oneLine[i];
                }
                bool isFloat = false;
                for (int j = 0; j < intOrFloat.size(); ++j) {
                    if (intOrFloat[j] == '.'){
                        isFloat = true;
                    }
                }
                if (isFloat){
                    std::pair<std::string, float> toAdd;
                    toAdd.first = keyName;
                    toAdd.second = std::stof(intOrFloat);
                    head_section->current_section->float_values.push_back(toAdd);
                } else {
                    std::pair<std::string, int> toAdd;
                    toAdd.first = keyName;
                    toAdd.second = std::stoi(intOrFloat);
                    head_section->current_section->int_values.push_back(toAdd);

                }
            }
        }
        return *head_section;

    }
};

omfl::__NameMe_ omfl::__NameMe_::parse(const std::filesystem::path &path){
    std::ifstream file;
    file.open(path);
    __NameMe_ parse_storage;
    parse_storage.head_section = &parse_storage;



    return parse_storage;
};
omfl::__NameMe_ omfl::__NameMe_::parse(const std::string &str){
    std::istringstream file(str);
    __NameMe_ parse_storage;
    parse_storage.head_section = &parse_storage;
    std::string current_string;
    bool one_invalid_string = false;
    while(file){
        file >> current_string;
        if (!valid_string(current_string)){
            one_invalid_string = true;
            break;
        } else {
            parse_storage.parse_this_string(current_string);
        }
    }
    if(one_invalid_string){
        parse_storage.head_section->valid_parse = false;
    } else parse_storage.head_section->valid_parse = true;

    return parse_storage;


}

omfl::__NameMe_::answerOrMassiveClass& omfl::__NameMe_::answerOrMassiveClass::find_key(std::string& key){

    for (int i = 0; i < current_section->string_values.size(); ++i) {
        if (current_section->string_values[i].first == key){

            theAnswer.second = 's';
            theAnswer.second = current_section->string_values[i].second;
            isAnswer = true;
            break;
        }
    }
    for (int i = 0; i < current_section->int_values.size(); ++i) {
        if (current_section->int_values[i].first == key){
            theAnswer.first = 'i';
            theAnswer.second = std::to_string(current_section->int_values[i].second);
            isAnswer = true;
            break;
        }
    }
    for (int i = 0; i < current_section->float_values.size(); ++i) {
        if (current_section->float_values[i].first == key){
            theAnswer.first = 'f';
            theAnswer.second = std::to_string(current_section->float_values[i].second);
            isAnswer = true;
            break;
        }
    }
    for (int i = 0; i < current_section->bool_values.size(); ++i) {
        if (current_section->bool_values[i].first == key){
            theAnswer.first = 'b';
            if (current_section->bool_values[i].second == true){
                theAnswer.second = "true";
            } else theAnswer.second = "false";
            isAnswer = true;
            break;
        }
    }
    for (int i = 0; i < current_section->massive_values.size(); ++i) {
        if (current_section->massive_values[i].first == key){
            massive = current_section->massive_values[i].second;
            isMassive = true;
        }
    }
    return *this;

}
omfl::__NameMe_::answerOrMassiveClass& omfl::__NameMe_::answerOrMassiveClass::Get(const std::string& key){
    //проходимся по всем секциям инвапиант - у нас название по порядку
    //ищем точку, чтобы определить подсекция ли это
        std::vector<std::string> sectionAndKeyNameVector = makeSectionNameVector(key);
        int where_sections_ends = -1;
        for (int i = 0; i < sectionAndKeyNameVector.size(); ++i) {
            for (int j = 0; j < current_section->pod_section_.size(); ++j) { //тк в конце может быть ключ, vjuen ,могут быть только названия секций
                if (sectionAndKeyNameVector[i] == current_section->pod_section_[j].first){
                    current_section = current_section->pod_section_[j].second;
                    where_sections_ends = i;
                }
            }
        }
    if (where_sections_ends == sectionAndKeyNameVector.size()-2){ //значит в конце есть ключ
        find_key(sectionAndKeyNameVector[sectionAndKeyNameVector.size()-1]);
    }
        return *this;
}
using namespace omfl;

 __NameMe_::answerOrMassiveClass __NameMe_::Get(const std::string& key){
    answerOrMassiveClass answerObject;
    answerObject.Get(key);
    return answerObject;
}
__NameMe_::answerOrMassiveClass& __NameMe_::answerOrMassiveClass::operator[](size_t const& index){
    if (massive.massKeys.size()-1 < index){
        theAnswer.first = '-';
        theAnswer.second = "";
        return *this;
    }
    if (massive.massKeys[index].first == 'm') {//тогда это значит, что там еще один массив
        massive = massive.massives[massive.massKeys[index].second];//теперь в нем лежит тот массив, что был раньше
        return *this;
    } else { //дошли до нормального значения в массиве
        int massiveIndex = massive.massKeys[index].second;
        if (massive.massKeys[index].first == 's'){
            theAnswer.first = 's';
            theAnswer.second = massive.stringMassValues[massiveIndex];
        } else if (massive.massKeys[index].first == 'b'){
            theAnswer.first = 'b';
            if (massive.boolMassValues[massiveIndex] == true){
                theAnswer.second = "true";
            } else theAnswer.second = "false";
        } else if (massive.massKeys[index].first == 'i'){
            theAnswer.first = 'i';
            theAnswer.second = std::to_string(massive.intMassValues[massiveIndex]);
        } else if (massive.massKeys[index].first == 'f'){
            theAnswer.first = 'f';
            theAnswer.second = std::to_string(massive.floatMassValues[massiveIndex]);
        }
    }
    return *this;
}



bool __NameMe_::answerOrMassiveClass::IsBool(){
    if (theAnswer.first == 'b'){
        return true;
    } return false;
}
bool __NameMe_::answerOrMassiveClass::IsInt(){
    if (theAnswer.first == 'i'){
        return true;
    } return false;
}
bool __NameMe_::answerOrMassiveClass::IsFloat(){
    if (theAnswer.first == 'f'){
        return true;
    } return false;
}
bool __NameMe_::answerOrMassiveClass::IsString(){
    if (theAnswer.first == 's'){
        return true;
    } return false;
}
bool __NameMe_::answerOrMassiveClass::IsArray(){
    if (theAnswer.first == 'm'){
        return true;
    } return false;
}

float __NameMe_::answerOrMassiveClass::AsFloat(){
    return std::stof(theAnswer.second);
}
bool __NameMe_::answerOrMassiveClass::AsBool(){
    if (theAnswer.second == "true"){
        return true;
    } return false;

}
int __NameMe_::answerOrMassiveClass::AsInt(){
    return std::stoi(theAnswer.second);
}
std::string __NameMe_::answerOrMassiveClass::AsString(){
    return theAnswer.second;
}

int __NameMe_::answerOrMassiveClass::AsIntOrDefault(int value){
    if (theAnswer.first == 'i') return std::stoi(theAnswer.second);
    return value;
}
std::string __NameMe_::answerOrMassiveClass::AsStringOrDefault(std::string value){
    if ( theAnswer.first == 's') return theAnswer.second;
    return value;
}
bool __NameMe_::answerOrMassiveClass::AsBoolOrDefault(bool value){
    if (theAnswer.first == 'b'){
        if (theAnswer.second == "true"){
            return true;
        } else return false;
    }
    return value;
}
float __NameMe_::answerOrMassiveClass::AsFloatOrDefault(float value){
    if(theAnswer.first == 'f') return std::stof(theAnswer.second);
    return value;
}

