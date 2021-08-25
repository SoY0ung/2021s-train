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
