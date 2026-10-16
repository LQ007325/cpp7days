// ============================================================
// day4 p5  ——  排序与及格率
// ============================================================
// 读 5 个分数，升序输出，并算出及格率（>=60 及格）。
// 
// 样例: 输入 88 45 92 60 73
//   排序后: 45 60 73 88 92
//   及格率: 80%
// 
// 及格率要用小数算: 100.0 * 及格人数 / 总人数
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
   cout<<"请输入数字个数"<<endl;
    int n;
    cin>>n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);            
    }
    sort(v.begin(),v.end());
    cout<<"排序后:";
    for(int x:v){
        cout<<x<<" ";
    }
    cout<<endl;
    int passCount = count_if(v.begin(), v.end(), [](int x) { return x >= 60; });
    cout << "及格率: " << (100.0 * passCount / v.size()) << "%" << endl;


        return 0;
}
