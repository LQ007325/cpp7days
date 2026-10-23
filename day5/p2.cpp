// ============================================================
// day5 p2  ——  学生排序（平均分 + 最高分）
// ============================================================
// 定义 struct Student { string name; int id; double score; };
// 读 5 个学生，输出平均分，以及最高分学生的姓名和分数。
//
// 样例输入:
//   5
//   张三 1 88
//   李四 2 95
//   王五 3 76
//   赵六 4 60
//   钱七 5 83
// 样例输出:
//   平均分: 80.4
//   最高分: 李四 (95)
//
// 提示: 打擂台时 best 存【下标】，不要存分数
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <numeric>
using namespace std;

struct Student {
    string name;
    int id;
    double score;
};


int main() {
    SetConsoleOutputCP(65001);

    // TODO 1: 读入 5 个学生，push_back 进 stus
    int n;
cin >> n;                     // ⚠️ 人数要读进来，别写死 5

vector<Student> stus;


for (int i = 0; i < n; i++) {
    Student s;                                  // ① 造一个空盒子
    cin >> s.name >> s.id >> s.score;           // ② 三个字段分别读
    stus.push_back(s);                          // ③ 整盒塞进 vector
}
if (stus.empty()) {
    cout << "没有学生" << endl;
    return 0;
}
    

    // TODO 2: 求和，算平均分，输出 "平均分: ..."
double sum = 0;
for (int i = 0; i < (int)stus.size(); i++) {
    sum += stus[i].score;        // ← 只加分数那一格
}
double average = sum / stus.size();
cout<<"平均分:"<<average<<endl;

    // TODO 3: 打擂台找最高分学生的【下标】
int best = 0;                                    // ① 第 0 个先当擂主

for (int i = 1; i < (int)stus.size(); i++) {     // ② 从第 1 个开始挑战
    if (stus[i].score > stus[best].score) {      // ③ 比擂主强吗？
        best = i;                                // ④ 强就换人
    }
}

// ⑤ 循环结束后，用 best 把人和分数都取出来
cout << "最高分: " << stus[best].name << " (" << stus[best].score << ")" << endl;



    // TODO 4: 输出 "最高分: 姓名 (分数)"

    return 0;
}
