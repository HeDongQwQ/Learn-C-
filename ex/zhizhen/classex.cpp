#include <iostream>
using namespace std;
void reset(int* p,int* q) {
    int temp=*p;
    *p=*q;
    *q=temp;
}
int main() {
    int a=10;
    int b=20;
    cout<<"a的值"<<a<<endl;
    cout<<"b的值"<<b<<endl;
    cout<<"交换后"<<endl;
    reset(&a,&b);
    cout<<"a的值"<<a<<endl;
    cout<<"b的值"<<b<<endl;
    return 0;
}
