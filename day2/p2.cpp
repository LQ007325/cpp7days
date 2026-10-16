// ============================================================
// day2 p2  ——  阶乘
// ============================================================
// 读 n（n ≤ 12，避免 int 溢出），输出 n!。
// 
// 样例: 5 → 120      0 → 1（边界情况）
// 
// 提示: 累乘初始值必须是 1（累加才是 0）
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
    int n,i,ji;
    ji=1;
    cout<<"请输入一个个位数"<<endl;
    cin>> n;
    for(i=1;i<=n;i++){
        ji*=i;
    }
    cout<<n<<"!="<<ji<<endl;


    // TODO: 开始写
    return 0;
}
