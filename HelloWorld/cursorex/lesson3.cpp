#include <iostream>
using namespace std;
int main(){
  int n=0;
  int j=0;
  cout<<"请输入一个整数"<<endl;
  cin>>n;
  for(int i=1;i<=n;i++){
    if(i%2==0){
      cout<<"偶数为"<<i<<" ";
    }
    j=j+i;
  }
  cout<<"1到n的和为"<<j<<endl;
  return 0;
}