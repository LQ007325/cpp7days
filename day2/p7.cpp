// ============================================================
// day2 p7  ——  奇偶统计
// ============================================================
// 先读个数 n，再读 n 个整数，统计偶数和奇数各多少个。
// 
// 样例: 输入 5 换行 1 2 3 4 5  →  偶数=2 奇数=3
// 
// 坑点: ① n 必须 cin 读进来  ② 两个计数器都要初始化成 0
//       ③ cin 放在循环里面    ④ 输出放在循环外面
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
//           或终端:  g++ -std=c++17 -Wall p7.cpp -o p7.exe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    cout<<"输入："<<endl;
    int n,x;
    cin>>n;
    int jishu=0,oushu=0;
    for(int i=1;i<=n;i++){
        cin>>x;
        if(x%2==0){
            oushu++;
        }else{
            jishu++;
        }
    }
    cout<<"偶数="<<oushu<<"奇数="<<jishu<<endl;
    

    
    return 0;
}
