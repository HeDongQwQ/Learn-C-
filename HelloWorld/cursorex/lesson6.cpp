#include <iostream>
using namespace std;
void swap(int& a,int& b){
    int temp=a;
    a=b;
    b=temp;
}
int main(){
    int x=10;
    int *p=&x;
    cout<<"x的值为"<<x<<endl;
    cout<<"x的地址为"<<&x<<endl;
    cout<<"p的值为"<<p<<endl;
    cout<<"*p的值为"<<*p<<endl;
    *p=99;
    cout<<"x的值为"<<x<<endl;
    cout<<"请输入两个整数"<<endl;
    int a,b;
    cin>>a>>b;
    swap(a,b);
    cout<<"a的值为"<<a<<endl;
    cout<<"b的值为"<<b<<endl;
    return 0;
}