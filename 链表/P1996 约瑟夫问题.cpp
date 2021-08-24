#include <bits/stdc++.h>
using namespace std;

vector<int> vec;

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    int len=n,now=m;
    for (int i = 1; i<=n; i++)
        vec.push_back(i);
    while (!vec.empty()) {
        now%=len;
        if(now==0) now=len;
        printf("%d ",*(vec.begin()+now-1));
        len--;
        vec.erase(vec.begin()+now-1);
        now+=(m-1);
    }
    return 0;
}
