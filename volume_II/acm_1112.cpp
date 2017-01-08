

// acm.timus.ru 1112. Cover
#include <stdio.h>

char in[8192] ;
char const* o ;
char      * w ;

int pv[ 100 ] ;
int dp[ 100 ] ;
int a [ 100 ], b[100];
int n;


int readInt()
{
    int u = 0;
    int s = 0;
    while(*o && *o <= 32)++o;
    if (*o == '-')s = 1,++o; else if (*o == '+')++o;
    while(*o >='0' && *o <= '9') u = (u << 3) + (u << 1) + (*o++ - '0');
    return (s ? -u : u);
}

void writeInt(int u, char c)
{
    int v, n;
    
    if (u < 0)
    {
        *w++ = '-';
        u = -u;
    }
    
    v = u; n = 0; do ++n; while(v/=10);
    v = n;
    while(v-->0)w[v] = u % 10 + '0', u/=10;
    w += n;
    *w++ = c;
}

int max_(int x, int y){ return x > y ? x : y;}

void readData()
{
    o  = in;
    w  = in;
    
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    n = readInt();
    for(int i= 0; i != n; ++i)
    {
        a[i] = readInt();
        b[i] = readInt();
        if (a[i] > b[i])
        {
            int t = a[i]; a[i] = b[i]; b[i] = t;
        }
    }
}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    
    readData();
    
    //sort
    for(int i = 0; i != n; ++i)
    {
        for(int j= i+1; j != n; ++j)
        {
            if (a[i] > a[j])
            {
                int t = a[i]; a[i] = a[j]; a[j] = t;
                t = b[i]; b[i] = b[j]; b[j] = t;
            }
        }
    }
        
    
    //use DP: dp[i][0] -  when i-th interval removed, dp[i][1] - when i-th interval not removed.
   
    
    for(int i = 0; i != n; ++i)
    {
        dp[ i ] = 1;//itself :)
        pv[ i ] = -1;
        
        for(int j = 0; j != i; ++j)
        {
            if ( b[ j ] <= a[ i ] ) // so i and j doesnot intersect
            {
                if (dp[j]  + 1 > dp[i] )
                {
                    dp[i]  = 1 + dp[j] ;
                    pv[i]  = j;
                }
            }
        }
    }
    
    int last = -1;
    int ans  = 0 ;
    for(int i= 0; i != n; ++i)
    {
        if (dp[i] > ans)
        {
            ans = dp[i];
            last = i;
        }
    }
    
    writeInt(ans,'\n');
    
    int m = 0;
    //dp[m++] = last;
    for( ; last >= 0; last = pv[last])
        dp[m++]  = last;
    while(m-->0)
    {
        last = dp[m];
        writeInt(a[last], ' ');
        writeInt(b[last], '\n');
    }
    
    fwrite(in,1,w-in,stdout);
    return 0;
}
