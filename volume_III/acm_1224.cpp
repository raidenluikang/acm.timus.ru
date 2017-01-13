// 1224. Spiral

#include <cstdio>

//    1 2 3 4 5 6 7 8
//0:  + - - - - - - -
//1:  + + - - - - - - 
//2:  + + + + - - - -
//3:  + + + + + + + -
//4:  + + + + + + + +
unsigned cnt_rotate(unsigned n, unsigned m)
{
    unsigned rn = 0;
    while( n >  3 && m > 3)
    {
            // x     n-2*x >= 1 &&  m - 2*x >= 1
       // 2x <= n - 3  && 2x <= m - 3
       unsigned x = ( (n < m ? n : m) - 1) / 2 ;
       n  -= x * 2;
       m  -= x * 2;
       rn += x * 4;	
    }
    // n <= 3 || m <= 3
    if(n == 1)return rn + 0;
    if(m == 1)return rn + 1;
    if(n == 2)return rn + 2;
    if(m == 2)return rn + 3;
    if(n == 3)return rn + 4;
    if(m == 3)return rn + 5;
    
    return rn;
}

int solve()
{
    unsigned n,m;

    scanf("%u%u",&n,&m);
    printf("%u\n", cnt_rotate(n,m));

    return 0;
}

int main() 
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    
    solve();
    
    return 0;
}
