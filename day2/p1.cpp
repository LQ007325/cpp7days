// ============================================================
// day2 p1  ——  1 到 100 求和
// ============================================================
// 用循环求和，再用公式 n*(n+1)/2 验证两者相等。
// 
// 输出:
//   循环求和=5050
//   公式验证=5050
//   一致: 是
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p1.cpp -o p1.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int sum=0,n=100,sum2=0;
    for(int i=1;i<=100;i+=1){
        sum=sum+i;
    }
    cout <<"循环求和："<<sum<<endl;
    sum2=n*(n+1)/2;
    cout<<"公式求和："<<sum2<<endl;

    return 0;
}
