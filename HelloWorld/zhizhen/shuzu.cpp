#include <iostream>
using namespace std;

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    
    // 验证1：数组名和首元素地址完全相等
    cout << "arr的值（数组名）：" << arr << endl;
    cout << "&arr[0]的值：" << &arr[0] << endl; // 和上面输出完全一致
    
    // 验证2：解引用数组名就是首元素
    cout << "*arr的值：" << *arr << endl; // 输出1，等价于arr[0]
    
    // 验证3：指针偏移等价于数组下标
    cout << "*(arr+1)的值：" << *(arr+1) << endl; // 输出2，等价于arr[1]
    cout << "*(arr+3)的值：" << *(arr+3) << endl; // 输出4，等价于arr[3]
    
    return 0;
}