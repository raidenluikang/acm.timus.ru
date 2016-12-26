//acm.timus.ru 1053. Pinocchio


#include <cstdio>


unsigned gcd(unsigned a,unsigned b)
{
    unsigned m;
    while(b != 0)
    {
        m = a % b;
        a = b;
        b = m;
    }
    return a;
}

char in[65536];
const char* o;

unsigned readInt()
{
    unsigned u = 0;
    while(*o && *o <= 32)++o;
    while(*o >= 48) u =(u << 3) + (u<<1) + *o++ - 48;
    return u;
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif

    o  = in;
    in[fread(in, 1, sizeof(in)-4, stdin)] = 0;

    unsigned n = readInt();
    unsigned ans = 0;
    for(unsigned i = 0; i != n; ++i)
    {
        unsigned a = readInt();
        ans = gcd(ans, a);
    }
    printf("%u\n",ans);
}
