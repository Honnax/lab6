#pragma once

#include <filesystem>
#include <istream>
#include <string>
#include <iostream>
#include <vector>
#include "ctype.h"

namespace omfl {
class __NameMe_ {
private:
    struct massiveStruct {
        massiveStruct ():massives(), stringMassValues(), intMassValues(), boolMassValues(), floatMassValues(){}
        std::vector<massiveStruct> massives;
        std::vector<std::string> stringMassValues;
        std::vector<int> intMassValues;
        std::vector<bool> boolMassValues;
        std::vector<float> floatMassValues;
        std::vector<std::pair<char, int>> massKeys;//сюда идем за индексами первое-тип, второе - их номер в том векторе
    };
    class answerOrMassiveClass {
        bool isAnswer;
        std::pair<char, std::string> theAnswer;
        bool isMassive;
        massiveStruct massive;
        __NameMe_* current_section;
    public:
        answerOrMassiveClass(): isAnswer(false), isMassive(false), theAnswer(), massive(), current_section(head_section){}
        answerOrMassiveClass& find_key(std::string& key);
        answerOrMassiveClass& operator[](size_t const& index);
        virtual answerOrMassiveClass& Get(const std::string& key);
        bool IsBool();
        bool IsInt();
        bool IsFloat();
        bool IsString();
        bool IsArray();

        float AsFloat();
        bool AsBool();
        int AsInt();
        std::string AsString();

        int AsIntOrDefault(int value);
        std::string AsStringOrDefault(std::string value);
        bool AsBoolOrDefault(bool value);
        float AsFloatOrDefault(float number);
    };
    static std::vector<std::string> makeSectionNameVector(const std::string &sectionName);
    massiveStruct makeItMassiveStruct(const std::string& oneLine, int& index);
    bool isSectionExist(const std::string& sectionName);

    friend answerOrMassiveClass& answerOrMassiveClass::Get(const std::string& key);
    friend answerOrMassiveClass& answerOrMassiveClass::find_key(std::string& key);
    friend answerOrMassiveClass& answerOrMassiveClass::operator[](size_t const& index);
    friend answerOrMassiveClass& answerOrMassiveClass::Get(const std::string& key);

    static __NameMe_* head_section;//родитель чтобы возвращаться при обходе
    __NameMe_* current_section;
    std::vector<std::pair<std::string, __NameMe_*>> pod_section_;//ссылки на подсекции
    std::vector<std::pair<std::string, std::string>> string_values;// название и то, что хранит
    std::vector<std::pair<std::string, int>> int_values;
    std::vector<std::pair<std::string, bool>> bool_values;

    std::vector<std::pair<std::string, float>> float_values;
    std::vector<std::pair<std::string, massiveStruct>> massive_values;
    static bool valid_parse;

    __NameMe_ parse_this_string(const std::string &str);
    bool valid_string(std::string get);

public:
    __NameMe_() : pod_section_(), string_values(), int_values(), bool_values(), float_values(), massive_values() {};
     __NameMe_ parse(const std::filesystem::path &path);
     __NameMe_ parse(const std::string &str);
    answerOrMassiveClass Get(const std::string& key);
    bool valid() const;
    friend __NameMe_ parse(std::string str);
};
}// namespace
omfl::__NameMe_ parse(std::string str);