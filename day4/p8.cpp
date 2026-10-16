// ============================================================
// day4 p8  ——  成绩统计器（今日主作品）
// ============================================================
// 不断读分数，输入 -1 结束，然后输出: 人数、平均分、最高分、最低分、及格率、排序后的列表。
// 
// 样例: 输入 88 45 92 60 73 -1
//   人数: 5
//   平均分: 71.6
//   最高分: 92
//   最低分: 45
//   及格率: 80%
//   排序后: 45 60 73 88 92
// 
// 循环条件: while (cin >> x && x != -1)
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p8.cpp -o p8.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    cout<<"请输入成绩：";
    int x;
    vector<int> v;
while (cin >> x && x != -1) {
    v.push_back(x);          // 读到 -1 就停，-1 不会被存进去
}
if (v.empty()) {                    
    cout << "没有输入任何成绩" << endl;
    return 0;}
cout<<"人数："<<v.size()<<endl;
cout << "平均分=" << accumulate(v.begin(), v.end(), 0.0) / v.size() << endl;
cout << "最高分=" << *max_element(v.begin(), v.end()) << endl;
cout << "最低分=" << *min_element(v.begin(), v.end()) << endl;
int passCount = count_if(v.begin(), v.end(), [](int x) { return x >= 60; });
    cout << "及格率: " << (100.0 * passCount / v.size()) << "%" << endl;
sort(v.begin(),v.end());
    cout<<"排序后:";
    for(int x:v){
        cout<<x<<" ";
    }
    return 0;
}
