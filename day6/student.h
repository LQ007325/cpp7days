#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
using namespace std;

struct Student {
    string name;
    string id;      // 学号用 string，可能含字母或以 0 开头
    double score;
};

// TODO: 在这里声明 7 个函数（声明时参数写不写名字都行，建议写上）
void addStudent(vector<Student>& list);
void removeStudent(vector<Student>& list);
void findById(const vector<Student>& list);
void updateScore(vector<Student>& list);
void showAll(const vector<Student>& list);
void sortByScore(vector<Student>& list);
void showAverage(const vector<Student>& list);

#endif
