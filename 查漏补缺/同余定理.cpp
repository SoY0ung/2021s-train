#include <bits/stdc++.h>
using namespace std;
 
int main(){
    string a;
    int b;
    cin >> a >> b;
    int len = a.length();
    int ans = 0;
    for(int i = 0; i < len; i++){
        ans = (ans * 10 + a[i] - '0') % b;
    }
    cout << ans << endl;
    return 0;
}
