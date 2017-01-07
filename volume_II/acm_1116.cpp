

//1116. Piecewise Constant Function


#include <cstdio>
  
typedef unsigned char byte;

static const int offset_x = 32768;
static const int offset_y = 128;

byte       h[ 131072 ]; // 0 - means not defined

char in[1<<19];

char const* o;

char *w;

int readInt()
{
    unsigned u = 0, s = 0;
    while(*o && *o <= 32)++o;
    if (*o == '-')s = ~0, ++o; else if(*o == '+')++o;
    while(*o>='0' && *o <='9')u = (u << 3) + (u << 1) + (*o++ - '0');
    return static_cast< int >( ( u ^ s ) + !!s ) ;
}

void writeInt(int x, char c)
{
    *--w = c;
    c = 0;
    if (x < 0){ c = '-'; x = -x; }
    do *--w = x %10 + '0'; while(x/=10);
    if( c )
        *--w = '-';
}

int solve()
{
    o = in;
    w = in + sizeof(in);
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    int n;
    n = readInt();
    for(int i= 0; i != n; ++i)
    {
        unsigned int a, b, y;
        
        a = readInt() + offset_x;
        b = readInt() + offset_x;
        
        y = readInt() + offset_y;
        
        a += a + 1;
        b += b;
        
        //printf("a = %d\tb = %d\n",a,b);
        // [ a..b ]
        for ( ; a <= b; ++a)
            h[ a ] = y;
    }
    
    //printf("-------------\n");
    n = readInt(); // second
    for(int i = 0; i != n; ++i)
    {
        unsigned a,b,y;
        
        a = readInt() + offset_x;
        b = readInt() + offset_x;
        
        y = readInt() + offset_y;
        
        a += a + 1;
        b += b;
      //  printf("a = %d\t b = %d\n",a,b);
        for( ; a <= b; ++a)
        {
            // 1. if h[a] - not defined
            h[ a ] = 0;
        }
    }
    
    n = 0;
    for(int i = 131071, j = i; i>0;  i = j)
    {
        byte const c = h[i];
        while( j > 0 && c == h[j] )
            --j;
        
        if ( c )
        {
            // j+1 .. i  defined
            int y = c - offset_y;
            int a = ( j + 1 ) >> 1;
            int b = i >> 1;
            
            a -= offset_x ;
            b -= offset_x ;
            
            writeInt( y, ' ' ) ;
            writeInt( b, ' ' ) ;
            writeInt( a, ' ' ) ;
            
            ++n;
        }
    }
    
    writeInt( n, ' ' );
    
    //in[ sizeof( in ) - 1 ] = '\n';
    
    fwrite(w, 1, in + sizeof(in) - w, stdout);
    
    return 0;
}

int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    
    solve();
    
    return 0;
}
