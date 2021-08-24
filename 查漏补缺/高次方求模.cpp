#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9 + 7;//规定对该数取模
 
long long fastpow(long long x, long long y) {//快速幂取模
    x %= mod;
    long long res = 1;
    while (y) {
        if (y & 1)res = res * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return res;
}

long long inv(long long n) {//逆元就是n^(mod-2)
    return fastpow(n, mod - 2);
}

int main(){
    long long a;
    cin>>a;
    cout<<inv(a);
    return 0;
}
