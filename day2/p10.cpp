// ============================================================
// day2 p10  ——  猜数字游戏
// ============================================================
// 程序随机想一个 1-100 的数，循环让用户猜，提示太大/太小，猜中后输出猜了几次。
// 
// 样例:
//   猜测: 50 → 太大了
//   猜测: 25 → 太小了
//   猜测: 42 → 猜中了！共猜了 3 次
// 
// 随机数: srand(time(0));  int answer = rand() % 100 + 1;   (需 <cstdlib> <ctime>)
// 骨架: while(true) + break，break 只在猜中那一支；count++ 放在判断之前
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p10.cpp -o p10.exe
// ============================================================

#include <iostream>
#include <cstdlib>          // rand, srand
#include <ctime>            // time
#include <windows.h>        // SetConsoleOutputCP
using namespace std;

int main() {
    SetConsoleOutputCP(65001);          // 防止中文乱码

    srand(time(0));                     // 设种子，只写一次
    const int answer = rand() % 100 + 1;   // 随机答案 1~100

    int guess;
    int count = 0;

    cout << "我想好了一个 1-100 的数，你来猜" << endl;

    while (true) {
        cout << "请输入你的猜测: ";
        cin >> guess;
        count++;

        if (guess == answer) {
            cout << "猜中了！共猜了 " << count << " 次" << endl;
            break;                      // 唯一出口
        } else if (guess > answer) {
            cout << "太大了" << endl;
        } else {
            cout << "太小了" << endl;
        }
    }

    return 0;
}
