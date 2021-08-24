#include <bits/stdc++.h>
using namespace std;

int n,r,ans[22],aans[22],cnt=0,havepri[100000003],numpri=0;
bool vis[22],prime[100000003];
void isPrime();
void dfs(int dep){
    if(dep>r) {
        int tot=0;
        for (int i = 1; i<=r; i++)
            tot+=aans[ans[i]];
        if(!prime[tot]) cnt++;
        return;
    }
    for (int i = 1; i<=n; i++) {
        if(!vis[i]) {
            vis[i]=1;
            if(ans[dep-1]<i){
            // meet the conditions --> Search
                ans[dep]=i;
                dfs(dep+1);
            }
            vis[i]=0;
        }
    }
}

int main(){
    scanf("%d%d",&n,&r);
    for (int i = 1; i<=n; i++)
        scanf("%d",aans+i);
    isPrime();
    //take r elements from n elements in total
    dfs(1);
    printf("%d",cnt);
    return 0;
}

void isPrime(){
    prime[1]=1; prime[0]=1;
    for (int i = 2; i<=100000003; i++) {
        if(!prime[i]) havepri[++numpri]=i;
        for (int k = 1; k<=numpri&&havepri[k]*i<=100000001; k++) {
            prime[havepri[k]*i]=1;
            if(i%havepri[k]==0) break;
        }
    }
}
