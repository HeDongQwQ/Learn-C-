#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> v;
    cout<<"请输入一个数：";
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        v.push_back(x);
    }
    cout<<"数组为：";
    for(int i=0;i<n;i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    cout<<"排序后";
    sort(v.begin(),v.end());
    for(int i=0;i<n;i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    cout<<"请输入要查找的数:"<<endl;
    int x;
    cin>>x;
    bool found=false;
    for(int i=0;i<n;i++){
        if(v[i]==x){
            found=true;
            break;
        }
    }
    if(found){
        cout<<"找到了"<<endl;
    }else{
        cout<<"没有找到"<<endl;
    }
    system("pause");
    return 0;
}