#include <bits/stdc++.h>
using namespace std;

list<int> lst;
typedef list<int>::iterator Iter;
Iter pos[100005];

void judge(int n){
    lst.push_front(1);
    pos[1]=lst.begin();
    for (int i = 2; i<=n; i++) {
        int k,p;
        scanf("%d%d",&k,&p);
        if(p==0){//left
            pos[i]=lst.insert(pos[k], i);//insert()函数插入到迭代器的前面
        }else {//right
            pos[i]=lst.insert(next(pos[k]), i);
        }
    }
}

void judge2(int m){
    for (int i = 1; i<=m; i++) {
        int x;
        scanf("%d",&x);
        if(pos[x]!=lst.end()){
            lst.erase(pos[x]);
        }
        pos[x]=lst.end();
    }
}

int main(){
    int n;
    scanf("%d",&n);
    judge(n);
    int m;
    scanf("%d",&m);
    judge2(m);
    bool frt=true;
    for (auto i:lst) {
        if(!frt)  putchar(' ');
        frt=false;
        printf("%d",i);
    }
    printf("\n");
    return 0;
}
