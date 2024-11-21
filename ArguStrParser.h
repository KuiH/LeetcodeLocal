#pragma once
#include<string>
#include<type_traits>
#include<vector>
#include<sstream>
#include<algorithm>

class ArguStrParser {
public:
    // ��ں���
    template <typename T>
    static T parseNestedVector(std::string& str);

private:
    template <typename T>
    static T _parseNestedVector(const std::string& str);

    // һЩ�ػ�
    template <>
    static std::vector<int> _parseNestedVector(const std::string& str);

    template <>
    static std::vector<double> _parseNestedVector(const std::string& str);

    template <>
    static std::vector<std::string> _parseNestedVector(const std::string& str);
};


template <typename T>
T ArguStrParser::parseNestedVector(std::string& str) {
    // ȥ�ո�
    str.erase(std::remove_if(str.begin(), str.end(), [](char c) { return c == ' ' || c == '\n' || c=='\"'; }), str.end());
    return ArguStrParser::_parseNestedVector<T>(str); //��������������һά�ģ���ֱ�ӵ����ػ��İ汾
}


template <typename T>
T ArguStrParser::_parseNestedVector(const std::string& str) {
    using ValueType = typename T::value_type;

    //if constexpr (std::is_same_v<ValueType, int>) {
    //    return _parseNestedVector<std::vector<int>>(str);
    //}
    //else {

    T result;
    std::string content = str.substr(1, str.size() - 2); // ȥ����㷽����

    int bracketCount = 0;
    std::string buffer;
    for (char ch : content) {
        if (ch == ',' && buffer.empty()) { //�ս�����һ��Ҷ�ڵ㣬���ж���Ķ���
            continue; 
        }
        if (ch == '[') {
            bracketCount++;
        }
        if (ch == ']') {
            bracketCount--;
        }
        buffer += ch;

        if (bracketCount == 0 && !buffer.empty()) {
            result.push_back(_parseNestedVector<ValueType>(buffer));
            buffer.clear();
        }
    }
    return result;

    //}
}


template <>
std::vector<int> ArguStrParser::_parseNestedVector(const std::string& str) {
    std::vector<int> result;
    std::string content = str.substr(1, str.size() - 2); // ȥ�����ߵķ�����
    std::stringstream ss(content);
    std::string token;
    while (std::getline(ss, token, ',')) {
        result.push_back(std::stoi(token));
    }
    return result;
}

template <>
std::vector<double> ArguStrParser::_parseNestedVector(const std::string& str) {
    std::vector<double> result;
    std::string content = str.substr(1, str.size() - 2);
    std::stringstream ss(content);
    std::string token;
    while (std::getline(ss, token, ',')) {
        result.push_back(std::stod(token));
    }
    return result;
}

template <>
std::vector<std::string> ArguStrParser::_parseNestedVector(const std::string& str) {
    std::vector<std::string> result;
    std::string content = str.substr(1, str.size() - 2);
    std::stringstream ss(content);
    std::string token;
    while (std::getline(ss, token, ',')) {
        result.push_back(token);
    }
    return result;
}