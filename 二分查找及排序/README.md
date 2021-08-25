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

##### [P1116 车厢重组](https://www.luogu.com.cn/problem/P1116)

就是问冒泡排序的次数

```cpp
#include <stdio.h>

int main(){
    int n,cnt=0,swap;
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d",arr+i);
    }
    for (int i = (n-1); i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j+1]) {
                swap = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=swap;
                cnt++;
            }
        }
    }
    printf("%d",cnt);
}
```

#### 3xc 插入排序

模版代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int arr[10010];

void InsertSort(int arr[], int left, int right){
    for (int i = left; i <= right; i++) {
        int v=arr[i]; //当前的值v
        int l=left, r=i;    //在left~i(有序区间中二分查找插入点)
        while (l < r) {//在l与r之间插入排序，可以理解为解决子问题1→2→...→n
            int mid = (l + r) / 2;
            if (arr[mid] <= v)
                l = mid + 1;
            else
                r = mid;
        }//l为插入点
        for (int j = i-1;j >= l; j--)//把插入点后至该元素前的元素向后移一位
            arr[j+1] = arr[j];
        arr[l] = v;
    }
}

int main(){
    int n;
    scanf("%d",&n);
    for (int i = 1; i<=n; i++)
        scanf("%d",arr+i);
    InsertSort(arr, 1, n);
    for (int i = 1; i<=n; i++)
        printf("%d ",*(arr+i));
    return 0;
}
```

#### 3xd 选择排序

模版代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int arr[10010];

void SelectSort(int arr[], int left, int right){//选择排序
    for (int i = left; i <= right; i++) {
        int k;
        //选出后半段最小的数，然后与后半段的第一个数(arr[i])交换
        for (int j = k = i; j <= right; j++) //k指向目前最小的数
            if (arr[j]<arr[k])
                k = j;
        if (i<k)
            swap(arr[i], arr[k]);
    }
}

int main(){
    int n;
    scanf("%d",&n);
    for (int i = 1; i<=n; i++)
        scanf("%d",arr+i);
    SelectSort(arr, 1, n);
    for (int i = 1; i<=n; i++)
        printf("%d ",*(arr+i));
    return 0;
}
```

#### 3xe 快速排序

##### [P1059 [NOIP2006 普及组] 明明的随机数](https://www.luogu.com.cn/problem/P1059)

用桶排序来去重，再用STL中的sort(快速排序)即可

```cpp
#include <bits/stdc++.h>
using namespace std;

int NUM[1001];
int ran[101];

int main(){
    int N;
    scanf("%d",&N);
    for (int i = 0; i<N; i++) {
        scanf("%d",ran+i);
        if(NUM[ran[i]]==0)NUM[ran[i]]=1;
        else N--,i--;
    }
    printf("%d\n",N);
    sort(ran, ran+N);
    for (int i = 0; i<N; i++) {
        printf("%d",ran[i]);
        if (i!=(N-1)) {
            printf(" ");
        }
    }
    return 0;
}
```

##### [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)

```cpp
#include <bits/stdc++.h>
using namespace std;

int arr[100007];

void myqsort(int l,int r){
    int mid=arr[(l+r)/2];//作为中间点
    int low=l,hgh=r;//左右进行判断
    do {
        while (arr[low]<mid)//找出比中间点大的数
            low++;
        while (arr[hgh]>mid)//找出比中间点小的数
            hgh--;
        if(low<=hgh){       //若不符合条件(即左边数大[low]右边数小[hgh])则交换
            swap(arr[low], arr[hgh]);
            low++; hgh--;
        }
    } while (low<=hgh);
    if(l<hgh) myqsort(l, hgh);  //进行下一轮排序
    if(low<r) myqsort(low, r);  //进行下一轮排序
}

int main(){
    int n;
    scanf("%d",&n);
    for (int i = 1; i<=n; i++)
        scanf("%d",arr+i);
    myqsort(1, n);
    for (int i = 1; i<=n; i++) {
        printf("%d ",arr[i]);
    }
    return 0;
}
```

##### [P1104 生日](https://www.luogu.com.cn/problem/P1104)

简单的结构体排序(自定义关键字排序)

```cpp
#include <bits/stdc++.h>

using namespace std;
struct birday {
    string name;
    int y,m,d,code;
}bir[101];

bool cmp(const birday &h1,const birday &h2){//手写比较函数
    if(h1.y!=h2.y) return h1.y<h2.y;
    if(h1.m!=h2.m) return h1.m<h2.m;
    if(h1.d!=h2.d) return h1.d<h2.d;
    return h1.code>h2.code;
}

int main(){
    int n;
    scanf("%d",&n);
    for (int i =1; i<=n; i++){
        cin>>bir[i].name>>bir[i].y>>bir[i].m>>bir[i].d;
        bir[i].code=i;
    }
    sort(bir+1, bir+1+n, cmp);
    for (int i = 1; i<=n; i++) {
        cout<<bir[i].name<<endl;
    }
    return 0;
}
```

