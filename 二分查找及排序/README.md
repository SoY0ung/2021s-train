## 3 二分查找及排序
(如遇公式显示问题，请关闭深色模式并使用科学上网)

#### 3xa 二分

> **二分查找**：在一个**单调有序**的集合中查找元素，每次将集合分为左右两部分，判断解在哪个部分中并调整集合上 下界，重复直到找到目标元素。

利用二分，我们就可以对一些题目进行**二分答案**  (这里**节选**几题)

##### [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,k,arr[100003];

int judge(int x){
    int cnt=0;
    for (int i = 1; i<=n; i++) {
        cnt+=(arr[i]/x);
        if(cnt>=k) return 1;
    }
    return 0;
}

int main(){
    long long sum=0;
    scanf("%d%d",&n,&k);
    for (int i = 1; i<=n; i++) {
        scanf("%d",arr+i);
        sum+=arr[i];
    }
    if(sum<k) {printf("0"); return 0;}
    sort(arr+1, arr+1+n);
    int l=1,r=arr[n],mid;
    while (l<r-1) {	//经典二分操作
        mid=(l+r)/2;
        if(judge(mid)) l=mid;
        else r=mid-1;
    }
    printf("%d",l);
    return 0;
}
```

##### [P2249 【深基13.例1】查找](https://www.luogu.com.cn/problem/P2249)

STL中的库函数也有二分查找函数

```cpp
#include <algorithm>//在algorithm头文件中
lower_bound(起始地址，结束地址，变量)//返回从起始地址到结束地址中，第一个大于等于变量的值的地址(位置)
upper_bound(起始地址，结束地址，变量)//返回从起始地址到结束地址中，第一个大于变量的值的地址(位置)
```

在这一题就用到了这里的库函数

```cpp
#include <bits/stdc++.h>
using namespace std;
long long arr[1000001];

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i = 1; i<=n; i++) {
        scanf("%lld",arr+i);
    }
    for (int i = 1; i<=m; i++) {
        long long x,num;
        scanf("%lld",&x);
        num = lower_bound(arr+1, arr+1+n, x)-(arr+1);
        if(upper_bound(arr+1, arr+1+n, x)-(arr+1) - num==0)	//没有找到，即不存在这个数
            printf("-1 ");
        else printf("%lld ",num+1);
    }
    return 0;
}
```

#### 3xb 冒泡排序


