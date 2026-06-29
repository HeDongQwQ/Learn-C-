#include <iostream>
using namespace std;

int main() {
    int a;
    cout << "选择? for(1)orwhile(2)" << endl;
    cin >> a;
    switch (a) {
        case 1: {
            cout << "for循环:" << endl;
            for (int j = 1; j <= 10; j++) {
                cout << "for:" << j << "  ";
            }
            break;
        }
        case 2: {
            cout << "while循环:" << endl;
            int i;
            cin >> i;
            while (i <= 10) {
                cout << "while:" << i << "  ";
                i++;
            }
            break;
        }
        default: {
            cout << "输入错误" << endl;
            break;
        }
    }
    return 0;
}