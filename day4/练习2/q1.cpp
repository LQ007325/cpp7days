// ============================================================
// day4 加练 q1  ——  最值与差值   ⭐
// ============================================================
// 输入:  5
//        3 7 1 9 4
//
// 输出:  最大值: 9
//        最小值: 1
//        差值: 8
//
// 考什么: max_element / min_element 返回的是"位置"，前面要加 *
// ⚠️ 坑: v 为空时 max_element 返回 v.end()，*v.end() 是越界
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall q1.cpp -o q1.exe
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>
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