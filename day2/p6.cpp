// ============================================================
// day2 p6  ——  数字反转
// ============================================================
// 读一个正整数，各位数字反转后输出（用 %10 和 /10，不用字符串）。
// 
// 样例: 1234→4321   1200→21   5→5
// 
// 核心三行:
//   int digit = n % 10;        取最后一位
//   rev = rev * 10 + digit;    左移一位再接上
//   n = n / 10;                去掉最后一位
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p6.cpp -o p6.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout<<"输入："<<endl;
    cin>>n;
    int m=0;
    while(n>0){
        m=m*10;
        m=m+n%10;
        n=n/10;
        
    }
    cout<<m<<endl;

    
    return 0;
}
