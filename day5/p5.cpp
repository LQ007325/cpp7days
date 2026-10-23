// ============================================================
// day5 p5  ——  Counter 类
// ============================================================
// 写一个类，private 一个 int n，
// 提供四个成员函数: inc() 加一、dec() 减一、get() const 查询、reset() 归零。
//
// 要求输出:
//   初始: 0
//   加3次: 3
//   减1次: 2
//   重置: 0
//
// 必做实验:
//   在 main 里写一行 c.n = 5;  然后编译，看报错:
//   error: 'int Counter::n' is private within this context
//   这个报错就是 private 存在的意义
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
// ============================================================

#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class Counter {
private:
    int n;

public:
    // TODO 1: 构造函数，把 n 初始化为 0
    Counter() { n = 0; }

    // TODO 2: void inc()
    void inc() { n++; }


    // TODO 3: void dec()
    void dec() { n--; }

    // TODO 4: int get() const      <- 注意 const
     int get() const { return n; }

    // TODO 5: void reset()
    void reset() { n = 0; }
};

int main() {
    SetConsoleOutputCP(65001);

    // TODO 6: 创建 Counter，依次测试
    Counter c;       // ② 一旦创建，n 就是 0
c.inc();                    // ③ 点号里带着 c
c.inc();
c.inc();
cout<<c.get()<<endl;
c.dec();
cout<<c.get()<<endl;
cout << c.get() << endl;    // ④ 读出来
c.reset(); 
cout<<c.get()<<endl;
    //         初始 / 加3次 / 减1次 / 重置

    return 0;
}
