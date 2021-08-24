#include <bits/stdc++.h>
using namespace std;

int main(){
    double a,b,c;
    cin>>a>>b>>c;
    double S;
    S=1.0/4*sqrt((a+b+c)*(a+b-c)*(a+c-b)*(b+c-a));//海伦公式
    cout<<S;
    return 0;
}
