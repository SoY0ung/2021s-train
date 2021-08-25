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
