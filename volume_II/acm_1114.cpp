



// acm.timus.ru 1114. Boxes

#include <stdio.h>


int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w",stdout);
#endif 
    
    //unsigned __int64 i,r=1,d=l-k;
    //for (i=1;i<=d;i++) {r*=(i+k); r/=i;}
    //return r;
    
    // l = n + a   k = a
    // i, r = 1 ,  d = l - k = n
    // i = 1..n 
    // r = r * (i + k)/i
    // r = (1+a)/1 * (2+a)/2 + .. (n+a)/n = (1+a)(2+a)...(n+a)/n! = (n+a)!/n!/a! = c[n+a][a] - binomial formula
    
    int n,a,b;
    unsigned long long c[40][40] = {};
    c[0][0] = 1;
    for(int i = 1; i < 40; ++i)
    {
        c[i][0] = 1;
        for(int j = 1; j < 40; ++j)
            c[i][j] = c[i-1][j] + c[i-1][j-1];
    }
    
    scanf("%d%d%d",&n,&a,&b);
    printf("%llu\n", c[n+a][a] * c[n+b][b]);
}
