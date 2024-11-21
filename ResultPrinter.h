#pragma once
#include<iostream>

class ResultPrinter {
public:
    // ��ں�����ȥ���ո񲢵��õݹ��������
    template <typename T>
    static void printResult(T& obj);

};

template<typename T>
inline void ResultPrinter::printResult(T& obj)
{
    if constexpr (std::is_same_v<T, int>) {
        std::cout << obj << ' ';
    }
    else if constexpr (std::is_same_v<T, double>) {
        std::cout << obj << ' ';
    }
    else if constexpr (std::is_same_v<T, float>) {
        std::cout << obj << ' ';
    }
    else if constexpr (std::is_same_v<T, bool>) {
        std::cout << obj << ' ';
    }
    else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << obj << ' ';
    }
    else {
        for (auto& i : obj)
        {
            ResultPrinter::printResult(i);
        }
    }
}
