#include <iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
class Student{
public:
    string name;
    int score;
    void print(){
        cout<<name<<" "<<score<<endl;
    }
};
int main(){
    vector<Student> st;
    cout<<"请输入人数"<<endl;
    int n;
    cin>>n;
    cout<<"请输入姓名和分数"<<endl;
    for(int i=0;i<n;i++){
        Student s;
        cin>>s.name>>s.score;
        st.push_back(s);
    }
    ofstream fout("Student.txt");
    for(int i=0;i<st.size();i++){
        fout<<st[i].name<<" "<<st[i].score<<endl;
    }
    fout.close();
    cout<<"已保存到Student.txt"<<endl;
    
    ifstream fin("Student.txt");
    for(int i=0;i<st.size();i++){
        fin>>st[i].name>>st[i].score;
    }
    vector<Student> st2;
    for(int i=0;i<st.size();i++){
        st2.push_back(st[i]);
    }
    cout<<"从文件读回："<<endl;
    for(int i=0;i<st2.size();i++){
        st2[i].print();
    }
    system("pause");
    return 0;
}