// ============================================================
// day6 student  ——  多文件工程（student.cpp）
// ============================================================
// 实现 student.h 里声明的每个函数。
// 
// 编译命令（三个文件一起编译）:
//   g++ -std=c++17 -Wall -g main.cpp student.cpp -o app.exe
// 
// 本文件只放"怎么做"，声明在 student.h，菜单在 main.cpp
//
// 编译运行: VS Code 里 Ctrl+Shift+P → Run Task → build-all
//           或终端:  cd C:\Users\LinQi\Desktop\cpp7days\day6 && g++ -std=c++17 -Wall -g *.cpp -o app.exe
// ============================================================

#include "student.h"
#include <iostream>
#include <algorithm>

// TODO: 在这里实现 student.h 里声明的每个函数
void addStudent(vector<Student>& list) {      // 要改 list，所以用 &
    Student s;
    cout << "姓名 学号 成绩: ";
    cin >> s.name >> s.id >> s.score;
    list.push_back(s);
    cout << "已添加" << endl;
}
// void removeStudent(vector<Student>& list);
void removeStudent(vector<Student>& list) {
    if (list.empty()) { cout << "暂无学生" << endl; return; }

    string id;
    cout << "要删除的学号: ";
    cin >> id;

    for (int i = 0; i < (int)list.size(); i++) {
        if (list[i].id == id) {
            list.erase(list.begin() + i);
            cout << "已删除" << endl;
            return;
        }
    }

    cout << "没找到学号 " << id << endl;
}


void findById(const vector<Student>& list) {
    if (list.empty()) { cout << "暂无学生" << endl; return; }

    string id;
    cout << "要查找的学号: ";
    cin >> id;

    
    for (int i = 0; i < (int)list.size(); i++) {
    if (list[i].id == id) {          
        cout << "找到: " << list[i].name << endl;
        return;                       
    }
}

    cout << "没找到学号 " << id << endl;
}
// void updateScore(vector<Student>& list);
void updateScore(vector<Student>& list) {      // ← 注意：这里没有 const
    if (list.empty()) { cout << "暂无学生" << endl; return; }

    string id;
    cout << "要改分的学号: ";
    cin >> id;

    // TODO: 遍历 list，找到 list[i].id == id
    //       输出当前分数，读入新分数存进 list[i].score
    //       "已修改" 然后 return
    for(int i=0;i<(int)list.size();i++){
        if(list[i].id==id){
            cout<<"当前分数:"<<list[i].score<<endl;
            cout<<"请输入修改后分数：";
            cin>>list[i].score;
            cout<<"已修改成功"<<endl;
            return;
        }
    }

    cout << "没找到学号 " << id << endl;
}
// void showAll(const vector<Student>& list);
void showAll(const vector<Student>& list) {   // 只读，所以用 const &
    if (list.empty()) {
        cout << "暂无学生" << endl;
        return;
    }
    for (int i = 0; i < (int)list.size(); i++) {
        cout << i + 1 << ". " << list[i].name
             << "  " << list[i].id
             << "  " << list[i].score << endl;
    }
}
// void sortByScore(vector<Student>& list);
void sortByScore(vector<Student>& list) {
    if (list.empty()) { cout << "没有学生" << endl; return; }

    // ↓↓↓ 调试代码：排序前看一眼
    cout << "[调试] 排序前 " << list.size() << " 人: ";
    for (auto& s : list) cout << s.name << "(" << s.score << ") ";
    cout << endl;

    sort(list.begin(), list.end(), [](const Student& a, const Student& b) {
        return a.score > b.score;
    });

    // ↓↓↓ 调试代码：排序后看一眼
    cout << "[调试] 排序后 " << list.size() << " 人: ";
    for (auto& s : list) cout << s.name << "(" << s.score << ") ";
    cout << endl;

    showAll(list);
}
// void showAverage(const vector<Student>& list);
void showAverage(const vector<Student>& list) {
    if (list.empty()) { cout << "暂无学生" << endl; return; }

    double sum = 0;
    for (int i = 0; i < (int)list.size(); i++) {
        sum += list[i].score;
    }
    cout << "人数: " << list.size() << endl;
    cout << "平均分: " << sum / list.size() << endl;
}
// 提示：实现里不要写 using namespace std 之外的花样，先把功能跑通
