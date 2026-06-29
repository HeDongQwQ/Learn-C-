#include <iostream>
using namespace std;
void sum(double a, double b) {
    cout<<a<<" + "<<b<<" = "<<a+b<<endl;
}
void sub(double a, double b) {
    cout<<a<<" - "<<b<<" = "<<a-b<<endl;
}
void mul(double a, double b) {
    cout<<a<<" * "<<b<<" = "<<a*b<<endl;
}
void chu(double a, double b) {
    if (b != 0) {
        cout<<a<<" / "<<b<<" = "<<a/b<<endl;
    } else {
        cout << "除数不能为0" << endl;
    }
}
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
                sum(a, b);
                break;
            case '-':
                sub(a, b);
                break;
            case '*':
                mul(a, b);
                break;
            case '/':
                chu(a, b);
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