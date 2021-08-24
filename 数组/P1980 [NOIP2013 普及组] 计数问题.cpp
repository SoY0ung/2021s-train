#include <stdio.h>

int main(){
    int num[10]={0};
    int n,x;
    scanf("%d %d",&n,&x);
    for (int i = 1; i<=n; i++) {
        int j = i,k;
        while ((k=j%10) != j) {
            num[k]++;
            j = j / 10;
        }
        num[j]++;
    }
    printf("%d",num[x]);
    return 0;
}
 
