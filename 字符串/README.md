## 4 字符串
(如遇公式显示问题，请关闭深色模式并使用科学上网)

计算机并不仅仅能够处理数学问题，还可以用来处理文字，比如写文章、处理代码、记录信息等等……如果需要将各种语句记录在计算机中，就要用到字符串或者字符数组。

字符串在程序设计中也有着很大的用处(如高精度运算等)

这里也是**节选一些题**

#### 4xa 常用函数

##### [P5015 [NOIP2018 普及组] 标题统计](https://www.luogu.com.cn/problem/P5015)

用到了ASCII码的知识

```cpp
#include <bits/stdc++.h>

using namespace std;

int main(){
    int length=0;
    char str[10];
    fgets(str, 9, stdin);
    int l=strlen(str);
    for (int i = 0; i<l; i++) {
        if(str[i]!=' '&&str[i]!='\n')
            length++;
    }
    printf("%d",length);
    return 0;
}
```

##### [P1308 [NOIP2011 普及组] 统计单词数](https://www.luogu.com.cn/problem/P1308)

用到了字符串的比较和strlen

```cpp
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
```

##### [P5734 【深基6.例6】文字处理软件](https://www.luogu.com.cn/problem/P5734)

这一题用到了字符串的很多函数，如：

- strcat连接字符串
- strncpy从原字符串中拷贝n个字符到目的字符串
- strcpy拷贝字符串
- strstr查找子串的第一次出现位置

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    scanf("%d",&n);
    char str[1000];
    scanf("%s",str);
    while (n--) {
        int cmd;
        int a,b;
        char dst[1000];
        scanf("%d",&cmd);
        switch (cmd) {
            case 1://cat
                scanf("%s",dst);
                strcat(str, dst);
                printf("%s\n",str);
                break;
            case 2:{
                scanf("%d%d",&a,&b);
                char tmp[1000]={0};
                strncpy(tmp, str+a, b);
                strcpy(str, tmp);
                printf("%s\n",str);
            }
                break;
            case 3:
                scanf("%d%s",&a,dst);
            {
                char tmpa[1000]={0},tmpb[1000]={0};
                strncpy(tmpa, str, a);
                strncpy(tmpb, str+a, strlen(str)-a);
                strcat(tmpa, dst);strcat(tmpa, tmpb);
                strcpy(str, tmpa);
            }
                printf("%s\n",str);
                break;
            case 4:
                scanf("%s",dst);
                char *p=strstr(str, dst);
                if(p==NULL) printf("-1\n");
                else{
                    printf("%d\n",p-str);
                }
                break;
        }
    }
    return 0;
}
```

#### 4xb KMP算法(简易版)
