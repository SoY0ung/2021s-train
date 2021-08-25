#include <bits/stdc++.h>
using namespace std;

char src[15];
char artic[1000010];
char ch;

int main(){
    int cnt=0,srt=0,now=0,n=0;
    while ((ch=getchar())!='\n') {
        if(ch>='A'&&ch<='Z') ch+=' ';
        src[cnt++]=ch;
    }
    src[cnt]='\0';
    cnt=0;
    int len=strlen(src);
    while ((ch=getchar())!=EOF&&ch!='\n') {
        if(ch>='A'&&ch<='Z') ch+=' ';
        if(ch==' ') {
            if(now==len) {
                if(cnt==0) {srt=n-len;}
                cnt++;
            }
            now=0; n++; continue;
        }
        if(now>=len) now=-1;
        if(now!=-1&&ch==src[now]){
            now++;
        }else now=-1;
        n++;
    }
    if(now==len) {
        if(cnt==0) {srt=n-len;}
        cnt++;
    }
    if(cnt==0) printf("-1");
    else printf("%d %d",cnt,srt);
    return 0;
}
