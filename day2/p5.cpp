// ============================================================
// day2 p5  ——  素数判断
// ============================================================
// 读 n，判断是否素数。循环条件用 i*i <= n；特判 n < 2。
// 
// 样例: 17→是素数   1→不是素数   9→不是素数   2→是素数
// 
// 提示: 试除从 i=2 开始（从 1 开始的话第一轮必然整除）
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p5.cpp -o p5.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout<<"输入"<<endl;
    cin >> n;
    bool a=true;
    if(n<2){
        a=false;}
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            a=false;
            break;
        }
    }
    if(a){
        cout<<"是素数"<<endl;
    }else{
        cout<<"不是素数"<<endl;
    }
    return 0;

    }
