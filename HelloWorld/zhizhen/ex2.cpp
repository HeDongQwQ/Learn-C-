#include <iostream>
using namespace std;
void reset(int *p) {
    *p=100;
}
int main() {
    int num=10;
    reset(&num);
    cout<<"num的值"<<num<<endl;
    return 0;
}