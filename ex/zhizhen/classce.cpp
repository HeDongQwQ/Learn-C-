#include <iostream>
using namespace std;
int find_max(int* arr, int len) {
    int max = *arr;
    int* end = arr + len;
    for (int* p = arr; p < end; p++) {
        if (*p > max) {
            max = *p;
        }
    }
    return max;
}
int main(){
    int arr[5]={1,2,3,4,5};
    int len=sizeof(arr)/sizeof(arr[0]);
    int max=find_max(arr,len);
    cout<<"max="<<max<<endl;
    return 0;
}