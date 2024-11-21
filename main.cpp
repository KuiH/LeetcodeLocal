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
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<int> res;
        int next[100005] = { 0 };
        for (int i = 0; i < n-1; ++i) { next[i] = i + 1; }
        int cur_len = n - 1;
        for (auto& q : queries) {
            if (next[q[0]] == -1) {  //这条边已经被删除
                res.push_back(cur_len);
                continue; 
            } 
            //删除节点
            int p = next[q[0]];
            while (p != -1 && p < q[1]) {
                int temp = next[p]; 
                next[p] = -1;
                p = temp;
                cur_len--;
            }
            next[q[0]] = q[1];
            res.push_back(cur_len);
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
    
    std::string input = "[[[0.34,323.9],[0,2]],[[0.34,323.9],[0,2]]]";
    using TargetType = std::vector<std::vector<std::vector<double>>>;
    TargetType parsedData = ArguStrParser::parseNestedVector<TargetType>(input);

    cout << "parsedData:" << endl;
    ResultPrinter::printResult(parsedData);

    //Solution solution;
    //auto res = excute(&Solution::shortestDistanceAfterQueries, &solution, 4, parsedData);
    //cout << "\nres:" << endl;
    //ResultPrinter::printResult(res);
    return 0;
}