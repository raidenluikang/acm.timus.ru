

// acm.timus.ru 1041. Nikifor

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <functional>

static const unsigned N = 50;
static const unsigned M = 2000;
static const double zero = 0.0;

#ifdef _MSC_VER
#define J_ALIGN_P  __declspec(align(64))
#define J_ALIGN_S  
#else 
#define J_ALIGN_P  
#define J_ALIGN_S  __attribute__((aligned(8)))
#endif

J_ALIGN_P
unsigned cost[M] J_ALIGN_S;

J_ALIGN_P
double a[ M ][ N ] J_ALIGN_S; // coefficients of linear vectors
double a_len[ M ];

int kk[ N ];
int n, m, tot;

char in[ 1 << 21 ];
char const* o;

bool canIndepend(int x)
{
    int nz = 0;
    
    for(int j = 0; j != n; ++j)
       nz += !( fabs(a [ x ][ j ]) > zero );
    
    if ( nz == n )
        return false;

    for(int i = 0; i != tot; ++i)
    {     
        int y = kk[ i ];
        double sum  = 0.0 ;
        double len2 = a_len[ y ] ;

        for (int j = 0; j != n; ++j) 
        {
            sum +=  a[ x ][ j ] * a[ y ][ j ];
        }
            
        
        double tt = sum / len2;
        nz = 0;
        for (int j = 0; j != n; ++j)
        {
            a[ x ] [ j ] -= a[ y ][ j ] * tt;
            nz += !( fabs(a[ x ][ j ]) > zero );
        }
        if ( nz == n) // all zero 
            return false;
    }
    // recalc a_len[x]
    a_len[ x ] = 0.0;
    for(int j = 0; j != n; ++j)
    {
        a_len[ x ] += a[ x ][ j ] * a[ x ][ j ];
    }
    return true;
}


int solve()
{
    o = in;
    in[ fread(in, 1, sizeof(in)-4, stdin)] = 0;

    n = m = 0;
    while(*o >= 48) m = (m<<3) + (m<<1) + (*o++ - 48);
    ++o; // skip whitespace
    while(*o >= 48) n = (n<<3) + (n<<1) + (*o++ - 48);
    ++o;//skip line break;

    for(int i = 0; i != m; ++i)
    {
        for(int j = 0; j != n; ++j)
        {
            unsigned  s = 0;// if first element is negative, so to invert a sign of next elements.
            unsigned  u = 0;
            if (*o=='-')s = ~s , ++o;
            else if (*o == '+')++o;
            while(*o>=48) u = (u << 3) + (u<<1) + (*o++ - 48);
            ++o; //skip whitespace or line break. 

            a[i][j] = static_cast< int >( ( u ^ s ) + !!s ) ;

        }
  }

    // now read cost 
    for(int i = 0; i != m; ++i)
    {
        unsigned u = 0;
        while(*o >= 48)u = (u << 3) + (u << 1) + (*o++ - 48);
        ++o;//skip line break
        //cost[ i ] = u; // cost  in [1..15000]  so its value less than 2^16
        cost[i] = (u << 16) | (   i ); // we encode [0..15] bits of cost i, [16..31] bits actual cost value.
    }

    // now sort cost by descending order, note that if costs equal so id will sorted ascending order.
    std::sort(cost, cost + m );

    int na = 0;
    unsigned s = 0;
    int g[ N ];
    tot = 0;
    for(int i = 0; i != m && na < n; ++i)
    {
        int id = ( cost[ i ] & 0xFFFF );
        bool can = canIndepend(id);
        if ( can )
        {
            kk[ tot++] = id;
            g[ na++ ] = id ;
            s += (cost[ i ] >> 16);
        }
    }

    
    if (na < n)
    {
        puts("0");
    }
    else
    {
        // print 50 numbers  each is <= 2000 (4-digits) + 1 symbol for line break,
        // so total symbols = 50 * 5 = 250 <<<< 4096
        char *w = in + 16384;
        std::sort(g, g + n, std::greater<int>());
        for(int i = 0; i != n; ++i)
        {
            unsigned u = 1 + g[ i ];// indexing starts from 1.
            *--w = '\n';
            do *--w = u % 10 + '0'; while(u/=10);
        }

        *--w = '\n';
        do *--w = s % 10 + '0'; while(s/=10);

        fwrite(w, 1, in + 16384 - w, stdout); 
    }

   return 0;
}

int main(int argc, char * argv[])
{

#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    solve();

    return 0;
}
