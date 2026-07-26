#include <iostream>
using namespace std;
int add(int a,int b){
    return a+b;
}
int findMax(int arr[], int len) {
    int max = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}
int main(){
    cout<<"请输入2个整数"<<endl;
    int a,b;
    cin>>a>>b;
    cout<<"两个整数的和为"<<add(a,b)<<endl;
    cout<<"请输入5个整数"<<endl;
    int arr[5];
    for(int i=0;i<5;i++){
        cin>>arr[i];
    }
    int len=sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<len;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<"最大值为"<<findMax(arr,len)<<endl;
    return 0;
}