#include <bits/stdc++.h>
using namespace std;
long long arr[1000001];

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i = 1; i<=n; i++) {
        scanf("%lld",arr+i);
    }
    for (int i = 1; i<=m; i++) {
        long long x,num;
        scanf("%lld",&x);
        num = lower_bound(arr+1, arr+1+n, x)-(arr+1);
        if(upper_bound(arr+1, arr+1+n, x)-(arr+1) - num==0)	//没有找到，即不存在这个数
            printf("-1 ");
        else printf("%lld ",num+1);
    }
    return 0;
}
