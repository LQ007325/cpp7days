// ============================================================
// day2 p4  ——  打印图形
// ============================================================
// 读 n，打印菱形（正三角 + 倒三角）。
// 
// 样例: 输入 3
//     *
//    ***
//   *****
//   *****
//    ***
//     *
// 
// 规律（先列表格再写代码）:
//   第 i 行: 空格 n-i 个,  星号 2*i-1 个
//   下半部分: 循环改成 i 从 n 到 1，循环体完全一样
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p4.cpp -o p4.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout << "输入 n: ";
    cin >> n;

    // ===== 上半部分：正三角形 =====
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) {
            cout << " ";              // 空格越往下越少
        }
        for (int k = 1; k <= 2*i - 1; k++) {
            cout << "*";              // 星号不要 endl！
        }
        cout << endl;                 // 一整行结束，换行
    }

    // ===== 下半部分：倒三角形（和上面一模一样的循环体）=====
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        for (int k = 1; k <= 2*i - 1; k++) {
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}
