// ============================================================
// day4 p4  ——  回文判断
// ============================================================
// 读一个字符串，判断是否回文（正读反读相同，不区分大小写）。
// 
// 样例: Level → 是回文      hello → 不是回文
// 
// 提示: 统一转小写再比较，或用两个下标从两头往中间夹
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p4.cpp -o p4.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

int main() {
    cout << "请输入字符串: ";
    string s;
    getline(cin, s);                   

    for (char& c : s) c = tolower(c);   

    int i = 0;
    int j = s.size() - 1;

    while (i < j) {                    
        if (s[i] != s[j]) {
            cout << "不是回文" << endl;
            return 0;
        }
        i++;
        j--;
    }
    cout << "是回文" << endl;    
    return 0;
}
