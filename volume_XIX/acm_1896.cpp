

// 1896. War Games 2.1

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stdint.h>

typedef  uint8_t  i8;
typedef  uint16_t i16;
typedef  uint32_t i32;

// 1.1 * 10^6 = 1 100 000 
static const int N = 1100008;
static const int NSH = 1 << 21;

i8 tree[ NSH + N];
i32 rem[ 1 << 16 ];

int n, h, k;


void init_tree(int n)
{
    for(int i = 0; i < n;++i)tree[i + NSH] = 1;
    
    for(int i = (n + NSH) / 2;  i >  0; --i)
    {
        tree[i] = tree[ i << 1 ] + tree[ i << 1 | 1 ];
    }
    
    for(int i = 65535; i>= 32768; --i)rem[i] = tree[i<<1] + tree[i<<1|1];
    for(int i = 32767; i >  0; --i)rem[i] = rem[i<<1] + rem[i<<1|1];
}

int kth_min(int p)
{
    int l = 1;
    ++p;
    while( l < 32768 )
    {
        l += l;
        if (rem[l] < p)p -= rem[l++];
    }
    
    while( l < NSH )
    {
        l += l;
        if (tree[l] < p) p-= tree[l++];
    }
    
    return l - NSH;
}

void dec(int i)
{
    i += NSH;
   
    for( ; i >= 65536; i>>= 1)
        --tree[i];
    
    // i < 1^16
    for( ; i > 0; i>>=1)
        --tree[i], --rem[i];
}

int xor_solve()
{
    int id, result = 0;
    int p = 0;
    
    // p = sum( i = 0 ..j,  (k-1)% (n-i) )
    
    for(int i = 0; i < n; ++i)
    {
        p = (p + k - 1) % ( n - i );
        
        id = kth_min( p );
        //printf("i = %d  id = %d\n", i+1, id+1);
        result ^= abs(i - id);
        
        dec( id );
    }
     
    return result;
}

int solve()
{
    scanf("%d%d",&n,&k);
    init_tree(n);
    int r = xor_solve();
    printf("%d\n", r);
    
    return 0;
}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    
#endif
   
    solve();
    
    
}
   
