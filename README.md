# 2021暑假自学报告

(如遇公式显示问题，请关闭深色模式并使用科学上网)

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
>  ![](https://latex.codecogs.com/svg.image?gcd(a,b)=gcd(b,r)\Rightarrow&space;gcd(a,b)=gcd(b,a\\;\textrm{mod}\\;b))

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
> 设有n个数（1，2，3，4，…   ，n），可以有组成不同(n!种)的排列组合，康托展开表示的就是是当前排列组合在n个不同元素的全排列中的名次。

先说一下思路，以序列![](https://latex.codecogs.com/svg.image?2,3,1)为例,怎么看是第几个呢？

我们**一位一位**去考虑

- 第一位是![](https://latex.codecogs.com/svg.image?2)，比它小的数只有一个![](https://latex.codecogs.com/svg.image?1)了，后面还有两位数可以随便排，因此有![](https://latex.codecogs.com/svg.image?1\times2!)种方法
- 第二位是![](https://latex.codecogs.com/svg.image?3)，比它小的数有两个![](https://latex.codecogs.com/svg.image?1,2)，但![](https://latex.codecogs.com/svg.image?2)前面已经用过了，所以只能选![](https://latex.codecogs.com/svg.image?1)，因此有![](https://latex.codecogs.com/svg.image?1\times1!)种方法
- 最后一位就不用考虑了，考虑的话也是![](https://latex.codecogs.com/svg.image?0\times0!)种方法
- 最后我们把这些加起来就是![](https://latex.codecogs.com/svg.image?2+1+0=3)，所以排名是第![](https://latex.codecogs.com/svg.image?4)名

所以我们得到公式：

![](https://latex.codecogs.com/svg.image?\sum_{i=1}^{n}sum_{a_i}\times(n-i)!)

其中![](https://latex.codecogs.com/svg.image?sum_{a_i})表示![](https://latex.codecogs.com/svg.image?a_i)后比它小的数的个数。~~容易看出~~, ![](https://latex.codecogs.com/svg.image?sum_{a_i}) 就是 ![](https://latex.codecogs.com/svg.image?{a_i}) 的逆序数

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
#### 0xe 同余定理

> **同余定理**：两个整数同时除以一个整数得到的**余数相同**，则两**整数**同余。记作![](https://latex.codecogs.com/svg.image?a\equiv{b}(\textrm{mod}\;m))

直接写出结论(证明略)

![](https://latex.codecogs.com/svg.image?(a+b)\\;\textrm{mod}\\;p=(a\\;\textrm{mod}\\;p+b\\;\textrm{mod}\\;p)\\;\textrm{mod}\\;p)

![](https://latex.codecogs.com/svg.image?(a-b)\\;\textrm{mod}\\;p=(a\\;\textrm{mod}\\;p-b\\;\textrm{mod}\\;p+p)\\;\textrm{mod}\\;p)

![](https://latex.codecogs.com/svg.image?(a\\,\times\\,b)\\;\textrm{mod}\\;p=a\\;\textrm{mod}\\;p\times{b}\\;\textrm{mod}\\;p)

![](https://latex.codecogs.com/svg.image?\textrm{But}\quad(a\\,\div\\,b)\\;\textrm{mod}\\;p\\,\neq\\,a\\;\textrm{mod}\\;p\\,\div\\,b\\;\textrm{mod}\\;p)

因此对一个高精度数取模，我们可以逐位分解求模：

如1234 = ((1 * 10 + 2) * 10 + 3) * 10 + 4，对这个多项式逐项取模即可

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int main(){
    string a;
    int b;
    cin >> a >> b;
    int len = a.length();
    int ans = 0;
    for(int i = 0; i < len; i++){
        ans = (ans * 10 + a[i] - '0') % b;
    }
    cout << ans << endl;
    return 0;
}
```
#### 0xf 高次方求模(快速幂)

在上面我们知道，除法是不满足同余运算的，那如果真遇到了除法取模(如求组合数)的情况，要怎么办呢？

这时候，我们的**费马小定理**就登场啦！(一般而言，我们的 ![](https://latex.codecogs.com/svg.image?p) 都是质数)

对于一个数 ![](https://latex.codecogs.com/svg.image?n) ，它的逆元就是![](https://latex.codecogs.com/svg.image?n^{p-2})，也就是费马小定理的 ![](https://latex.codecogs.com/svg.image?n\\,\times{n^{p-2}}\equiv1\\,(\textrm{mod}\\,p))

一般这个 ![](https://latex.codecogs.com/svg.image?p) 都很大，我们从1次方开始求效率肯定低，因此我们结合二进制，有了**快速幂取模**

> **快速幂取模**：将幂拆解为多个底数的平方次的积，如果指数为偶数，把指数除以2，并让底数的平方次取余，如果指数为奇数，就把多出来的底数记录下来，再执行偶数次的操作。(具体可百度)

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9 + 7;//规定对该数取模
 
long long fastpow(long long x, long long y) {//快速幂取模
    x %= mod;
    long long res = 1;
    while (y) {
        if (y & 1)res = res * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return res;
}

long long inv(long long n) {//逆元就是n^(mod-2)
    return fastpow(n, mod - 2);
}

int main(){
    long long a;
    cin>>a;
    cout<<inv(a);
    return 0;
}
```

#### 0xg 三角形面积(海伦公式)

直接上公式

![](https://latex.codecogs.com/svg.image?S=\sqrt{p(p-a)(p-b)(p-c)}{\qquad}(p=\frac{1}2(a+b+c)))

![](https://latex.codecogs.com/svg.image?\Rightarrow{S}=\frac{1}4\sqrt{(a+b+c)(a+b-c)(a+c-b)(b+c-a)})

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    double a,b,c;
    cin>>a>>b>>c;
    double S;
    S=1.0/4*sqrt((a+b+c)*(a+b-c)*(a+c-b)*(b+c-a));//海伦公式
    cout<<S;
    return 0;
}
```

#### 0xh 三点顺序

即判断三点![](https://latex.codecogs.com/svg.image?P_1,P_2,P_3)是顺时针还是逆时针方向(或共线)
设![](https://latex.codecogs.com/svg.image?P_1=(x_1,y_1),\\;P_2=(x_2,y_2),\\;P_3=(x_3,y_3) )
则可得到向量 
![](https://latex.codecogs.com/svg.image?\boldsymbol{P_1P_2}=(x_2-x_1,y_2-y_1) )
![](https://latex.codecogs.com/svg.image?\boldsymbol{P_2P_3}=(x_3-x_2,y_3-y_2))
则当 ![](https://latex.codecogs.com/svg.image?\boldsymbol{P_1P_2})与![](https://latex.codecogs.com/svg.image?\boldsymbol{P_2P_3}) 的叉乘（向量积)在z轴上的分量为

![](https://latex.codecogs.com/svg.image?(x_2-x_1)*(y_3-y_2)-(y_2-y_1)*(x_3-x_2))

由右手定则得：

- 其为正时，![](https://latex.codecogs.com/svg.image?\overline{P_1P_2P_3}) 路径的走向为逆时针
- 其为负时，![](https://latex.codecogs.com/svg.image?\overline{P_1P_2P_3}) 路径的走向为顺时针 
- 其为零时，![](https://latex.codecogs.com/svg.image?\overline{P_1P_2P_3})三点在一直线上

```cpp
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
```
## 1 数组

数组可谓程序存储的基础，充分利用数组以及其高效处理的函数可以让我们写代码事半功倍

**由于数组属于基础部分，为节省篇幅，这里只列举部分(少于20题)。**

#### 1xa 一维数组

一维数组的处理无非就是排序和遍历，偶尔会用来标记某个数是否出现。

当然，有些高级数据结构(如前面提到的树状数组)的基础数据结构就是数组。

这里基本不做思路分析，直接上代码

##### [**P1047 [NOIP2005 普及组] 校门外的树.cpp**](https://www.luogu.com.cn/problem/P1047)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int arr[MAXN];
int brr[MAXN];

int main(){
    int n;
    cin>>n;
    for (int i = 1; i<=n; i++) {
        scanf("%d",arr+i);
        for (int j = 1; j<i; j++) {
            if(arr[j]<arr[i]) brr[i]++;
        }
    }
    for(int i = 1;i<=n;i++){
        printf("%d ",brr[i]);
    }
    return 0;
}
```

##### [P1980 [NOIP2013 普及组] 计数问题](https://www.luogu.com.cn/problem/P1980)

```cpp
#include <stdio.h>

int main(){
    int num[10]={0};
    int n,x;
    scanf("%d %d",&n,&x);
    for (int i = 1; i<=n; i++) {
        int j = i,k;
        while ((k=j%10) != j) {
            num[k]++;
            j = j / 10;
        }
        num[j]++;
    }
    printf("%d",num[x]);
    return 0;
}
```

##### [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int arr[MAXN];

int main(){
    //当然，也可以用栈(stack)做
    int num,cnt=0;
    while (1) {
        scanf("%d",&num);
        if(num==0) break;
        arr[++cnt]=num;
    }
    for (int i = cnt; i>=1; i--) {
        printf("%d ",arr[i]);
    }
    return 0;
}
```

##### [P2615 NOIP2015 提高组 神奇的幻方](https://www.luogu.com.cn/problem/P2615)

```cpp
#include <stdio.h>

int arr[40][40];

int main(){
    int N,a,b;
    scanf("%d",&N);
    a = 0;b = (N-1)/2;
start:arr[a][b]=1;
    for (int i = 2; i <= N*N; i++) {
        a--;b++;
        if (a < 0) {
            a += N;
        }
        if (b >= N) {
            b -= N;
        }
        if (arr[a][b] == 0) {
            arr[a][b]=i;
        } else {
            a+=2;b--;
            if (b < 0) {
                b += N;
            }
            if (a >= N) {
                a -= N;
            }
            arr[a][b]=i;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ",arr[i][j]);
        }
        putchar('\n');
    }
    return 0;
}
```

##### [P1161 开灯](https://www.luogu.com.cn/problem/P1161)

```cpp
#include <stdio.h>

int light[2000000]={0};

int main(){
    int n,t,l,max=0;
    double a;
    scanf("%d",&n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %d",&a,&t);
        if (a*t>max) {
            max = a * t;
        }
        for (int t_i = 1; t_i <= t; t_i++) {
            l = a * t_i;
            light[l] = !light[l];
        }
    }
    for (int i = 1; i <= max; i++) {
        if (light[i] == 1) {
            printf("%d",i);
            break;
        }
    }
    return 0;
}
```

##### [P1036 NOIP2002 普及组 选数](https://www.luogu.com.cn/problem/P1036)

这题说一下思路，首先用线性筛筛出全部质数，然后再用dfs(深度优先搜索)进行n选r的操作，也就是用dfs暴力求出每一种情况。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,r,ans[22],aans[22],cnt=0,havepri[100000003],numpri=0;
bool vis[22],prime[100000003];
void isPrime();
void dfs(int dep){
    if(dep>r) {
        int tot=0;
        for (int i = 1; i<=r; i++)
            tot+=aans[ans[i]];
        if(!prime[tot]) cnt++;
        return;
    }
    for (int i = 1; i<=n; i++) {
        if(!vis[i]) {
            vis[i]=1;
            if(ans[dep-1]<i){
            // meet the conditions --> Search
                ans[dep]=i;
                dfs(dep+1);
            }
            vis[i]=0;
        }
    }
}

int main(){
    scanf("%d%d",&n,&r);
    for (int i = 1; i<=n; i++)
        scanf("%d",aans+i);
    isPrime();
    //take r elements from n elements in total
    dfs(1);
    printf("%d",cnt);
    return 0;
}

void isPrime(){
    prime[1]=1; prime[0]=1;
    for (int i = 2; i<=100000003; i++) {
        if(!prime[i]) havepri[++numpri]=i;
        for (int k = 1; k<=numpri&&havepri[k]*i<=100000001; k++) {
            prime[havepri[k]*i]=1;
            if(i%havepri[k]==0) break;
        }
    }
}
```

##### [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

上面提过了，可以戳[洛谷博客](https://www.luogu.com.cn/blog/ravenclawyangrunze/solution-p5367)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5+7;
int n,t[MAXN];

int lowbit(int x){
    return x&-x;
}

void update(int pos,int val){
    while (pos<=n) {
        t[pos]+=val;
        pos+=lowbit(pos);
    }
}

int sum(int x){
    int ans=0;
    while (x) {
        ans+=t[x];
        x-=lowbit(x);
    }
    return ans;
}

int main(){
    int m;
    scanf("%d%d",&n,&m);
    for (int i = 1; i<=n; i++) {
        int v;
        scanf("%d",&v);
        update(i, v);
    }
    for (int i = 1; i<=m; i++) {
        int cmd,x,y;
        scanf("%d%d%d",&cmd,&x,&y);
        if(cmd==1){
            update(x, y);
        }else {
            printf("%d\n",sum(y)-sum(x-1));
        }
    }
    return 0;
}
```

#### 1xb 二维数组

##### [P5731 【深基5.习6】蛇形方阵](https://www.luogu.com.cn/problem/P5731)

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[10][10];
int i=1,j=1,flag=1,n,cnt=2;

void heng(){
    //j only
    if (flag<=2) {
        //move right j++
        j++;
        while (1) {
            if (j==n||a[i][j+1]!=0) {
                a[i][j]=cnt;
                cnt++;
                flag++;
                break;
            }else{
                a[i][j]=cnt;
                cnt++;
                j++;
            }
        }
        if (flag>4) {
            flag=1;
        }
    }else {
        //move left j--
        j--;
        while (1) {
            if (j==1||a[i][j-1]!=0) {
                a[i][j]=cnt;
                cnt++;
                flag++;
                break;
            }else{
                a[i][j]=cnt;
                cnt++;
                j--;
            }
        }
        if (flag>4) {
            flag=1;
        }
    }
    
}
void shu(){
    //i only
    if (flag<=2) {
        //move down i++
        i++;
        while (1) {
            if (i==n||a[i+1][j]!=0) {
                a[i][j]=cnt;
                cnt++;
                flag++;
                break;
            }else{
                a[i][j]=cnt;
                cnt++;
                i++;
            }
        }
        if (flag>4) {
            flag=1;
        }
    }else{
        //move up i--
        i--;
        while (1) {
            if (i==1||a[i-1][j]!=0) {
                a[i][j]=cnt;
                cnt++;
                flag++;
                break;
            }else{
                a[i][j]=cnt;
                cnt++;
                i--;
            }
        }
        if (flag>4) {
            flag=1;
        }
    }
}

int main(){
    scanf("%d",&n);
    int mx=n*n;
    a[1][1]=1;
    while (1) {
        heng();
        if (cnt>mx)
            break;
        shu();
        if (cnt>mx)
            break;
    }
    for (i=1; i<=n; i++) {
        for (j=1; j<=n; j++) {
            printf("%3d",a[i][j]);
        }
        putchar('\n');
    }
    return 0;
}
```

##### [P5732 【深基5.习7】杨辉三角](https://www.luogu.com.cn/problem/P5732)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN=22;
int arr[MAXN][MAXN];

int main(){
    arr[1][1]=1;
    int n;
    scanf("%d",&n);
    for (int i = 2; i<=n; i++) {
        for (int j = 1; j<=i; j++) {
            arr[i][j]=arr[i-1][j-1]+arr[i-1][j];
        }
    }
    for (int i = 1; i<=n; i++) {
        for (int j = 1; j<=i; j++) {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```

##### [P1789 【Mc生存】插火把](https://www.luogu.com.cn/problem/P1789)

```cpp
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
```

