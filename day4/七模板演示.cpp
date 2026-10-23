 // ============================================================
//  Day4 七模板演示 —— 一次看完，不用答题
// ============================================================
//  跑法：VS Code 里打开这个文件，按 Ctrl+Shift+B
//
//  这个程序不需要你输入任何东西，直接跑，直接看输出。
//  七段互不干扰，每段前面有【模板 N】标记。
//
//  看到哪段不懂，就把那个数字告诉人家，人家单独讲。
//  想动手了，就改某一段里的数字，再跑一遍，看输出变不变。
//
//  ⚠️ 注意：变量名必须用英文（中文名 g++ 8.1.0 不认，会报
//     stray '\345' in program）。字符串里的中文没问题。
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>   // sort, max_element, min_element, count_if, find
#include <numeric>     // accumulate
#include <cmath>       // abs
#include <windows.h>   // SetConsoleOutputCP
using namespace std;

// ============================================================
// 【模板 1】把一堆数存进 vector
// ============================================================
void demo1() {
    cout << "=========== 【模板 1】存数进 vector ===========" << endl;

    // 模拟【从键盘读到了这几个数】（真实情况下是 cin >> x）
    int raw_data[] = {80, 90, 70, 100, 60};

    vector<int> v;                          // ① 先准备一个空盒子
    for (int i = 0; i < 5; i++) {
        v.push_back(raw_data[i]);           // ② 一个一个放进去
    }

    cout << "放了 " << v.size() << " 个进去" << endl;
    cout << "现在盒子里是: ";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    cout << "  [要点] push_back 就是往末尾塞一个" << endl;
    cout << endl;
}

// ============================================================
// 【模板 2】遍历 + 算平均（含 size() 的两个坑）
// ============================================================
void demo2() {
    cout << "=========== 【模板 2】遍历 + 算平均 ===========" << endl;

    vector<int> v = {80, 90, 70};

    // --- 坑 A 的现场：size() 是无符号数 ---
    cout << "  size() 减 1 是多少？ " << v.size() - 1 << "   <- 正常" << endl;
    cout << "  但如果 v 是空的，size()-1 = " << vector<int>().size() - 1 << endl;
    cout << "  ^ 这就是那个 18446744073709551615，别再拿它做循环条件" << endl;
    cout << endl;

    // --- 正确姿势：计数器用 int ---
    double sum = 0;
    for (int i = 0; i < (int)v.size(); i++) {   // (int) 转一下，后面才能放心比较
        sum += v[i];
    }
    cout << "  求和 = " << sum << endl;
    cout << "  平均 = " << sum / v.size() << endl;
    cout << endl;

    // --- 坑 B 的现场：空 vector 会算出 nan ---
    vector<int> empty_v;
    double sum2 = 0;
    double avg2 = sum2 / empty_v.size();          // 0 / 0
    cout << "  空 vector 的平均 = " << avg2 << "   <- nan（不是数字）" << endl;
    cout << "  它会安安静静算完，不报错，这才是最坑的" << endl;
    cout << "  修法：先判断 if (v.empty()) { 说没有数据; return; }" << endl;
    cout << endl;
}

// ============================================================
// 【模板 3】sort 的三种写法（Day5 的核心）
// ============================================================
void demo3() {
    cout << "=========== 【模板 3】sort 三种写法 ===========" << endl;

    vector<int> a = {5, 2, 9, 1, 7};
    cout << "  原始:       5 2 9 1 7" << endl;

    // ① 升序（默认）
    vector<int> b = a;
    sort(b.begin(), b.end());
    cout << "  ① 升序:     ";
    for (int x : b) cout << x << " ";
    cout << "   <- sort(v.begin(), v.end())" << endl;

    // ② 降序（用现成的 greater<int>()）
    vector<int> c = a;
    sort(c.begin(), c.end(), greater<int>());
    cout << "  ② 降序:     ";
    for (int x : c) cout << x << " ";
    cout << "   <- 加第三个参数 greater<int>()" << endl;

    // ③ 自定义规则：按绝对值从小到大
    vector<int> d = {5, -2, 9, -1, 7};
    sort(d.begin(), d.end(), [](int x, int y) {
        return abs(x) < abs(y);
    });
    cout << "  ③ 按绝对值: ";
    for (int x : d) cout << x << " ";
    cout << "   <- lambda 自己定规则" << endl;
    cout << endl;

    cout << "  lambda 怎么读：" << endl;
    cout << "     [](int x, int y) { return abs(x) < abs(y); }" << endl;
    cout << "      ^    ^      ^                    ^" << endl;
    cout << "      空   两个    返回 true 表示      比较什么" << endl;
    cout << "      []   参数    x 该排在 y 前面" << endl;
    cout << endl;
}

// ============================================================
// 【模板 4】找最大 / 最小（星号是重点）
// ============================================================
void demo4() {
    cout << "=========== 【模板 4】max_element / min_element ===========" << endl;

    vector<int> v = {80, 95, 70, 88};

    int mx = *max_element(v.begin(), v.end());
    int mn = *min_element(v.begin(), v.end());

    cout << "  数据: 80 95 70 88" << endl;
    cout << "  最大值 = " << mx << "   <- *max_element(...)" << endl;
    cout << "  最小值 = " << mn << "   <- *min_element(...)" << endl;
    cout << endl;

    cout << "  [要点] max_element 返回的是【位置】，加 * 才是【值】" << endl;
    cout << endl;

    // 想知道最大值在【第几个】
    int pos = max_element(v.begin(), v.end()) - v.begin();
    cout << "  最大值在第 " << pos << " 个（从 0 开始数）" << endl;
    cout << endl;
}

