// ========================================
// 本文件由助手根据 lesson12.cpp 修改生成
// 对照原文件可看差异；请以本文件为准学习「正确写法」
// ========================================
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

class Student {
public:
    string name;
    int score;
    // [助手] 加 const，方便 showAll(const vector&) 调用
    void print() const {
        cout << name << " " << score << endl;
    }
};

void addStudent(vector<Student>& st) {
    Student s;
    cout << "请输入姓名和分数" << endl;
    cin >> s.name >> s.score;
    st.push_back(s);
}

void loadStudent(vector<Student>& st) {
    ifstream fin("Student.txt");
    if (!fin.is_open()) {
        cout << "文件打开失败！" << endl;
        return;
    }
    st.clear();
    cout << "正在加载学生信息..." << endl;
    Student s;
    int count = 0;
    while (fin >> s.name >> s.score) {
        st.push_back(s);
        cout << "第 " << ++count << " 条：";
        s.print();
    }
    fin.close();
    cout << "加载完成，共 " << st.size() << " 名学生" << endl;
}

// [助手] 新增：只显示内存，不读文件（原 lesson12 选项2误用了 loadStudent）
void showAll(const vector<Student>& st) {
    if (st.empty()) {
        cout << "当前没有学生" << endl;
        return;
    }
    for (int i = 0; i < st.size(); i++) {
        st[i].print();
    }
}

// [助手] 升序用 < ，降序用 >（原版曾把两个比较写反）
bool cmpAsc(const Student& a, const Student& b) {
    return a.score < b.score;
}
bool cmpDesc(const Student& a, const Student& b) {
    return a.score > b.score;
}

void sortStudent(vector<Student>& st, int a) {
    if (a == 1) {
        sort(st.begin(), st.end(), cmpAsc);
        for (int i = 0; i < st.size(); i++) {
            st[i].print();
        }
    } else if (a == 2) {
        sort(st.begin(), st.end(), cmpDesc);
        for (int i = 0; i < st.size(); i++) {
            st[i].print();
        }
    }
}

// [助手] 增加「没有找到」提示
void findStudent(vector<Student>& st, string name) {
    bool found = false;
    for (int i = 0; i < st.size(); i++) {
        if (st[i].name == name) {
            st[i].print();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "没有找到" << endl;
    }
}

void saveStudent(vector<Student>& st) {
    ofstream fout("Student.txt");
    for (int i = 0; i < st.size(); i++) {
        fout << st[i].name << " " << st[i].score << endl;
    }
    fout.close();
    cout << "已保存到Student.txt" << endl;
}

int main() {
    vector<Student> st;
    int a;
    do {
        // [助手] 菜单：2=显示，6=加载；选项3文字改为「按分数排序」
        cout << "请选择操作：1.添加学生 2.显示学生 3.按分数排序 4.按姓名查找 5.保存 6.加载 0.退出" << endl;
        cin >> a;
        if (a == 1) {
            addStudent(st);
        } else if (a == 2) {
            // [助手] 原版这里是 loadStudent(st)
            showAll(st);
        } else if (a == 3) {
            int way;
            cout << "请输入排序方式：1.按分数排序升序 2.按分数排序降序" << endl;
            cin >> way;
            sortStudent(st, way);
        } else if (a == 4) {
            string name;
            cout << "请输入姓名" << endl;
            cin >> name;
            findStudent(st, name);
        } else if (a == 5) {
            saveStudent(st);
        } else if (a == 6) {
            // [助手] 新增选项：从文件加载
            loadStudent(st);
        } else if (a == 0) {
            break;
        } else {
            cout << "无效操作" << endl;
        }
    } while (a != 0);
    system("pause");
    return 0;
}
