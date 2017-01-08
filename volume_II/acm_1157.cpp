
// acm.timus.ru 1135. Recruits

#include <cstdio>
#include <cmath>


int d[ 10000 + 8];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    int m,n,k;
    
    scanf("%d%d%d", &m, &n, &k);
    
    for(int i = 1; i <= 100; ++i)
    {
        // i  is divisor of  i, 2i, 3i, 4i, ... ai
        for(int j = i * i; j <= 10000; j += i )
        {
            ++d[ j ];
        }
    }
     
    for(int l = k; l <= 10000; ++l)
    {
        if (d[l] == n && d[l-k] == m)
        {
            printf("%d\n",l);
            return 0;
        }
    }
    printf("0\n");
    return 0;
}
