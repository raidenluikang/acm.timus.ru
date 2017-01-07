#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

unsigned d[3008];


char in[ 1 << 16 ];
char const* o;
char * w;

static
unsigned readInt()
{
    unsigned  u = 0;
    while(*o && *o <= 32)++o;
    while(*o >='0' && *o <= '9') u = (u << 3) + (u << 1 ) + (*o ++ - '0');
    return u;
}

void writeInt(unsigned v)
{
    *--w = '\n';
    do *--w = v % 10 + '0'; while(v/=10);
}
static 
void show(unsigned const* l, unsigned const* r)
{
    unsigned root = *--r ;
    //printf("root = %d\n",root);
    unsigned const* m = std::lower_bound(l, r, root);
    writeInt(root);
    
    // m first position of interval [l..r)  which *m >= root
    
    // so  [l..m) - left side
    //     [m..r) - right side
    if (l < m)
        show(l, m);
    if (m < r)
        show(m, r);
    
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    w = in + sizeof(in);   
    int n = readInt();
    for(int i= 0; i != n; ++i)
        d[i] = readInt();
    
    
    show(d, d + n);
    
    fwrite(w, 1, in + sizeof(in) - w, stdout);
    return 0;
}
