// ============================================================
// day3 p5  ——  计算器循环版
// ============================================================
// 把 p4 包进 while(true)，可以连续计算，输入 q 退出。
// 
// 样例:
//   1 + 2 → 3
//   10 / 4 → 2.5
//   q → 再见
// 
// 退出判断: if (!(cin >> a)) break;   ← 读不到数字（比如输入 q）就退出
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p5.cpp -o p5.exe
// ============================================================

#include <iostream>
#include <windows.h>          // SetConsoleOutputCP
using namespace std;

// ==================== 四个运算函数 ====================
double add(double a, double b) {
    return a + b;
}

double sub(double a, double b) {
    return a - b;
}

double mul(double a, double b) {
    return a * b;
}

// 返回 bool 报告"成功/失败"，用引用把结果带回来
bool divide(double a, double b, double& result) {
    if (b == 0) {
        return false;              // 失败：不碰 result
    }
    result = a / b;                // 成功：写进引用参数
    return true;
}

// ==================== 主程序 ====================
int main() {
    SetConsoleOutputCP(65001);

    while (true) {
        double a, b;
        char op;

        cout << "请输入表达式(输入 q 退出): ";

        if (!(cin >> a)) {         // 读不到数字（比如输入了 q）→ 退出
            cout << "再见" << endl;
            break;
        }
        cin >> op >> b;            // 再读运算符和第二个数

        double r;
        switch (op) {
            case '+':
                cout << add(a, b) << endl;
                break;
            case '-':
                cout << sub(a, b) << endl;
                break;
            case '*':
                cout << mul(a, b) << endl;
                break;
            case '/':
                if (divide(a, b, r)) {
                    cout << r << endl;
                } else {
                    cout << "错误：除数不能为 0" << endl;
                }
                break;
            default:                                        // ← default 在 switch 里面
                cout << "不支持的运算符(只支持 + - * /)" << endl;
                break;
        }                                                   // ← switch 在这里结束
    }                                                       // ← while 在这里结束

    return 0;                                               // ← return 和 0 之间有空格
}                                                           // ← main 在这里结束
