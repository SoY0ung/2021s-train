## 2 链表
(如遇公式显示问题，请关闭深色模式并使用科学上网)

链表是最简单、最基本的一种数据结构，每个元素有前驱（前一个元素）后继（后一个元素）。

与静态数组不同，链表的长度(大小)是可以时刻变化的，这在动态程序设计中起到了很大的作用。

在这一节，我不会讲链表的本体实现，而是介绍C++的STL库中的好朋友：vector和list，vector可当作单链表，list可当作双向链表。

我的代码也将用上述模版编写(同样，**只列举部分**)。
##### [P1160 队列安排](https://www.luogu.com.cn/problem/P1160)

这里用到了STL的list和迭代器。更多见[洛谷博客](https://www.luogu.com.cn/blog/onlynagesha/solution-p1160)

```cpp
#include <bits/stdc++.h>
using namespace std;

list<int> lst;
typedef list<int>::iterator Iter;
Iter pos[100005];

void judge(int n){
    lst.push_front(1);
    pos[1]=lst.begin();
    for (int i = 2; i<=n; i++) {
        int k,p;
        scanf("%d%d",&k,&p);
        if(p==0){//left
            pos[i]=lst.insert(pos[k], i);//insert()函数插入到迭代器的前面
        }else {//right
            pos[i]=lst.insert(next(pos[k]), i);
        }
    }
}

void judge2(int m){
    for (int i = 1; i<=m; i++) {
        int x;
        scanf("%d",&x);
        if(pos[x]!=lst.end()){
            lst.erase(pos[x]);
        }
        pos[x]=lst.end();
    }
}

int main(){
    int n;
    scanf("%d",&n);
    judge(n);
    int m;
    scanf("%d",&m);
    judge2(m);
    bool frt=true;
    for (auto i:lst) {
        if(!frt)  putchar(' ');
        frt=false;
        printf("%d",i);
    }
    printf("\n");
    return 0;
}
```

