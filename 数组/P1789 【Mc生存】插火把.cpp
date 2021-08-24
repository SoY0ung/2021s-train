#include <bits/stdc++.h>
using namespace std;

bool vis[110][110];
int n;

void tjudge(int x,int y){
    vis[x][y]=1;
    for (int i = 1; i<=5; i++) {
        int p=i-3;//x -2 -1 0 1 2
        int num,s;
        if(abs(p)==2) num=1,s=0;
        else if(abs(p)==1) num=3,s=-1;
        else num=5,s=-2;
        int nowx=x+p,nowy=y+s;
        for (int j = 0; j<num; j++) {
            if(nowx>=1&&nowx<=n&&nowy+j>=1&&nowy+j<=n) vis[nowx][nowy+j]=1;
        }
    }
}

void sjudge(int x,int y){
    vis[x][y]=1;
    for (int i = 1; i<=5; i++) {
        int p=i-3;
        int num=5,s=-2;
        int nowx=x+p,nowy=y+s;
        for (int j = 0; j<num; j++) {
            if(nowx>=1&&nowx<=n&&nowy+j>=1&&nowy+j<=n) vis[nowx][nowy+j]=1;
        }
    }
}

int main(){
    int m,k;//n*n m--torch k--stone
    int ans=0;
    scanf("%d%d%d",&n,&m,&k);
    int x,y;
    for (int i = 1; i<=m; i++) {
        scanf("%d%d",&x,&y);
        tjudge(x, y);
    }
    for (int i = 1; i<=k; i++) {
        scanf("%d%d",&x,&y);
        sjudge(x, y);
    }
    for (int i = 1; i<=n; i++) {
        for (int j = 1; j<=n; j++) {
            if(!vis[i][j]) ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
