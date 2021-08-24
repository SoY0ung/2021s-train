#include <bits/stdc++.h>
using namespace std;

int main(){
    double x1,x2,x3,y1,y2,y3;
    printf("依次输入P1P2P3的横纵坐标\n");
    scanf("%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3);
    double flag;
    flag=(x2-x1)*(y3-y2)-(y2-y1)*(x3-x2);//叉乘在z轴上的分量
    if(flag>0){
        printf("P1P2P3方向为逆时针\n");
    }else if(flag<0){
        printf("P1P2P3方向为顺时针\n");
    }else printf("P1P2P3共线\n");
    return 0;
}
