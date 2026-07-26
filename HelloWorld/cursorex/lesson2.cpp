#include <iostream>
using namespace std;
int main(){
    int n=0;
    cout<<"请输入一个整数"<<endl;
    cin>>n;
    if(n>0){
        cout<<"n是正数"<<endl;
    }else if(n<0){
        cout<<"n是负数"<<endl;
    }else{
        cout<<"n是0"<<endl;
    }
    if(n%2==0){
        cout<<"n是偶数"<<endl;
    }else{
        cout<<"n是奇数"<<endl;
    }
    return 0;
}