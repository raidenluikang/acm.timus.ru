

//1184. Cable Master


#include <cstdio>

static const int N = 10000;


char in[65536*4]; // 100 km = 100 * 1000 m = 100 * 1000 * 100 sm = 10^7 sm.

char const* o;

int l[ N ];

int readInt()
{
    int u = 0;
    while(*o && *o <= 32)++o;
    
    while(*o >='0' && *o<='9') u = (u << 3) + (u << 1) + (*o++ - '0');
    if (*o == '.')
    {
        ++o;
        while(*o >='0' && *o <='9') u = (u << 3) + (u << 1) + (*o ++  -'0');
    }
    return u;
}

// 10^7 * 10^4 = 10000


int main()
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    int n ;
    int q ;
    int s = 0;
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    n = readInt();
    q = readInt();
    
    for(int i= 0; i!=n;++i)
    {
        l[i] = readInt();//santimeter
        s += l[i];
    }
    
    int l_min = 1;
    int l_max = 12000000;
    
    while (l_min < l_max )
    {
        int lc = ( l_min + l_max + 1) >> 1 ;
        int lq = 0;
        
        for(int i = 0; i != n && lq < q; ++i)
            lq += l[i]/lc;
        
        if ( lq >= q )
            l_min = lc ;
        else 
            l_max = lc - 1;
    }
    s = 0;
    for(int i = 0; i != n && s < q; ++i)
        s += l[i] / l_min;
    
    if (s < q)
    {
        l_min = 0;
    }
    
    printf("%d.%02d\n", l_min/100, l_min%100);
}
