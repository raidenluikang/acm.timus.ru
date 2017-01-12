
#include <stdio.h>

unsigned n,m;
unsigned a[1024];

char in[65536];
char const* o;
char *w;
unsigned readInt()
{
    unsigned u = 0;
    while(*o && *o <= 32)++o;
    while(*o >='0' && *o<='9') u =(u << 3) + (u << 1) +(*o++ - '0');
    return u;
}
void writeInt(unsigned u, char c)
{
    unsigned v = u, n = 0;
    do ++n; while(v/=10);
    v = n;
    while(v-->0)w[v] = u % 10 + '0', u/=10;
    w += n;
    *w++ = c;
}

int solve()
{
    unsigned i,j;
    o = in; w = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    n = readInt();
    
    
    for( i = 0; i!=n;++i)
        a[i] = readInt();
    
    for( i = 0, j = 0; i != n; i = j)
    {
        for( ; j != n && a[i] == a[j]; ++j);
        
        writeInt(j - i, ' ');
        writeInt(a[ i ], ' ');
    }
	 
    w[-1]= '\n';
    
    fwrite(in ,1 , w - in, stdout);
	 
    
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

