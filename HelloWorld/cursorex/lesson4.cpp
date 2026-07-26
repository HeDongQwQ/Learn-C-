#include <iostream>
using namespace std;
int main(){
    int a[5];
    cout<<"请输入5个整数"<<endl;
    for(int i=0;i<5;i++){
        cin>>a[i];
    }
    int max=a[0];
    int min=a[0];
    for(int i=0;i<5;i++){
        
        cout<<a[i]<<" ";
        if(a[i]>max){
            max=a[i];
        }
        if(a[i]<min){
            min=a[i];
        }
    }
    cout<<"最大值为"<<max<<endl;
    cout<<"最小值为"<<min<<endl;
  return 0;
}