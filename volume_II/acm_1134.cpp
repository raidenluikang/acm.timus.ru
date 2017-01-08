#include <stdio.h>
#include <stdlib.h>

int d[ 1024 ] ;
int e[ 1024 ] ;
int l[ 1024 ] ;

int n,m;
char in[65536];
char const* o;
static 
int readInt();
static
void readData()
{
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    n = readInt();
    m = readInt();
    
    if (m > n)
    {
        puts("NO");
        exit(0);
    }
    for(int i= 0; i<=n;++i)
    {
        d[i] = 0;
        e[i] = 0;
        l[i] = 2;
    }
    
    l[ 0 ] = l[ n ] = 1;
    
    for(int i= 0; i != m; ++i)
    {
        int x  = readInt();
        if (x > n)
        {
            puts("NO");
            exit(0);
        }
        d[x]++;
    }
}

static
int readInt()
{
    int u = 0;
    while(*o && *o <= 32)++o;
    while(*o>='0' && *o <='9') u = (u << 3) + (u << 1 ) + (*o++ - '0');
    return u;
}

static
bool calc()
{
    for(int i = 0; i <= n; ++i)
    {
        if ( d[ i ] + e[ i ] > l[ i ])
            return false;
        
        for(int j = 0; j < d[i]; ++j)
        {
            // i - 1  and i + 1
            if ( i > 0 && d[ i - 1] + e[ i - 1 ] < l[ i - 1] )// can put left
            {
                ++e[ i - 1 ];
            }
            else if (i + 1 <= n && d[ i + 1 ] + e[ i + 1 ] < l[ i + 1 ] )
            {
                ++e[ i + 1 ];
            }
            else 
            {
                //can't put left and right, so this sequence is invalid
                return false;
            }
        }
    }
    
    return true;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 

    readData();
    
    
    if (calc())
        puts("YES");
    else
        puts("NO");
    
    return 0;
}
