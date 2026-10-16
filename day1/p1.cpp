// ============================================================
// day1 p1  ——  输出与变量
// ============================================================
// 用变量存姓名、学号、专业，然后打印三行。
// 
// 预期输出（内容随你改）:
//   姓名: 林淇
//   学号: 2024001
//   专业: 计算机
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p1.cpp -o p1.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>          // ← 新增这一行，只为防中文乱码
using namespace std;

int main() {
    SetConsoleOutputCP(65001);   // ← 新增这一行：让屏幕按 UTF-8 显示中文

    string a,b,c;

    a = "林淇";
    b ="20263008555";
    c ="生医工";
    cout << "姓名: " << a << endl;
    cout << "学号: " << b << endl;
    cout << "专业: " << c << endl;

    // TODO: 学号、专业用同样方式补上，再各打印一行

    return 0;
}
