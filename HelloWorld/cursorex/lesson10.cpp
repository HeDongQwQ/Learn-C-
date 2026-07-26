#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Student{
public:
    string name;
    int score;
    void print(){
        cout<<name<<" "<<score<<endl;
    }
};
bool cmp(const Student& a,const Student& b){
    return a.score>b.score;
}
int main(){
    vector<Student> st;
    cout<<"请输入学生人数：";
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        Student s;
        cout<<"请输入学生姓名和分数：";
        cin>>s.name>>s.score;
        st.push_back(s);
    }
    cout<<"全部学生："<<endl;
    for(int i=0;i<st.size();i++){
        st[i].print();
    }
    sort(st.begin(),st.end(),cmp);
    cout<<"排序后："<<endl;
    for(int i=0;i<st.size();i++){
        st[i].print();
    }
    cout<<"请输入要查找的学生姓名：";
    string name;
    cin>>name;
    bool found=false;
    for(int i=0;i<st.size();i++){
        if(st[i].name==name){
            found=true;
            cout<<"找到了";
            st[i].print();
            break;
        }
    }
    if(!found){
        cout<<"没有找到"<<endl;
    }
    system("pause");
    return 0;
}
