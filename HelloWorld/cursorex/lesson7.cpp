#include <iostream>
using namespace std;
class Student{
public:
    string name[2];
    int score[2];

    void print(Student stu){
        int max=stu.score[0];
        for(int i=0;i<2;i++){
            cout<<"姓名："<<stu.name[i]<<endl;
            cout<<"分数："<<stu.score[i]<<endl;
            if(stu.score[i]>max){
                max=stu.score[i];
            }
        }
        cout<<"最高分："<<max<<endl;
    }
};

int main(){
    Student stu;
    cout<<"请输入学生1姓名：";
    cin>>stu.name[0];
    cout<<"请输入学生1分数：";
    cin>>stu.score[0];
    cout<<"请输入学生2姓名：";
    cin>>stu.name[1];
    cout<<"请输入学生2分数：";
    cin>>stu.score[1];
    stu.print(stu);
    system("pause");
    return 0;
}