#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int arr[MAXN];

int main(){
    //当然，也可以用栈(stack)做
    int num,cnt=0;
    while (1) {
        scanf("%d",&num);
        if(num==0) break;
        arr[++cnt]=num;
    }
    for (int i = cnt; i>=1; i--) {
        printf("%d ",arr[i]);
    }
    return 0;
}
