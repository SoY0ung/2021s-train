#include <bits/stdc++.h>
using namespace std;

bool vis[12];
long long f[12];
int ans[12];

void dofact(int n){ //预处理阶乘和树状数组
    f[0]=1;f[1]=1;
    for (int i = 2; i<=n; i++) {
        f[i]=(f[i-1]*i);
    }
}
void solve(int n,int k){    //已知一个 1~n 的排列 A 的排名为 k，求 A
    memset(vis,0,sizeof(vis)); k--;    //有 k-1 种排列比 A 的字典序小
    for(int i=1;i<=n;i++){
        int cnt=k/f[n-i];    //有cnt个数比 A 的第i位小 (取(n-i)!的商)
        for(int j=1;j<=n;j++)//循环遍历出第cnt个未出现过的数
            if(!vis[j]){
                if(!cnt){ans[i]=j;vis[j]=1;break;}//就是该数，把它标记为1
                cnt--;
            }
        k%=f[n-i];    //还剩下几种排列比 A 的字典序小(取(n-i)!的余数)
    }
}

int main(){
    int n,k;
    cout<<"输入序列长度n和排名k(n最大为11)"<<endl;
    cin>>n>>k;
    dofact(n);
    solve(n, k);
    for (int i = 1; i<=n; i++) {
        printf("%d ",ans[i]);
    }
    return 0;
}
