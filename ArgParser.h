#pragma once

#include <cstring>
#include <iostream>
#include <vector>
#include <sstream>


namespace ArgumentParser {

class ArgParser {
private:

    std::vector<std::string> params_;
    std::vector<std::string> vec_for_description_for_strings_;
    std::vector<std::string> added_arguments_;
    std::vector<std::pair<char, std::string>> added_arguments_and_char_;
    std::vector<std::string*> arguments_;
    std::vector<int> *int_arguments_{};
    std::vector<std::pair<std::string, std::string>> pair_for_store_value_;
    std::vector<std::pair<std::string, bool>> pair_for_bool_store_value_;
    std::vector<std::pair<bool, std::pair<char, std::string>>> pair_for_flags_;
    std::vector<uint8_t> vec_for_bool_;
    std::vector<std::string> vec_for_description_char_and_flag_;
    std::vector<std::pair<std::string, std::string>> vec_for_description_;
    std::vector<bool*> vec_for_bool_store_value;

    bool flag_argc_argv_ = false;
    bool flag_default_ = false;
    bool flag_add_str_ = false;
    bool flag_store_value_ = false;
    bool flag_store_values_ = false;
    bool flag_store_values_bool_ = false;
    bool flag_multi_ = false;
    bool flag_add_int_ = false;
    bool flag_mult = false;
    bool flag_sum = false;
    bool* bool_store_value{};
    bool flag_position_ = false;
    bool flag_help_ = false;

    std::string vec_for_help_[3];
    std::string* store_value_{};
    std::string string_for_store_value_;
    std::string string_for_bool_;
    std::string parser_name_;
    uint32_t mid_count_ = 0;
    uint32_t min_arg_count_ = 0;
    uint32_t counter_ = 0;

public:
    explicit ArgParser(const std::string &parser_name);

    bool Parse(std::vector<std::string> vec_strings);

    bool Parse(int argc, char** argv);

    ArgParser& AddStringArgument(const std::string& string_argument);

    ArgParser& AddStringArgument(char char_argument, const std::string& string_argument);

    ArgParser& AddStringArgument(char char_to_add, const std::string& string_to_add, const std::string& some_description);

    ArgParser& AddIntArgument(const std::string& int_argument);

    ArgParser& AddIntArgument(const std::string& int_argument, const std::string& some_description);

    ArgParser& AddIntArgument(char char_to_add, const std::string& int_argument);

    ArgParser& AddFlag(char char_to_add, const std::string& string_to_add);

    ArgParser& AddFlag(const std::string& str_to_add, const std::string& description);

    ArgParser& AddFlag(char char_to_add, const std::string& string_to_add, const std::string& some_description);

    ArgParser& MultiValue(uint32_t min_count = 0);

    ArgParser& Default(const std::string& string_default);

    ArgParser& Default(int flag);

    std::string& StoreValue(std::string& string_value);

    bool& StoreValue(bool& bool_value);

    std::vector<int>& StoreValues(std::vector<int>& vector_value);

    ArgParser& Positional();

    std::string GetStringValue(std::string string);

    long long GetIntValue(std::string string);

    int GetIntValue(const std::string& string, uint32_t Value);

    bool GetFlag(const std::string& string);

    ArgParser& AddHelp(char char_to_add, const std::string& string_to_add, const std::string& some_description);

    bool Help();

    std::string HelpDescription();
};

} // namespace ArgumentParser