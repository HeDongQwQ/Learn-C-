#include <iostream>
using namespace std;
int main() {
    int a[5];
    cout << "请输入5个整数：" << endl;
    for (int i = 0; i < 5; i++) {
        cin >> a[i];
    }
    cout << "数组和是：" << endl;
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += a[i];
    }
    cout << sum << endl;
    cout<<"max"<<endl;
    int max = a[0];
    for (int i = 0; i < 5; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    cout << max << endl;
    cout<<"min"<<endl;
    int min = a[0];
    for (int i = 0; i < 5; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    cout << min << endl;
    return 0;
}