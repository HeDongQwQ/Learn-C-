#include <iostream>
using namespace std;
int main() {
    int num=10;
    int* p=&num;
    cout<<"num原来的值"<<num<<endl;
    cout<<"num的地址"<<&num<<endl;
    cout<<"p的地址"<<p<<endl;
    return 0;
}