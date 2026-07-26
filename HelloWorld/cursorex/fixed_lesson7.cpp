#include <iostream>
#include <string>
using namespace std;

// 一个 Student 对象 = 一个学生（姓名 + 分数）
class Student {
public:
    string name;
    int score;

    void print() {
        cout << name << " " << score << endl;
    }
};

int main() {
    Student s1, s2;  // 两个学生 → 两个对象

    cout << "请输入学生1姓名和分数：" << endl;
    cin >> s1.name >> s1.score;

    cout << "请输入学生2姓名和分数：" << endl;
    cin >> s2.name >> s2.score;

    s1.print();
    s2.print();

    if (s1.score > s2.score) {
        cout << "更高分：" << s1.name << endl;
    } else if (s2.score > s1.score) {
        cout << "更高分：" << s2.name << endl;
    } else {
        cout << "分数相同" << endl;
    }

    return 0;
}
