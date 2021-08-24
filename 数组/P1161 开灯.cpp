#include <stdio.h>

int light[2000000]={0};

int main(){
    int n,t,l,max=0;
    double a;
    scanf("%d",&n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %d",&a,&t);
        if (a*t>max) {
            max = a * t;
        }
        for (int t_i = 1; t_i <= t; t_i++) {
            l = a * t_i;
            light[l] = !light[l];
        }
    }
    for (int i = 1; i <= max; i++) {
        if (light[i] == 1) {
            printf("%d",i);
            break;
        }
    }
    return 0;
}
