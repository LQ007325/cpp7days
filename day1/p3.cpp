// ============================================================
// day1 p3  ——  数的性质判断
// ============================================================
// 读一个整数，依次输出是否偶数、是否为正、是否为零。
// 
// 样例: 输入 -4
//   偶数: 是   正数: 否   零: 否
// 
// 提示: 三个独立的 if（一个数可以同时是"偶数"和"负数"）
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
    int a;
    cout << "请输入一个整数:"<<endl;
    cin >> a;
   if (a%2==0 ){
    cout <<"是偶数"<<endl;
   }else{
    cout<<"是奇数"<<endl;
   }
   if(a>0){
    cout<<"是正数"<<endl;
   }else{
    cout<<"不是正数"<<endl;
   }

    // TODO: 开始写
    return 0;
}
