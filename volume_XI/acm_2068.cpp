// 2068. Game of Nuts


#include <cstdio>


char in[65536];
char const * o;


int readInt()
{
    int u = 0;
    while(*o && *o <= 32)++o;
    while( *o >='0' && *o <= '9') u = (u << 3) + (u<<1) + (*o++ - '0');
    return u;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    
    int n,m,i;
    o = in; in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    n = readInt();
    m = 0;
    for(i = 0; i < n; ++i)
    {
        m += ( readInt() / 2 )& 1;
    }
    
    if (m&1) // first win, i.e. Daenerys
        puts("Daenerys");
    else
        puts("Stannis");
    
    return 0;
}
