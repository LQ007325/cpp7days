// ============================================================
// day3 p2  ——  引用传参（今天的重点）
// ============================================================
// 写并验证:
//   void swap2(int& a, int& b);                  交换两个数
//   void divmod(int a, int b, int& q, int& r);   同时算出商和余数
// 
// 样例: 输入 17 5  →  商=3 余数=2
// 验证交换: swap2(a,b) 后必须是 a=8 b=3（变了才对）
// 
// 实验: 把 & 删掉再跑一次，看结果怎么变 —— 亲手体验值传递 vs 引用传递
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p2.cpp -o p2.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
void swap2(int&a, int&b){
    int t=a;
    a=b;
    b=t;
}
void divmod(int a, int b, int&q, int&r){
    q=a/b;
    r=a%b;
}



int main() {
    int a=4;
    int b=8;
    cout<<"交换前a为"<<a<<"b为"<<b<<endl;
    swap2(a,b);
    cout<<"交换后a为"<<a<<",b为"<<b<<endl;
    int m=32,n=26;
    int x,y;
    divmod(m,n,x,y);
    cout<<m<<"除以"<<n<<"商为"<<x<<","<<"余数为"<<y<<endl;


    return 0;
}
