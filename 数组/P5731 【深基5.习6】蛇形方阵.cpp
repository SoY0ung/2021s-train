#include <bits/stdc++.h>
using namespace std;

int a[10][10];
int i=1,j=1,flag=1,n,cnt=2;

void heng(){
    //j only
    if (flag<=2) {
        //move right j++
        j++;
        while (1) {
            if (j==n||a[i][j+1]!=0) {
                a[i][j]=cnt;
                cnt++;
                flag++;
                break;
            }else{
                a[i][j]=cnt;
                cnt++;
                j++;
            }
        }
        if (flag>4) {
            flag=1;
        }
    }else {
        //move left j--
        j--;
        while (1) {
            if (j==1||a[i][j-1]!=0) {
                a[i][j]=cnt;
                cnt++;
                flag++;
                break;
            }else{
                a[i][j]=cnt;
                cnt++;
                j--;
            }
        }
        if (flag>4) {
            flag=1;
        }
    }
    
}
void shu(){
    //i only
    if (flag<=2) {
        //move down i++
        i++;
        while (1) {
            if (i==n||a[i+1][j]!=0) {
                a[i][j]=cnt;
                cnt++;
                flag++;
                break;
            }else{
                a[i][j]=cnt;
                cnt++;
                i++;
            }
        }
        if (flag>4) {
            flag=1;
        }
    }else{
        //move up i--
        i--;
        while (1) {
            if (i==1||a[i-1][j]!=0) {
                a[i][j]=cnt;
                cnt++;
                flag++;
                break;
            }else{
                a[i][j]=cnt;
                cnt++;
                i--;
            }
        }
        if (flag>4) {
            flag=1;
        }
    }
}

int main(){
    scanf("%d",&n);
    int mx=n*n;
    a[1][1]=1;
    while (1) {
        heng();
        if (cnt>mx)
            break;
        shu();
        if (cnt>mx)
            break;
    }
    for (i=1; i<=n; i++) {
        for (j=1; j<=n; j++) {
            printf("%3d",a[i][j]);
        }
        putchar('\n');
    }
    return 0;
}
P5731 【深基5.习6】蛇形方阵
