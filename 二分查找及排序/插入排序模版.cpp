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
