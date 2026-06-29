#include <iostream>
using namespace std;
// 交换数组中下标i和j的元素（完全复用你之前的swap逻辑）
void swap_arr(int* arr, int i, int j) {
    int temp = arr[i];   // 等价于*(arr+i)，取第i个元素
    arr[i] = arr[j];     // 等价于*(arr+i) = *(arr+j)
    arr[j] = temp;       // 把临时存的第i个元素赋给第j个位置
}

// 打印数组（必须传长度，解决你之前的坑）
void print_arr(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " "; // 也可以用*(arr+i)，效果完全一样
    }
    cout << endl;
}


int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);

    cout << "交换前：";
    print_arr(arr, len);

    swap_arr(arr, 0, 4); // 交换第0个和第4个元素（1和5互换）
    swap_arr(arr, 1, 3); // 交换第1个和第3个元素（2和4互换）

    cout << "交换后：";
    print_arr(arr, len);
    return 0;
}