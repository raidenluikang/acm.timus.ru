//acm.timus.ru 1117. Hierarchy

// sol(1 x) = x - 2 * (popcount(x) - 1) - popcount(x ^ (x - 1))

#include <stdio.h>



static inline unsigned  number_of_bits(unsigned x)
{
    unsigned n = 0;
    while(x)
    {
        ++n;
        x &= x - 1;
    }
    return n;
}

static inline unsigned distance(unsigned x)
{
    return  x - 2 * (number_of_bits( x ) - 1) - number_of_bits( x ^ ( x - 1 ) );
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    unsigned x,y;
    scanf("%u%u",&x,&y);
    
    x = distance(x);
    y = distance(y);
    if (x>y)
        x = x- y;
    else
        x = y - x;
    printf("%u\n",x);
}
