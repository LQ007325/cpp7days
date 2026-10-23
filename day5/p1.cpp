// ============================================================
// day5 p1  ——  Point 与距离
// ============================================================
// 定义 struct Point { double x, y; };
// 读入两个点的坐标，输出它们的距离。
//
// 样例: 输入 0 0 3 4   ->   距离 = 5
//
// 提示:
//   double distance(const Point& a, const Point& b) {
//       double dx = a.x - b.x;
//       double dy = a.y - b.y;
//       return sqrt(dx * dx + dy * dy);
//   }
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
// ============================================================

#include <iostream>
#include <string>
#include <cmath>       // sqrt
#include <windows.h>   // SetConsoleOutputCP
using namespace std;

struct Point {
    double x;
    double y;
};

// TODO 1: 在这里写 distance 函数
double distance(const Point& a, const Point& b) {
      double dx = a.x - b.x;
      double dy = a.y - b.y;
      return sqrt(dx * dx + dy * dy);
  }



int main() {
    SetConsoleOutputCP(65001);

    Point a, b;

    cin >> a.x >> a.y >> b.x >> b.y;

    double d = distance(a, b);

    cout << "距离 = " << d << endl;

    return 0;
}







