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

#### 4xb KMP算法

KMP算法用来高效匹配文本串(Text)中的模式串(Pattern)。

> **模式串匹配**，就是给定一个需要处理的文本串（理论上应该很长）和一个需要在文本串中搜索的模式串（理论上长度应该远小于文本串），查询在该文本串中，给出的模式串的出现有无、次数、位置等。

不同于暴力匹配，KMP的精髓在于，对于每次失配之后，都**不会从头重新开始**枚举，而是根据我已经得知的数据，从某个特定的位置开始匹配；而对于模式串的每一位，都有**唯一**的“特定变化位置”，这个在失配之后的特定变化位置可以帮助我们利用已有的数据不用从头匹配，从而节约时间

而这个位置就是我们要求的最长公共前后缀长度(一般叫做prefix或next数组)

实现在代码里有注释，这里就不写了，可以参考[洛谷博客](https://www.luogu.com.cn/blog/yueying/solution-p3375)或[B站视频(AV16828557)](https://www.bilibili.com/video/av16828557)

##### [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)

附上这题的AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+7;
char T[MAXN],P[MAXN];

void run_prefix(char *pattern, int *prefix, int n){
//pattern --> 模式串   prefix --> 前缀表
//这里设prefix和pattern的第一个下标都从0开始
/*
 例：n=9;
    index    0   1   2   3   4   5   6   7   8
    pattren  A   B   A   B   C   A   B   A   A
    prefix   0   0   1   2   0   1   2   3   1
 */
    prefix[0]=0;    //第一个子串没有【真】前缀和【真】后缀
    int len=0,i=1;  //len表示当前最大连续前后缀长度，i从[1,n)遍历
    while (i<n) {
    //分两个情况
        //(1)可直接递推，即下一个字母是原前缀的下一个字母，此时len+1，继续向后递推(i++)
        if(pattern[i]==pattern[len])
            prefix[i++]=++len;
        else {
        //(2)需要回溯，这时需要回溯到当前len的上一个最长前后缀子串中，再继续向后用(1)查找
        //注意，避免数组越界，len应该大于0，当len=0时，直接将当前i的prefix设置为len(即0)即可，再继续递推
            if(len>0){
                len=prefix[len-1];//向前一位回溯
            }else {
                prefix[i++]=len;//继续递推
            }
        }
    }
}

void move_prefix(int *prefix, int n){
//把prefix数组移动成方便KMP算法的格式
/*
 例：n=9;
    index    0   1   2   3   4   5   6   7   8
    pattren  A   B   A   B   C   A   B   A   A
    prefix   0   0   1   2   0   1   2   3   1
移动后prefix -1   0   0   1   2   0   1   2   3
*/
    for (int i = n; i>0; i--) {
        prefix[i]=prefix[i-1];
    }
    prefix[0]=-1;
    
}

void prt_border(int n,int *prefix){
    for (int i = 1; i<=n; i++)
        printf("%d ",prefix[i]);
}

void kmp(char *text,char *pattern){
//text为需要搜索的文本，pattern为搜索内容串(模式串)
    int n=strlen(pattern),m=strlen(text);
    int *prefix;
    prefix=new int[n+1];    //动态开辟空间
    run_prefix(pattern, prefix, n);
    move_prefix(prefix, n);
//至此，预处理工作完成，接下来就是KMP算法了
    //我们规定文本串T长度为m，"指针"为i
    //模式串P长度为n，"指针"为j
    int i=0,j=0;
    while(i<m) {    //i从头到尾跑一次即可
        if(j == (n-1) && text[i]==pattern[j]){
        //找到记录的情况
            printf("%d\n",i-j+1);//i-j为下标
            j=prefix[j];    //继续向后搜索，注意j不需要后移
        }
        if(text[i]==pattern[j]){
            i++;j++;//匹配就继续往后匹配
        }else {
            //利用prefix数组移动P串的指针j，注意当prefix[j]=-1的时候，要整体前移
            j=prefix[j];
            if(j==-1) {i++;j++;}
        }
    }
    prt_border(n, prefix);
}

int main(){
    scanf("%s%s",T,P);
    kmp(T, P);
    return 0;
}
```


