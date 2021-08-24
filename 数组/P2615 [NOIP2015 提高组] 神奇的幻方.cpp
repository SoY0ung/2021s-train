#include <stdio.h>

int arr[40][40];

int main(){
    int N,a,b;
    scanf("%d",&N);
    a = 0;b = (N-1)/2;
start:arr[a][b]=1;
    for (int i = 2; i <= N*N; i++) {
        a--;b++;
        if (a < 0) {
            a += N;
        }
        if (b >= N) {
            b -= N;
        }
        if (arr[a][b] == 0) {
            arr[a][b]=i;
        } else {
            a+=2;b--;
            if (b < 0) {
                b += N;
            }
            if (a >= N) {
                a -= N;
            }
            arr[a][b]=i;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ",arr[i][j]);
        }
        putchar('\n');
    }
    return 0;
}
 
