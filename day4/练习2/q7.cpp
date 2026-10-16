// ============================================================
// day4 加练 q7  ——  有没有重复字符   ⭐⭐
// ============================================================
// 输入:  abcdef   →  没有重复
// 输入:  hello    →  有重复（l 出现了 2 次）
// 输入:  aabbcc   →  有重复
// 输入:  Aa       →  你定（在注释里写明理由）
//
// 考什么: sort + unique 三连的妙用 —— 反过用来判断"有没有重复"
//
// 思路:
//   string t = s;                        // 复制一份，别破坏原串
//   sort(t.begin(), t.end());
//   auto it = unique(t.begin(), t.end());
//   // it 指向"新的有效结尾"
//   // 如果 it - t.begin() < s.size() → 有元素被挪走了 → 有重复
//
// ⚠️ 关键: 这次不要 erase！拿 unique 的返回值做判断
// ⚠️ 大小写: Aa 算不算重复？你自己定，注释里写清楚
//
// 编译运行: VS Code 里按 Ctrl+Shift+B
// ============================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

int main() {
    cout << "请输入字符串: ";
    string s;
    getline(cin, s);

    // TODO: 开始写


    return 0;
}