// ============================================================
// day5 p4  ——  Book 管理
// ============================================================
// struct Book { string title, author; double price; bool borrowed; };
// 用 vector<Book> 存，读 n 本书，支持按作者搜索、输出未借出的书。
//
// 样例输入:
//   2
//   C++Primer Lippman 99.0 0
//   EffectiveC++ Meyers 59.0 1
//   Meyers
// 样例输出:
//   找到: EffectiveC++ / 59
//   未借出: C++Primer
//
// 提示:
//   - bool 用 cin >> 读：输入 0 是 false，输入 1 是 true
//   - "未借出" 判断写 !b.borrowed  （! 是逻辑非）
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

struct Book {
    string title;
 string author; 
    double price;
    bool borrowed;      // true 表示已借出
};

int main() {
    SetConsoleOutputCP(65001);

    int n;
    cin >> n;

    vector<Book> books;

    // TODO 1: 读入 n 本书
    for(int i=0;i<n;i++){
        Book s;
        cin>>s.title>>s.author>>s.price>>s.borrowed;
        books.push_back(s);
    }

    // TODO 2: 读入要查询的作者名 who，遍历输出 "找到: 书名 / 价格"
    string author;
    cin>>author;
    for (int i = 0; i < (int)books.size();i++) {
    if (books[i].author ==author){ 
        cout << "找到: " << books[i].title<<" / "<<books[i].price<<endl;                      
    }
}

    


    // TODO 3: 输出 "未借出: " 后面跟所有未借出的书名
cout << "未借出: ";
    for (int i = 0; i < (int)books.size(); i++) {
        if(!books[i].borrowed){
            cout<<books[i].title<<" ";
        
            
        }
    }
    cout << endl;


    return 0;
}
