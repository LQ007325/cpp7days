// ============================================================
// day3 p1  ——  基础函数集
// ============================================================
// 自己写并在 main 里测试这四个函数:
//   int       max3(int a, int b, int c);
//   bool      isPrime(int n);
//   long long factorial(int n);
//   int       gcd(int a, int b);
// 
// 要求: 函数写在 main 上面；函数里只 return，不要 cout
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p1.cpp -o p1.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// ① max3：去掉 &
int max3(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= c) return b;
    return c;
}
// 注：第二个条件可以简化成 b >= c。因为能走到第二行，说明 a 已经被淘汰了

// ② isPrime：补上 return true，去掉 flag（用不上了）
bool isPrime(int n) {
    if (n < 2) return false;                  // 0 和 1 特判
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;                              // ← 关键
}

// ③ factorial：初始值改成 1，变量名改清楚
long long factorial(int n) {
    long long result = 1;                     // ← 1 不是 0！
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// ④ gcd：你写对了，一字不改
int gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}
int main() {
    
    
    
    return 0;
}
