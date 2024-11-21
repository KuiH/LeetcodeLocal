#include<vector>
#include<iostream>
#include<stack>
#include<list>
#include<queue>
#include<deque>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<string>
#include<algorithm>
#include<memory>
#include<functional>
#include<random>

#include"ArguStrParser.h"
#include"ResultPrinter.h"
using namespace std;

class Solution {
public:
    int finalPositionOfSnake(int n, vector<string>& commands) {
        int res = 0;
        std::map<std::string, int> com_map = {
           {"UP", -n},
           {"RIGHT", 1},
           {"DOWN", n},
           {"LEFT", -1}
        };
        for (auto& c : commands) {
            res += com_map[c];
        }
        return res;
    }
};

//template<typename Func, typename ... Args>
//auto excute(Func&& function, Solution* solution, Args&& ... args)
//{
//    return (solution->*function)(args ...);
//}

template<typename FuncType, typename ClassType,  typename... Args>
auto excute(FuncType ClassType::* func, ClassType* obj, Args&&... args)
{
    return (obj->*func)(args...);
}



int main()
{
    
    std::string input = R"(["RIGHT","DOWN"])";
    using TargetType = std::vector<std::string>;
    TargetType parsedData = ArguStrParser::parseNestedVector<TargetType>(input);

    cout << "parsedData:" << endl;
    ResultPrinter::printResult(parsedData);

    Solution solution;
    auto res = excute(&Solution::finalPositionOfSnake, &solution,2, parsedData);
    cout << "\nres:" << endl;
    ResultPrinter::printResult(res);
    return 0;
}