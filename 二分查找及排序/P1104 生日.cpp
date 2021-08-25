#include <bits/stdc++.h>

using namespace std;
struct birday {
    string name;
    int y,m,d,code;
}bir[101];

bool cmp(const birday &h1,const birday &h2){//手写比较函数
    if(h1.y!=h2.y) return h1.y<h2.y;
    if(h1.m!=h2.m) return h1.m<h2.m;
    if(h1.d!=h2.d) return h1.d<h2.d;
    return h1.code>h2.code;
}

int main(){
    int n;
    scanf("%d",&n);
    for (int i =1; i<=n; i++){
        cin>>bir[i].name>>bir[i].y>>bir[i].m>>bir[i].d;
        bir[i].code=i;
    }
    sort(bir+1, bir+1+n, cmp);
    for (int i = 1; i<=n; i++) {
        cout<<bir[i].name<<endl;
    }
    return 0;
}
