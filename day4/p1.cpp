// ============================================================
// day4 p1  ——  vector 基本统计
// ============================================================
// 读 n 和 n 个数，输出和、平均、最大、最小。
// 
// 样例: 输入 5 换行 3 1 4 1 5  →  和=14 平均=2.8 最大=5 最小=1
// 
// 提示: accumulate(v.begin(),v.end(),0) / *max_element(...) / *min_element(...)
//      需要 #include <numeric>（accumulate 在里面）
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p1.cpp -o p1.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#include <numeric>

int main() {
    cout<<"请输入数字个数"<<endl;
    int n;
    cin>>n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);            
    }
    cout << "和="   << accumulate(v.begin(), v.end(), 0) << endl;
    cout << "平均=" << accumulate(v.begin(), v.end(), 0.0) / v.size() << endl;
    cout << "最大=" << *max_element(v.begin(), v.end()) << endl;
    cout << "最小=" << *min_element(v.begin(), v.end()) << endl;
    return 0;
}
