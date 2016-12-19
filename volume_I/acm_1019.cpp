

// acm.timus.ru 1019. Line Painting.

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

#ifdef _MSC_VER  // Visual Studio C/C++

#define JUDGE_ALIGNED_PREF  __declspec(align(128))
#define JUDGE_ALIGNED_SUFF  

#else 
 
#define JUDGE_ALIGNED_PREF   
#define JUDGE_ALIGNED_SUFF  __attribute__((aligned(128)))

#endif

//crash divide to zero.
void judge_assert(bool b){ if (!b)printf("%d",1/b);}

// n <= 10^5     "1 2 3 4 5 6\n" : 12 symbols: total symbols = 10^5*12 = 1.2*10^6.
JUDGE_ALIGNED_PREF
char in[ ( 1 << 19 ) ] JUDGE_ALIGNED_SUFF;

JUDGE_ALIGNED_PREF
const char* o  JUDGE_ALIGNED_SUFF;


JUDGE_ALIGNED_PREF
char out[128] JUDGE_ALIGNED_SUFF;

JUDGE_ALIGNED_PREF
char * w  JUDGE_ALIGNED_SUFF;


static const unsigned N = 10128;

JUDGE_ALIGNED_PREF
char segment_tree[ N << 2 ] JUDGE_ALIGNED_SUFF ;

struct node
{
    unsigned a ;
    unsigned b ;
    char color ;
} nodes[ 5008 ];

unsigned xs[ N ];
unsigned nx;

void writeInt(unsigned u, char c)
{
    unsigned v = u, n = 0;
    do ++n; while(v/=10);
    v = n;
    while(v-->0)w[v] = u%10 + '0', u/=10;
    w += n;
    *w++ = c;
}

unsigned readInt()
{
    unsigned u = 0;
    while(*o && *o <= 32)++o;
    while(*o>=48) u = (u<<3) + (u<<1) + *o++ - 48;
    return u;
}
char readChar()
{
    while(*o && *o <= 32)++o;
    return *o++;
}

int solve()
{
    unsigned n;
    n = fread(in, 1, sizeof(in)-4 , stdin);
    in[n] = '\0';
    o = in;
    w = out;

    n = readInt();
    nodes[ 0 ].a = 0 ;
    nodes[ 0 ].b = 1000000000;
    nodes[ 0 ].color = 'w';
    
    
    nx = 0;
    xs[ nx++ ] = nodes[0].a;
    xs[ nx++ ] = nodes[0].b;
  
    for(unsigned i = 1; i != n+1; ++i)
    {
        nodes[ i ].a     = readInt();
        nodes[ i ].b     = readInt();
        nodes[ i ].color = readChar();

    
        xs[ nx++ ] = nodes[ i ].a;
        xs[ nx++ ] = nodes[ i ].b;
    }

    std::sort(xs, xs + nx);//sort coordinates
    nx = std::unique(xs, xs + nx) - xs; // remove dublicates.
    
    std::fill(segment_tree, segment_tree + sizeof(segment_tree), '\0');
    
    for(unsigned i = 0; i != n + 1; ++i)
    {
        unsigned a = nodes[i].a;
        unsigned b = nodes[i].b;
        char color = nodes[i].color;

        unsigned l =   std::lower_bound(xs, xs + nx, a ) - xs;
        unsigned r =   std::lower_bound(xs, xs + nx, b ) - xs;
        l = l + l  + 1; // a = 100 : pos: 10  , means 10 less arguments + and 2*a value: total 10*2+1  
        r = r + r ; 
        unsigned pl = l + nx + nx;
        unsigned pr = r + nx + nx;
        
        // 2^14 > N  &&  2^13 < N , so 14 - height of segment tree.
        for(unsigned h = 15; h > 0; --h)
        {
            unsigned p = pl >> h;
            if (char c = segment_tree[ p ])
            {
                segment_tree[ p << 1 ] = c;
                segment_tree[(p << 1 ) | 1 ] = c;
                segment_tree[p] = '\0';
            }

            p = pr >> h;
            if (char c = segment_tree[p])
            {
                segment_tree[p << 1] = c;
                segment_tree[(p<<1)|1] = c;
                segment_tree[p] = '\0';
            }
        }

        for( ++pr; pl < pr; pl >>= 1, pr >>= 1)
        {
            if (pl & 1) segment_tree[pl++] = color;
            if (pr & 1) segment_tree[--pr] = color;
        }
    }

    for(unsigned i = 0; i != nx+nx; ++i)
    {
        if (char c = segment_tree[ i ])
        {
            segment_tree[ i << 1] = c;
            segment_tree[(i << 1) | 1 ] = c;
            segment_tree[ i ] = '\0';
        }
    }
    
#ifndef ONLINE_JUDGE
    //debug
    for(unsigned i = 0; i != nx + nx; ++i)
    {
        unsigned a = xs[ i >> 1 ];
        char color = segment_tree[i + nx];
        if (color != 0)
        {
          printf("x: %u\tcolor: %c\n",a,color );   
        }
        //judge_assert(color != '\0');
      //  
    }
#endif

    unsigned max_dif = 0, max_start = 0, max_end = 0;
    for(unsigned i = 0, j = 0; i != nx + nx; i = j)
    {
           while( j != nx + nx && segment_tree[nx + nx + i] == segment_tree[nx + nx + j])
              ++j;

           // [i, j) - interval painting same color.
           if (segment_tree[nx + nx + i] == 'w')
           {
                unsigned i_0 =  i;//i> 0  && !(xs[ i - 1 ] & 1)  ? i - 1 : i ;
                unsigned i_1 =  j-1;//( xs[j-1] & 1 ) ? j  : j-1;
                unsigned a = xs[ i_0 >> 1]; // real coordinates
                unsigned b = xs[ i_1 >> 1]; // real coordinates
                unsigned dif = b - a;
                if (dif > max_dif)
                {
                    max_dif = dif;
                    max_start = a;
                    max_end = b;
                }
                
           }   
    }


     //printf("%u %u\n", max_start >> 1, max_end >> 1);
    writeInt(max_start,' ');
    writeInt(max_end, '\n');
    fwrite(out, 1, w - out, stdout);
    return 0;
}


int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    
    return 0;
}
