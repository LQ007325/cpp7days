// ============================================================
// day4 加练 q3  ——  按绝对值排序   ⭐⭐
// ============================================================
// 输入:  5
//        -3 1 -7 2 -5
//
// 输出:  1 2 -3 -5 -7
//
// 要求: 按绝对值从小到大排（绝对值相同就随便）
// 考什么: lambda 自定义规则的第一关 —— 先加工再比较
// 提示: abs(x) 求绝对值（#include <cmath>）
//
// 规则函数: sort(v.begin(), v.end(), [](int a, int b) {
//               return _______;   // 问: a 该排在 b 前面吗？
//           });
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    cout << "请输入数字个数: ";
    int n;
    cin >> n;

    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);
    }

    // TODO: 开始写


    return 0;
}