
// acm.timus.ru 1209. 1 10 100, 1000

#include <cstdio>
#include <cmath>
char const*o;
char * w;
char in[ 1 << 20 ];

unsigned readInt()
{
    unsigned u = 0;
    while(*o && *o <= 32)++o;
    while(*o >= '0') u = (u << 3) + (u << 1) + (*o++ - '0');
    return u;
}

int solve()
{
    unsigned n, i, k, res, root, step, r2;
    o = w = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;

    n = readInt();
    for( i = 0; i < n; ++i)
    {
         
        k = readInt();
        root = sqrt( k + k - 2.0);// k = 2^31 - 1,  k+k = 2^32-2
        
        if (root * (root + 1)/2 == k - 1)
          *w++ = '1';
        else
            *w++ = '0';
        
        *w++ = ' ';
    }
    w[-1] = '\n';
    fwrite(in,1,w-in,stdout);
    
    return 0;
}

int main(int argc, char **argv)
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    
    solve();

    return 0;
}

