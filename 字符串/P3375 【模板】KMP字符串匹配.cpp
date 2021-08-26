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
