#include <iostream>
#include "fangfa2sum.h"
using namespace std;
int main() {
    double a, b;
    char c;
    while (true) {
        cout<<"请输入第一个数："<<endl;
        cin>>a;
        cout<<"请输入运算符: +, -, *, /"<<endl;
        cin>>c;
        cout<<"请输入第二个数："<<endl;
        cin>>b;
        switch (c) {
            case '+':
                cout<<a<<" + "<<b<<" = "<<sum(a, b)<<endl;
                break;
            case '-':
                cout<<a<<" - "<<b<<" = "<<sub(a, b)<<endl;
                break;
            case '*':
                cout<<a<<" * "<<b<<" = "<<mul(a, b)<<endl;
                break;
            case '/':
                cout<<a<<" / "<<b<<" = "<<chu(a, b)<<endl;
                break;
            default:
                cout<<"输入错误"<<endl;
                break;
        }
        cout<<"是否继续？(y/n)"<<endl;
        cin>>c;
        if (c == 'n') {
            break;
        }
        else {
            continue;
        }
    }
    return 0;
}