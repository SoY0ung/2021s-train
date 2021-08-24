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

