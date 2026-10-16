// ============================================================
// day3 p3  ——  vector 当参数
// ============================================================
// 写并验证（都用 const vector<int>&，不复制 + 不改）:
//   int    sumOf(const vector<int>& v);
//   double averageOf(const vector<int>& v);
//   int    maxOf(const vector<int>& v);
// 
// 样例: 输入 5 换行 10 20 30 40 50  →  和=150 平均=30 最大=50
// 
// 坑: 平均分要写 sum * 1.0 / v.size()，不能写 sum / v.size()
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p3.cpp -o p3.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int sumOf(const vector<int>& v) {
    int sum = 0;
    for (int i = 0; i < v.size(); i++) {     // 注意是 v.size()，不是 n
        sum += v[i];
    }
    return sum;
}
int maxOf(const vector<int>& v) {
    int maxVal = v[0];                       // 先让第一个当擂主
    for (int i = 1; i < v.size(); i++) {     // 从第二个开始挑战
        if (v[i] > maxVal) {
            maxVal = v[i];
        }
    }
    return maxVal;
}
double averageOf(const vector<int>& v) {
    int sum = sumOf(v);                      // 可以直接调用你刚写的 sumOf
    return sum * 1.0 / v.size();             // ⚠️ 不能写 sum / v.size()
}

int main() {
    int n;
    cout << "请输入数字个数: ";
    cin >> n;

    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);              // 塞进 vector
    }

    cout << "和=" << sumOf(v) << endl;
    cout << "平均=" << averageOf(v) << endl;
    cout << "最大=" << maxOf(v) << endl;
    return 0;
}
