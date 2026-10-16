// ============================================================
// day4 p6  ——  去重（两种写法）
// ============================================================
// 读 n 个数，输出去重后的结果（升序）。两种写法都要写:
//   写法一: sort + unique + erase
//   写法二: set
// 
// 样例: 输入 6 换行 3 1 4 1 5 3  →  1 3 4 5
// 
// 三步曲: sort(v.begin(),v.end());  v.erase(unique(v.begin(),v.end()), v.end());
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p6.cpp -o p6.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    cout<<"请输入数字个数:";
    int n;
    cin>>n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);            
    }
    if (v.empty()) { cout << "没有输入任何数字" << endl; return 0; }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()), v.end());
    for (int x : v) cout << x << " ";
cout << endl;


    

    return 0;
}
