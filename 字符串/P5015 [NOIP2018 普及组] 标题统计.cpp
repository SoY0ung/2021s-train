#include <bits/stdc++.h>

using namespace std;

int main(){
    int length=0;
    char str[10];
    fgets(str, 9, stdin);
    int l=strlen(str);
    for (int i = 0; i<l; i++) {
        if(str[i]!=' '&&str[i]!='\n')
            length++;
    }
    printf("%d",length);
    return 0;
}
