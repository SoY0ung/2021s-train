#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a,long long b){
    if(a<b) swap(a, b);//保证a不小于b
    return b==0?a:gcd(b,a%b);//b==0代表余数为0，即找到了最大公约数
}

int main(){
    int a,b;
    cout<<"输入你要求gcd的两个数"<<endl;
    cin>>a>>b;
    cout<<gcd(a, b);
    return 0;
}
