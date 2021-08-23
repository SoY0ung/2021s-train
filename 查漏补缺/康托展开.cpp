#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+3,p=998244353;
int arr[MAXN],n;

long long fact[MAXN];
int t[MAXN];//树状数组

//树状数组三件套
int lowbit(int x){
    return x&-x;
}
//求[1,now]的和
int getSum(int now){
    int sum=0;
    while(now){
        sum+=t[now];now-=lowbit(now);
    }
    return sum;
}
//单点i修改
void update(int i,int val) {
    while (i<=n){
        t[i]+=val;i+=lowbit(i);
    }
}

void dofact(int n){ //预处理阶乘和树状数组
    fact[0]=1;fact[1]=1;
    update(1, 1);
    for (int i = 2; i<=n; i++) {
        fact[i]=(fact[i-1]*i)%p;
        update(i, 1);//将树状数组初始化为1
    }
}

int main(){
    cin>>n;
    dofact(n);
    long long ans=0;
    for (int i = 1; i<=n; i++){
        scanf("%d",arr+i);
        ans=(ans+((getSum(arr[i]-1))*fact[n-i]%p))%p; //这里得到树状数组[1,arr[i]-1]的和
        update(arr[i], -1);//将树状数组还原为0(也就是-1)
    }
    cout<<ans+1;
    return 0;
}
