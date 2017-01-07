// acm.timus.ru 1194. Handshakes


#include <cstdio>

static const int N = 20000 + 8;

//int g[ N ];

char in[1<< 9];
char const* o;

int n, q, ans, gn, gi;

static
unsigned readInt()
{
    unsigned u = 0;
    while(*o && *o <= 32)++o;
    while(*o >='0' && *o <='9')u = (u<<3) + (u<<1) + (*o ++ - '0');
    return u;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    while(*o && *o <= 32)++o;
    n = readInt();
    q = readInt();
    
    ans = (n * (n-1))/2 - q;
    
    printf("%d\n",ans);
    return 0;
}
