# 2021暑假自学报告



## 0 查漏补缺

#### 0xa 欧几里得算法求最大公约数

>  辗转相除法， 又名欧几里得算法，是求最大公约数的一种方法。
>
> 它的具体做法是：用**较大**数除以**较小**数，再用出现的余数（第一余数）去除除数，再用出现的余数（第二余数）去除第一余数，如此反复，直到最后余数是0为止。如果是求两个数的最大公约数，那么最后的**除数**就是这两个数的最大公约数。
>
> 用公式表达就是：
>
> 当![](https://latex.codecogs.com/svg.image?a=q*b&plus;r),即 ![](https://latex.codecogs.com/svg.latex?a\div{b}=q\cdots{r}),有
>
> ![](https://latex.codecogs.com/svg.latex?gcd(a,b)=gcd(b,r)\Rightarrow{gcd(a,b)=gcd(b,a{\&space;}mod{\&space;}b)})

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