// ============================================================
// 【模板 5】求和 / 计数 / 查找
// ============================================================
void demo5() {
    cout << "=========== 【模板 5】accumulate / count_if / find ===========" << endl;

    vector<int> v = {80, 95, 70, 88, 60, 59};

    // ① 求和
    int total = accumulate(v.begin(), v.end(), 0);
    cout << "  ① 求和 = " << total << "   <- accumulate 第三个参数 0" << endl;

    // ② 算平均（注意用 0.0 而不是 0）
    double avg = accumulate(v.begin(), v.end(), 0.0) / v.size();
    cout << "  ② 平均 = " << avg << "   <- 第三个参数写 0.0 才是小数" << endl;

    // ③ 数一数有几个及格的
    int pass_count = count_if(v.begin(), v.end(), [](int x) {
        return x >= 60;
    });
    cout << "  ③ 及格人数 = " << pass_count << "   <- count_if + lambda" << endl;

    // ④ 找某个值在不在
    int target = 88;
    auto it = find(v.begin(), v.end(), target);
    if (it != v.end()) {
        cout << "  ④ " << target << " 找到了，在第 " << (it - v.begin()) << " 个" << endl;
    } else {
        cout << "  ④ " << target << " 没找到" << endl;
    }

    int missing = 999;
    auto it2 = find(v.begin(), v.end(), missing);
    cout << "  ⑤ 找 " << missing << "：";
    if (it2 == v.end()) cout << "没找到（it 等于 v.end() 就是没找到）" << endl;
    cout << endl;
}

// ============================================================
// 【模板 6】struct —— 把几个数据捆成一个东西
// ============================================================
struct Student {
    string name;    // 注意这个分号
    int score;      // 这个分号
};                  // 还有这个分号！三处都不能少

void demo6() {
    cout << "=========== 【模板 6】struct ===========" << endl;

    // 当成普通类型用
    Student a;
    a.name = "小明";
    a.score = 90;
    cout << "  一个学生: " << a.name << " " << a.score << endl;

    // 花括号一次性塞好
    Student b = {"小红", 95};
    cout << "  另一个:   " << b.name << " " << b.score << endl;

    // 配合 vector，这才是威力所在
    vector<Student> class_list;
    class_list.push_back({"小明", 90});
    class_list.push_back({"小红", 95});
    class_list.push_back({"小刚", 70});

    cout << "  全班三个人: ";
    for (int i = 0; i < (int)class_list.size(); i++) {
        cout << class_list[i].name << "(" << class_list[i].score << ") ";
    }
    cout << endl;

    // 按分数排序 —— Day5 就要写这个
    sort(class_list.begin(), class_list.end(),
         [](const Student& x, const Student& y) {
             return x.score > y.score;          // 分高的排前面
         });
    cout << "  按分数从高到低: ";
    for (auto& s : class_list) {
        cout << s.name << "(" << s.score << ") ";
    }
    cout << endl << endl;
}

// ============================================================
// 【模板 7】菜单循环骨架（Day5 主程序的骨架）
// ============================================================
void demo7() {
    cout << "=========== 【模板 7】菜单循环骨架 ===========" << endl;
    cout << "  这个模板正常需要你输数字，人家这里用模拟的方式演示：" << endl;
    cout << endl;

    // 模拟用户依次选了 1, 2, 9, 0
    int simulated_choices[] = {1, 2, 9, 0};

    for (int i = 0; i < 4; i++) {
        int choice = simulated_choices[i];

        cout << "  ----- 用户输入了 " << choice << " -----" << endl;
        cout << "  1. 添加   2. 显示   0. 退出" << endl;

        if (choice == 0) {
            cout << "  -> 选择 0，退出程序" << endl;
            break;                          // 跳出 while / for
        }

        switch (choice) {
            case 1:
                cout << "  -> 进入 [添加] 功能" << endl;
                break;                      // 这个 break 不能漏
            case 2:
                cout << "  -> 进入 [显示] 功能" << endl;
                break;
            default:
                cout << "  -> 没有这个选项（走的是 default）" << endl;
                break;
        }
        cout << endl;
    }

    cout << "  [要点]" << endl;
    cout << "    - while(true) 是一直转" << endl;
    cout << "    - break 是跳出循环" << endl;
    cout << "    - switch 里每个 case 后面必须 break，否则会穿透到下一个 case" << endl;
    cout << endl;
}

// ============================================================
int main() {
    SetConsoleOutputCP(65001);   // 让中文正常显示

    cout << "====================================================" << endl;
    cout << "        Day4 七模板演示 —— 全部跑一遍" << endl;
    cout << "====================================================" << endl;
    cout << endl;

    demo1();   // 【模板 1】存数进 vector
    demo2();   // 【模板 2】遍历 + 算平均
    demo3();   // 【模板 3】sort 三种写法
    demo4();   // 【模板 4】max_element 星号
    demo5();   // 【模板 5】accumulate / count_if / find
    demo6();   // 【模板 6】struct
    demo7();   // 【模板 7】菜单循环骨架

    cout << "====================================================" << endl;
    cout << "  全部演示完毕。看到哪段不懂，告诉人家数字。" << endl;
    cout << "  想动手了，就改某段的数字，再跑一遍。" << endl;
    cout << "====================================================" << endl;

    return 0;
}
