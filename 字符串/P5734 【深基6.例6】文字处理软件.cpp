#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    scanf("%d",&n);
    char str[1000];
    scanf("%s",str);
    while (n--) {
        int cmd;
        int a,b;
        char dst[1000];
        scanf("%d",&cmd);
        switch (cmd) {
            case 1://cat
                scanf("%s",dst);
                strcat(str, dst);
                printf("%s\n",str);
                break;
            case 2:{
                scanf("%d%d",&a,&b);
                char tmp[1000]={0};
                strncpy(tmp, str+a, b);
                strcpy(str, tmp);
                printf("%s\n",str);
            }
                break;
            case 3:
                scanf("%d%s",&a,dst);
            {
                char tmpa[1000]={0},tmpb[1000]={0};
                strncpy(tmpa, str, a);
                strncpy(tmpb, str+a, strlen(str)-a);
                strcat(tmpa, dst);strcat(tmpa, tmpb);
                strcpy(str, tmpa);
            }
                printf("%s\n",str);
                break;
            case 4:
                scanf("%s",dst);
                char *p=strstr(str, dst);
                if(p==NULL) printf("-1\n");
                else{
                    printf("%d\n",p-str);
                }
                break;
        }
    }
    return 0;
}
