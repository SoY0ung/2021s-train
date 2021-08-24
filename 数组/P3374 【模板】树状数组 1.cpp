#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5+7;
int n,t[MAXN];

int lowbit(int x){
    return x&-x;
}

void update(int pos,int val){
    while (pos<=n) {
        t[pos]+=val;
        pos+=lowbit(pos);
    }
}

int sum(int x){
    int ans=0;
    while (x) {
        ans+=t[x];
        x-=lowbit(x);
    }
    return ans;
}

int main(){
    int m;
    scanf("%d%d",&n,&m);
    for (int i = 1; i<=n; i++) {
        int v;
        scanf("%d",&v);
        update(i, v);
    }
    for (int i = 1; i<=m; i++) {
        int cmd,x,y;
        scanf("%d%d%d",&cmd,&x,&y);
        if(cmd==1){
            update(x, y);
        }else {
            printf("%d\n",sum(y)-sum(x-1));
        }
    }
    return 0;
}
