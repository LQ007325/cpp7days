// ============================================================
// day4 p3  ——  单词统计
// ============================================================
// 用 getline 读一整行，统计有几个单词（空格分隔，忽略连续空格）。
// 
// 样例: 输入 "hello   world  cpp"  →  单词数=3
// 
// 坑点: cin >> n 之后紧跟 getline，必须先写 cin.ignore();
//       否则 getline 读到的是那个残留的回车，结果是空字符串
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p3.cpp -o p3.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    cout<<"请输入英文单词:"<<endl;            
string s;
getline(cin, s); 
int count = 0;
for (int i = 0; i < s.size(); i++) {
    if (s[i] != ' ' && (i == 0 || s[i-1] == ' ')) {
        count++;
    }
}     
cout<<"共"<<count<<"个单词";   
    return 0;
}
