// ============================================================
// day3 p4  ——  计算器（今日主作品）
// ============================================================
// 读一行形如 10 / 4 的表达式，输出结果。每个运算一个函数，main 只负责读入→分发→打印。
// 
//   double add(double a, double b);
//   double sub(double a, double b);
//   double mul(double a, double b);
//   bool   divide(double a, double b, double& result);   除数为 0 返回 false
// 
// 样例: 10 / 4 → 2.5     7 % 2 → 不支持的运算符     5 / 0 → 错误：除数不能为 0
// 
// 提示: cin >> a >> op >> b;  会自动切分，op 用 char + switch 分发
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p4.cpp -o p4.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
double add(double a, double b){
    return a+b;
}
double sub(double a, double b){
    return a-b;
}
double mul(double a, double b){
    return a*b;
}
bool divide(double a, double b, double& result) {
    if (b==0) {        // b 几乎是 0
        return false;            // 失败！直接返回，不碰 result
    }
    result = a / b;              // 成功：把算出的结果写进外面的变量
    return true;
}


int main() {
    double a, b;
    char op;
    cout<<"请输入计算式："<<endl;
    cin >> a >> op >> b;

    double r;                              // 准备一个"空盒子"
    switch (op) {
        case '/':
            if (divide(a, b, r)) {         // ① 先问"成功了吗"
                cout << r << endl;         // ② 成功了才用 r
            } else {
                cout << "错误：除数不能为 0" << endl;
            }
            break;
        case'+':
            cout<<add(a,b)<<endl;break;
        case'-':
            cout<<sub(a,b);break;
        case'*':
            cout<<mul(a,b);break;
        
            
    }

    
    return 0;
}
