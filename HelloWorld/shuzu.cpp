#include <iostream>
// #include <string>
using namespace std;
int main() {
    int a[5];
    int b[5];
    cout << "请输入5个整数：" << endl;
    for (int i = 0; i < 5; i++) {
        cin >> a[i];
    }
    //冒泡排序
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    // 将排序后的 a 复制到 b
    for (int i = 0; i < 5; i++) {
        b[i] = a[i];
    }
    cout << "排序后的数组是：" << endl;
    for (int i = 0; i < 5; i++) {
        cout << b[i] << " ";
    }
    // string a[5] = {"apple", "banana", "cherry", "date", "elderberry"};
    // for (int i = 0; i < 5; i++) {
    //     cout << a[i] << " ";
    // }
    return 0;
}