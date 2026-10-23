// ============================================================
// day5 p3  ——  按字段排序（lambda 第一课）
// ============================================================
// 在 p2 的基础上，按分数从高到低输出全部学生；
// 分数相同时，按学号从【小到大】。
//
// 输入和 p2 一样的 5 个学生
// 样例输出:
//   李四 2 95
//   张三 1 88
//   钱七 5 83
//   王五 3 76
//   赵六 4 60
//
// 提示（这个模式今天最重要，主作品也要用）:
//   sort(stus.begin(), stus.end(), [](const Student& a, const Student& b) {
//       if (a.score != b.score) return a.score > b.score;
//       return a.id < b.id;
//   });
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>   // sort
#include <windows.h>
using namespace std;

struct Student {
    string name;
    int id;
    double score;
};

int main() {
    SetConsoleOutputCP(65001);

    vector<Student> stus;

    // TODO 1: 读入 5 个学生
    int n;
cin >> n;                     // ⚠️ 人数要读进来，别写死 5




for (int i = 0; i < n; i++) {
    Student s;                                  // ① 造一个空盒子
    cin >> s.name >> s.id >> s.score;           // ② 三个字段分别读
    stus.push_back(s);                          // ③ 整盒塞进 vector
}
if (stus.empty()) {
    cout << "没有学生" << endl;
    return 0;
}


    // TODO 2: 用 sort + lambda 排序（分数降序，学号升序）
     sort(stus.begin(), stus.end(), [](const Student& a, const Student& b) {
        if(a.score!=b.score)
        return a.score > b.score;      // 大的排前面
        return a.id < b.id;
    });


    // TODO 3: 遍历输出 "姓名 学号 分数"
    for (int i = 0; i < (int)stus.size(); i++) {
        cout << i + 1 << ". " << stus[i].name
             << "  " << stus[i].id
             << "  " << stus[i].score << endl;
    }


    return 0;
}
