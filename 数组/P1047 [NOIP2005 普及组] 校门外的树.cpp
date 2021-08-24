#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int arr[MAXN];
int brr[MAXN];

int main(){
    int n;
    cin>>n;
    for (int i = 1; i<=n; i++) {
        scanf("%d",arr+i);
        for (int j = 1; j<i; j++) {
            if(arr[j]<arr[i]) brr[i]++;
        }
    }
    for(int i = 1;i<=n;i++){
        printf("%d ",brr[i]);
    }
    return 0;
}
