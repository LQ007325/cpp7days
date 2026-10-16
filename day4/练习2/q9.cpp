// ============================================================
// day4 加练 q9  ——  前 3 名   ⭐⭐⭐
// ============================================================
// 输入:  5
//        Alice 88
//        Bob 95
//        Cindy 88
//        Dave 70
//        Eve 95
//
// 输出:  第 1 名: Bob 95
//        第 2 名: Eve 95
//        第 3 名: Alice 88
//
// 规则: 分数降序；分数相同按名字升序
// 考什么: 和 p7 一模一样的模式（pair + lambda 多字段排序），只取前 3 个
//
// ⚠️ 坑:
//   1. 总人数少于 3（只有 2 个学生）→ 不能硬输出 3 行！
//      用 min(3, (int)scores.size()) 或者 if 判断
//   2. scores.size() 是无符号数 —— 用在 i < scores.size() 里没问题（不加不减就行）
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

int main() {
    cout << "请输入学生个数: ";
    int n;
    cin >> n;

    vector<pair<string, int>> scores;
    for (int i = 0; i < n; i++) {
        string name;
        int score;
        cin >> name >> score;
        scores.push_back({name, score});
    }

    // TODO: 开始写


    return 0;
}