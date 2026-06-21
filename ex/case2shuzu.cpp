#include <iostream>
#include <string>
using namespace std;
int main(){
    string a = "adminapperandas";
    int count = 0;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == 'a') {
            count++;
        }
    }

    cout << "字符串中 a 的个数是：" << count << endl;
    return 0;
}
