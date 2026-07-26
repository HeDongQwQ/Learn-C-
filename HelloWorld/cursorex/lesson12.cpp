#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
class Student{
public:
    string name;
    int score;
    void print(){
        cout<<name<<" "<<score<<endl;
    }
};
void addStudent(vector<Student> &st){
    
    Student s;
    cout<<"请输入姓名和分数"<<endl;
    cin>>s.name>>s.score;
    st.push_back(s);
    
}
void loadStudent(vector<Student> &st){
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
bool cmpAsc(const Student& a,const Student& b){
    return a.score<b.score;
}
bool cmpDesc(const Student& a,const Student& b){
    return a.score>b.score;
}
void sortStudent(vector<Student> &st,int a){
    
    if(a==1){
        sort(st.begin(),st.end(),cmpAsc);
        for(int i=0;i<st.size();i++){
            st[i].print();
        }
    }else if(a==2){
        sort(st.begin(), st.end(), cmpDesc);
        for(int i=0;i<st.size();i++){
            st[i].print();
        }
    }  
} 
void findStudent(vector<Student> &st,string name){
    for(int i=0;i<st.size();i++){
        if(st[i].name==name){
            st[i].print();
        }
    }
}
void saveStudent(vector<Student> &st){
    ofstream fout("Student.txt");
    for(int i=0;i<st.size();i++){
        fout<<st[i].name<<" "<<st[i].score<<endl;
    }
    fout.close();
    cout<<"已保存到Student.txt"<<endl;
}
int main(){
    vector<Student> st;
    int a;
    do{
        cout<<"请选择操作：1.添加学生 2.显示学生 3.按分数排序降序 4.按姓名查找 5.保存 0.退出"<<endl;
        cin>>a;
        if(a==1){
            addStudent(st);
        }else if(a==2){
            loadStudent(st);
        }else if(a==3){
            int way;
            cout<<"请输入排序方式：1.按分数排序升序 2.按分数排序降序"<<endl;
            cin>>way;
            sortStudent(st,way);
        }else if(a==4){
            string name;
            cout<<"请输入姓名"<<endl;
            cin>>name;
            findStudent(st,name);
        }else if(a==5){
            saveStudent(st);
        }else if(a==0){
            break;
        }else{
            cout<<"无效操作"<<endl;
        }
    } 
    while(a!=0);
    system("pause");
    return 0;
}
