#include <cstdio>
#include <cstring>
#include <cmath>

unsigned w[128];

char in[1<<16];
char const* o;


static
unsigned readInt()
{
    unsigned  u = 0;
    while(*o && *o <= 32)++o;
    while(*o >='0' && *o <= '9') u = (u << 3) + (u << 1 ) + (*o ++ - '0');
    return u;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
   
    unsigned n = readInt();
    
    for(unsigned i = 0; i != n; ++i)
        w[i] = readInt();
    
    for(unsigned i = 0; i != n; ++i)
    {
        for(unsigned j = i + 1; j != n; ++j)
        {
            if (w[i] < w[j]){unsigned t = w[i]; w[i] = w[j]; w[j] = t;}
        }
    }
    
    double a = w[0];
    for(unsigned i = 1; i != n; ++i)
    {
        a = 2 * sqrt(a * w[i]);
    }
    printf("%.2f\n",a);
    return 0;
}
