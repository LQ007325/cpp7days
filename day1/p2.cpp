// ============================================================
// day1 p2  ——  四则运算
// ============================================================
// 读两个整数，输出和、差、积、商、余数。
// 
// 样例: 输入 7 2
//   和=9  差=5  积=14  商=3  余数=1
// 
// 注意: 整数除法会截断，7/2 得 3 不是 3.5
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p2.cpp -o p2.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int a,b;
    cout <<"请输入两个数字" <<endl;
    cin >> a >> b;
    int he,cha,ji,shang,yu;
    he = a+b;
    cha= a-b;
    ji=a*b;
    shang=a/b;
    yu=a%b;
    cout << "和为" << he<<endl;
    cout << "差为" << cha<<endl;
    cout << "乘积为" << ji<<endl;
    cout << "商为" << shang<<endl;
    cout << "余数为" << yu<<endl;




    // TODO: 开始写
    return 0;
}
