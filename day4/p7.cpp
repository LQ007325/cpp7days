// ============================================================
// day4 p7  ——  pair 练习
// ============================================================
// 读 n 组"名字 分数"，存进 vector<pair<string,int>>，按分数从高到低输出；分数相同时按名字升序。
// 
// 样例: 输入 3 换行 张三 88 / 李四 95 / 王五 88
//   李四 95
//   张三 88
//   王五 88
//   ⚠️ 中文名字不按拼音排！sort 比的是 Unicode 编码（张 U+5F20 < 王 U+738B）。
//      想按拼音要自己写映射表，超出本周范围。用英文名测试更直观（Alice < Bob）。
// 
// 自定义比较用 lambda:
//   sort(v.begin(), v.end(), [](const pair<string,int>& a, const pair<string,int>& b) { ... });
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p7.cpp -o p7.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

int main() {
    cout<<"请输入学生个数:"<<endl;
    int n;
cin >> n;

vector<pair<string, int>> scores;        // 空箱子

for (int i = 0; i < n; i++) {
    string name;
    int score;
    cin >> name >> score;                // ✅ 一行读两个（你 Day1 就学过）
    scores.push_back({name, score});     // ✅ 组装 + 塞进去
}
sort(scores.begin(), scores.end(), [](const pair<string,int>& a,
                                      const pair<string,int>& b) {

    // 第①条：分数不一样 → 按分数排，大的在前
    if (a.second != b.second) {
        return a.second > b.second;      // 88 > 60 → true → a 在前
    }                                     //   ↑ 大于号 = 降序

    // 第②条：分数一样 → 按名字排，小的在前
    return a.first < b.first;            // "Alice" < "Bob" → true → a 在前
                                          //    ↑ 小于号 = 升序
});
for (auto& [name, score] : scores) {
    cout << name<<" "<<score;
}
    return 0;
}
