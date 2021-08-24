#include <bits/stdc++.h>
using namespace std;

int n,k,arr[100003];

int judge(int x){
    int cnt=0;
    for (int i = 1; i<=n; i++) {
        cnt+=(arr[i]/x);
        if(cnt>=k) return 1;
    }
    return 0;
}

int main(){
    long long sum=0;
    scanf("%d%d",&n,&k);
    for (int i = 1; i<=n; i++) {
        scanf("%d",arr+i);
        sum+=arr[i];
    }
    if(sum<k) {printf("0"); return 0;}
    sort(arr+1, arr+1+n);
    int l=1,r=arr[n],mid;
    while (l<r-1) {	//经典二分操作
        mid=(l+r)/2;
        if(judge(mid)) l=mid;
        else r=mid-1;
    }
    printf("%d",l);
    return 0;
}
