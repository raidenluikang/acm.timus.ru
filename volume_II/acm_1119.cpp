// acm.timus.ru 1194. Handshakes


#include <cstdio>

static const int N = 20000 + 8;

char in[1<< 18];
char const* o;

int n, m, p, t;
int  x [ 256 ];
int  y [ 256 ];
bool a [ 256 ];
int ax[128];
int ay[128];
int na;
double d[256];

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
    
    n = readInt();
    m = readInt();
    
    p = 0;
    x[p]  = 0;
    y[p]  = 0;
    
    ++p;
    
    x[p] = n;
    y[p] = m;
    
    ++p;
    
    t = readInt();
    na = t;
    for(int i= 0; i != t; ++i)
    {
         x[p] = readInt();
         y[p] = readInt();

         ax[i] = x[p];
         ay[i] = y[p];

         ++p;
        
        x[ p ] =  x[ p - 1 ] - 1;
        y[ p ] =  y[ p - 1 ] - 1;
        ++p;
    }
    
    // sort (x,y)
    for(int i= 0; i < p ; ++i)
    {
        for(int j= i + 1; j < p; ++j)
        {
            if (x[i] > x[j] || (x[i] == x[j] && y[i] > y[j]))
            {
                t = x[i]; x[i] = x[j]; x[j] = t;
                t = y[i]; y[i] = y[j]; y[j] = t;
            }
        }
    }
    
    // remove duplicates
    t = p;
    p = 1;
    for(int i = 1; i  < t; ++i)
    {
        if (x[i] == x[p-1] && y[i] == y[p-1])
           ;
        else
        {
            
            x[ p ] = x[ i ];
            y[ p ] = y[ i ];
            ++p;
        }
    }
    
    
    // for i < j -->  x[i] < x[j] ||  x[i] == x[j] && y[i] < y[j]   not equal points
    for(int i = 0; i != p; ++i)
    {
        d[ i ] = x[ i ] + y[ i ];// distance from (0,0) --> to (x[i], y[i]) is equal to |x[i]| + |y[i]| = x[i] + y[i], because, x[i],y[i]>=0
    }
    
    for(int i = 0; i != p; ++i)
    {
        a[i] = false;
        for(int j = 0; j != na; ++j)
            a[i] |= (x[i] == ax[j] && y[i] == ay[j]);
    }
    
    const double sqrt_2 = 1.414213562;
    
    for(int i = 0; i != p; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            double h = (x[i] - x[j]) + (y[i] - y[j]); // x[i] >= x[j]  and y[i] >= y[j]
            
            if ( y[i] < y[j] )continue;
            
            if (a[i] && x[j] == x [ i ] - 1 && y[ j ] == y[ i ] - 1)
                h = sqrt_2;
            
            if (d[j] + h < d[ i ])
                d[i] = d[j] + h;
        }
    }
    
    unsigned ans = d[p-1] * 100  + 0.5 ;
    printf("%u\n",ans);
    
    return 0;
}
