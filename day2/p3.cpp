// ============================================================
// day2 p3  ——  9x9 乘法表
// ============================================================
// 打印 9x9 乘法表，用 \t 对齐，只打印下三角（j <= i）。
// 
// 输出（前两行示意）:
//   1*1=1
//   1*2=2   2*2=4
// 
// 提示: 外层 i 控行，内层 j 到 i 为止；endl 放在内层循环外面
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p3.cpp -o p3.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= i; j++) {
        cout << j << "*" << i << "=" << i * j << "\t";   // \t 是制表符，对齐用
    }
    cout << endl;
}
    // TODO: 开始写
    return 0;
}
