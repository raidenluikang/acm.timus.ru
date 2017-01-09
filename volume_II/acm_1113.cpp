  
// acm.timus.ru  1113. Jeep

#include <cstdio>

int main()
{
#ifndef ONLINE_JUDGE
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    int n,m,t,f;
    double s, ans;
    scanf("%d%d",&n,&m);
    
    t = 1;
    f = 0;
    while(s + m/(double)(t+t-1) < n)
    {
        s += m/(double)(t+t-1);
        f +=   m;
        ++t;
    }
    
    ans = (  n - s )*(t+t-1) + f;
    
    printf("%.0f\n", ( ans + 0.5 - 1.0E-12 ) );
 
    return 0;
}
