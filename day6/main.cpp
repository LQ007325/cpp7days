// ============================================================
// day6 main  ——  多文件工程（main.cpp）
// ============================================================
// 在 switch 里补全 case 1..7，调用 student.h 里声明的函数。
// 
// 编译命令:
//   g++ -std=c++17 -Wall -g main.cpp student.cpp -o app.exe
// 
// 附加任务: 故意制造 8 种报错并修复（见练习册 Day6）
// 附加任务: 在 sortByScore 里打断点，按 F5 单步，观察 vector 的变化
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall main.cpp -o main.exe
// ============================================================

#include "student.h"
#include <iostream>
using namespace std;

int main() {
    vector<Student> list;
    while (true) {
        cout << "\n===== 学生成绩管理系统 =====\n";
        cout << "1.添加 2.删除 3.查找 4.改分 5.显示 6.排序 7.平均分 0.退出\n请选择: ";
        int choice;
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, char(10)); continue; }
        switch (choice) {
            case 0: return 0;
            // TODO: 补全 case 1..7，调用对应函数
            default: cout << "无效选择\n";
        }
    }
}
