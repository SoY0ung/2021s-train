#include <bits/stdc++.h>
using namespace std;

int NUM[1001];
int ran[101];

int main(){
    int N;
    scanf("%d",&N);
    for (int i = 0; i<N; i++) {
        scanf("%d",ran+i);
        if(NUM[ran[i]]==0)NUM[ran[i]]=1;
        else N--,i--;
    }
    printf("%d\n",N);
    sort(ran, ran+N);
    for (int i = 0; i<N; i++) {
        printf("%d",ran[i]);
        if (i!=(N-1)) {
            printf(" ");
        }
    }
    return 0;
}
