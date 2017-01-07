#include <cstdio>





char in[ 1 << 18 ];
char const* o;
char * w;


unsigned d[ 26000 ];
unsigned f[ 26000 ];
unsigned s[ 26000 ];

static
unsigned readInt()
{
    unsigned  u = 0;
    while(*o >='0' && *o <= '9') u = (u << 3) + (u << 1 ) + (*o ++ - '0');
    return u;
}

void writeInt(unsigned v)
{
    *--w = '\n';
    do *--w = v % 10 + '0'; while(v/=10);
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
    
    int m = readInt();
    int n = 0;
    while(true)
    {
        while(*o && *o <= 32)++o;
        if (*o == '\0' ||  o[0] == '-' && o[1] == '1')
            break;
        
        d[++n]  = readInt();
    }
    
    int h = 0; 
    for(int i = n; i > 0; --i)
    {
        while(h > 0 && d[ s[ h - 1 ] ] < d[ i ] )
        {
             f[ s[--h] ] = i;
        }
        
        s[ h++ ] = i;
    }
    
    while(h > 0 )
        f[ s [ -- h ] ] = 0;
    
    
    
    int p = n  + 1;
    for(int i = n; i >= m; --i)
    {
        int r = i;
        int l = i - m + 1;
        
        // find largest element d[l]..d[r]
        if (p > r)
        {
            p = r;
        }
        // f[l] < l --> so loop guaranted to end.
        while( f[ p ] >= l)
            p = f[ p ];
        
        //judge_assert(p >= l && p <= r);
        writeInt( d[ p ] );
    }
    
    fwrite(w, 1, in + sizeof(in) - w, stdout);
    
    return 0;
}
