// ============================================================
// day5 p6  ——  学生成绩管理系统 v1（今日主作品，内存版）
// ============================================================
// 菜单驱动，数据存在 vector<Student>，每个功能一个函数。
//
//   1.添加 2.删除 3.按学号查找 4.修改成绩
//   5.显示全部 6.按成绩排序 7.统计平均分 0.退出
//
// 要求:
//   - 每个选项一个函数（addStudent / removeStudent / findByld / ...）
//   - 主循环 while(true) + switch，选 0 用 break 退出
//   - 要修改 list 的函数用 vector<Student>&
//   - 只读的函数用 const vector<Student>&
//   - 删除/查找不存在的学号要给提示，不能崩
//   - 删除时用 list.erase(list.begin() + i)，删完立刻 return
//
// 分步做，别一次写完:
//   第1步: 添加 + 显示 + 退出
//   第2步: 排序 + 平均分
//   第3步: 查找 + 改分
//   第4步: 删除
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
using namespace std;

struct Student {
    string name;
    string id;        // 学号用 string，可能含字母或以 0 开头
    int score;
};

// TODO 1: 七个函数的【声明】写在这里
// void addStudent(vector<Student>& list);
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

// void findByld(vector<Student>& list);
void findById(const vector<Student>& list) {
    if (list.empty()) { cout << "暂无学生" << endl; return; }

    string id;
    cout << "要查找的学号: ";
    cin >> id;

    // TODO: 遍历 list，如果 list[i].id == id
    //       就输出这个学生，然后 return
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
    if (list.empty()) { cout << "暂无学生" << endl; return; }

    sort(list.begin(), list.end(), [](const Student& a, const Student& b) {
        return a.score > b.score;      // 大的排前面
    });

    cout << "已按成绩从高到低排序" << endl;
    showAll(list);                      // 排完直接显示，省得再按 5
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

// TODO 2: 七个函数的【实现】写在 main 上面（或者 main 下面，但上面要声明）


int main() {
    SetConsoleOutputCP(65001);

    vector<Student> list;
    while (true) {
        cout << "\n1.添加 2.删除 3.查找 4.改分 5.显示 6.排序 7.平均 0.退出" << endl;
        cout << "请选择: ";

        int choice;
        if (!(cin >> choice)) break;      // ⚠️ 输入失败就退出，防止死循环
        if (choice == 0) break;

        switch (choice) {
    case 1: addStudent(list);    break;
    case 2: removeStudent(list); break;
    case 3: findById(list);      break;
    case 4: updateScore(list);   break;
    case 5: showAll(list);       break;
    case 6: sortByScore(list);   break;
    case 7: showAverage(list);   break;
    default: cout << "请输入 0-7 之间的数字" << endl; break;
}
    }

    cout << "再见" << endl;
    return 0;
}


    

