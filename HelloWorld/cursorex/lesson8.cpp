#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    cout<<"请输入一个数：";
    int n;
    int sum=0;
    cin>>n;
    vector<int> v;
    cout<<"请输入四个数：";
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        v.push_back(x);
    }
    cout<<"数组为：";
    for(int i=0;i<n;i++){
        cout<<v[i]<<" ";
    }
    for(int i=0;i<n;i++){
        sum=sum+v[i];
    }
    cout<<"sum "<<sum<<endl;
    int max=v[0];
    for(int i=0;i<n;i++){
        if(v[i]>max){
            max=v[i];
        }
    }
    cout<<"max: "<<max<<endl;
    
    string word;
    cout<<"请输入一个单词：";
    cin>>word;
    cout<<"单词为："<<word<<endl;
    cout<<"长度为："<<word.size()<<endl;
    cout<<"第一个元素为："<<word[0]<<endl;
    cout<<"最后一个元素为："<<word[word.size()-1]<<endl;
    system("pause");
    return 0;
}