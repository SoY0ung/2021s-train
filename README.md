# 2021暑假自学报告

(如遇公式显示问题，请关闭深色模式或科学上网)

## 0 查漏补缺

#### 0xa 欧几里得算法求最大公约数

>  辗转相除法， 又名欧几里得算法，是求最大公约数的一种方法。
>
>  它的具体做法是：用**较大**数除以**较小**数，再用出现的余数（第一余数）去除除数，再用出现的余数（第二余数）去除第一余数，如此反复，直到最后余数是0为止。如果是求两个数的最大公约数，那么最后的**除数**就是这两个数的最大公约数。
>
>  用公式表达就是：
>
>  当![](https://latex.codecogs.com/svg.image?a=q*b&plus;r),即 ![](https://latex.codecogs.com/svg.latex?a\div{b}=q\cdots{r}),有
>
>  ![](https://latex.codecogs.com/svg.image?gcd(a,b)=gcd(b,r)\Rightarrow&space;gcd(a,b)=gcd(b,a\;mod\;b))

因此我们得出代码(递归)

```cpp
long long gcd(long long a,long long b){
    if(a<b) swap(a, b);//保证a不小于b
    return b==0?a:gcd(b,a%b);//b==0代表余数为0，即找到了最大公约数
}
```

#### 0xb 筛法求素数

这里只选用埃氏筛，思路如下

> 最小的素数是2，那么2的整数倍都不是素数，删去4,6,8…
>
> 余下的数里，最小的素数是3，删去6,9,12…
>
> 最终未被删去的数就是素数
>
> 时间复杂度是![](https://latex.codecogs.com/svg.image?O(NlogNlogN))

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 1000007;
bool prim[MAXN];//标记数组，默认为0。0为质数，1为非质数

void isPrime(long long n){
    for(int i=2;i<=n;i++){//一步一步筛选
        if(prim[i]==0) //是质数就把它若干倍的数都标记为1
            for(int j=i*2;j<=n;j+=i)
                prim[j]=1;
    }
}

int main(){
    prim[1]=1;//1不是质数
    long long n;
    cout<<"输入筛选范围n(n最大为1e6):";
    cin>>n;
    isPrime(n);
    cout<<"筛选结果如下:"<<endl;
    for (long long i = 1; i<=n; i++)
        if(prim[i]==0) cout<<i<<endl;
    return 0;
}
```

但是我们发现，在效率上有一个问题：

一个数会被删去多次
例如42会被2 3 7都删去一遍

这时候我们就可以使用欧拉筛(线性筛)，时间复杂度为![](https://latex.codecogs.com/svg.image?O(N))

这里不介绍了，有兴趣的可以前往[洛谷](https://www.luogu.com.cn/problem/solution/P3383)查看

#### 0xc 康托展开

> 康托展开是一个**全排列**到一个**自然数**的双射，常用于构建hash表时的空间压缩。
>
> 设有n个数（1，2，3，4，…，n），可以有组成不同(n!种)的排列组合，康托展开表示的就是是当前排列组合在n个不同元素的全排列中的名次。

先说一下思路，以序列![](https://latex.codecogs.com/svg.image?2,3,1)为例,怎么看是第几个呢？

我们**一位一位**去考虑

- 第一位是![](https://latex.codecogs.com/svg.image?2)，比它小的数只有一个![](https://latex.codecogs.com/svg.image?1)了，后面还有两位数可以随便排，因此有![](https://latex.codecogs.com/svg.image?1\times2!)种方法
- 第二位是![](https://latex.codecogs.com/svg.image?3)，比它小的数有两个![](https://latex.codecogs.com/svg.image?1,2)，但![](https://latex.codecogs.com/svg.image?2)前面已经用过了，所以只能选![](https://latex.codecogs.com/svg.image?1)，因此有![](https://latex.codecogs.com/svg.image?1\times1!)种方法
- 最后一位就不用考虑了，考虑的话也是![](https://latex.codecogs.com/svg.image?0\times0!)种方法
- 最后我们把这些加起来就是![](https://latex.codecogs.com/svg.image?2+1+0=3)，所以排名是第![](https://latex.codecogs.com/svg.image?4)名

所以我们得到公式：

![](https://latex.codecogs.com/svg.image?\sum_{i=1}^{n}sum_{a_i}\times(n-i)!)

其中![](https://latex.codecogs.com/svg.image?sum_{a_i})表示![](https://latex.codecogs.com/svg.image?a_i)后比它小的数的个数。~~容易看出~~,![](https://latex.codecogs.com/svg.image?sum_{a_i})就是![](https://latex.codecogs.com/svg.image?{a_i})的逆序数

因此我们只要维护好**阶乘运算**和**逆序数**就可以啦！

阶乘我们可以直接预处理，但逆序数一个一个求太慢了，因此得请出我们高级数据结构——树状数组，具体实现和求逆序数这里就不赘述了，可以戳[洛谷博客](https://www.luogu.com.cn/blog/ravenclawyangrunze/solution-p5367)

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+3,p=998244353;
int arr[MAXN],n;

long long fact[MAXN];
int t[MAXN];//树状数组

//树状数组三件套
int lowbit(int x){
    return x&-x;
}
//求[1,now]的和
int getSum(int now){
    int sum=0;
    while(now){
        sum+=t[now];now-=lowbit(now);
    }
    return sum;
}
//单点i修改
void update(int i,int val) {
    while (i<=n){
        t[i]+=val;i+=lowbit(i);
    }
}

void dofact(int n){ //预处理阶乘和树状数组
    fact[0]=1;fact[1]=1;
    update(1, 1);
    for (int i = 2; i<=n; i++) {
        fact[i]=(fact[i-1]*i)%p;
        update(i, 1);//将树状数组初始化为1
    }
}

int main(){
    cin>>n;
    dofact(n);
    long long ans=0;
    for (int i = 1; i<=n; i++){
        scanf("%d",arr+i);
        ans=(ans+((getSum(arr[i]-1))*fact[n-i]%p))%p; //这里得到树状数组[1,arr[i]-1]的和
        update(arr[i], -1);//将树状数组还原为0(也就是-1)
    }
    cout<<ans+1;
    return 0;
}
```

#### 0xd 逆康托展开

> 既然说康托展开是一个**全排列**到一个**自然数**的双射，那么它也一定是可逆的
>
> 也就是说我们可以通过某个序列的排名还原出这个序列

以集合![](https://latex.codecogs.com/svg.image?\\{1,2,3,4,5\\})为例,怎么找出第96个排列呢？

- 首先用96-1得到95

- 用95去除4! 得到3余23

  因此有3个数比它小，所以第一位是4

- 用23去除3! 得到3余5

  因此有3个数比它小，但4已经在之前出现过了，所以第二位是5

- 用5去除2!得到2余1

  因此有2个数比它小，所以第三位是3

- 用1去除1!得到1余0

  因此有1个数比它小，所以第二位是2

- 最后一个数只能是1

所以这个数是45321

也就是说，我们**不断 % (n-i)!, /(n-i)!就可以得到排列数组**

代码如下(只是思路，没有优化，最大能处理长度为11的序列)

```cpp
#include <bits/stdc++.h>
using namespace std;

bool vis[12];
long long f[12];
int ans[12];

void dofact(int n){ //预处理阶乘和树状数组
    f[0]=1;f[1]=1;
    for (int i = 2; i<=n; i++) {
        f[i]=(f[i-1]*i);
    }
}
void solve(int n,int k){    //已知一个 1~n 的排列 A 的排名为 k，求 A
    memset(vis,0,sizeof(vis)); k--;    //有 k-1 种排列比 A 的字典序小
    for(int i=1;i<=n;i++){
        int cnt=k/f[n-i];    //有cnt个数比 A 的第i位小 (取(n-i)!的商)
        for(int j=1;j<=n;j++)//循环遍历出第cnt个未出现过的数
            if(!vis[j]){
                if(!cnt){ans[i]=j;vis[j]=1;break;}//就是该数，把它标记为1
                cnt--;
            }
        k%=f[n-i];    //还剩下几种排列比 A 的字典序小(取(n-i)!的余数)
    }
}

int main(){
    int n,k;
    cout<<"输入序列长度n和排名k(n最大为11)"<<endl;
    cin>>n>>k;
    dofact(n);
    solve(n, k);
    for (int i = 1; i<=n; i++) {
        printf("%d ",ans[i]);
    }
    return 0;
}
```

