// ============================================================
// day4 p2  ——  倒序输出
// ============================================================
// 读 n 个数，倒序输出。两种写法都要写: ① 下标倒着遍历  ② 用 reverse 后再正着输出
// 
// 样例: 输入 3 换行 1 2 3  →  3 2 1
// 
// reverse(v.begin(), v.end());  需要 <algorithm>
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p2.cpp -o p2.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    cout<<"请输入数字个数"<<endl;
    int n;
    cin>>n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);            
    }
    reverse(v.begin(), v.end());
for (int x : v) {
    cout << x << " ";
}
    return 0;
}
