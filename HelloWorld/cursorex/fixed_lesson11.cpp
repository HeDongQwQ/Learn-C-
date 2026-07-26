#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Student {
public:
    string name;
    int score;
};

int main() {
    vector<Student> st;
    cout << "请输入人数" << endl;
    int n;
    cin >> n;

    cout << "请输入姓名和分数" << endl;
    for (int i = 0; i < n; i++) {
        Student s;                 // 先造一个临时学生
        cin >> s.name >> s.score;
        st.push_back(s);           // 再放进 vector（此时 st 才会变长）
    }

    ofstream fout("students.txt");
    if (!fout) {
        cout << "打开文件失败" << endl;
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fout << st[i].name << " " << st[i].score << endl;
    }
    fout.close();
    cout << "已保存到 students.txt" << endl;

    // 从文件读回
    ifstream fin("students.txt");
    if (!fin) {
        cout << "打开文件失败" << endl;
        return 1;
    }
    vector<Student> loaded;
    Student s;
    while (fin >> s.name >> s.score) {
        loaded.push_back(s);
    }
    fin.close();

    cout << "从文件读回：" << endl;
    for (int i = 0; i < loaded.size(); i++) {
        cout << loaded[i].name << " " << loaded[i].score << endl;
    }
    return 0;
}
