

// acm.timus.ru 1042. Central Heating


// g[x][y] -- x master y kranni burashi mumkin bolsin. 
// ans[x] -- x master burasin
// //1 kranni burishlar soni: (g[0][0]&& ans[0]) ^ (g[1][0] && ans[1]) ^ ... ^ (g[n-1][0] && ans[n-1]) = true 
// agar g[x][y] - ni transparent qilsak, u holda uning manosi,  x-kranni, y-master buray oladimi boladi, va tenglama
//
// i  = 0..n-1
//   (g[i][0] & ans[0])^(g[i][1] & ans[1]) ^ ... ^(g[i][n-1] & ans[n-1]) = true 
// ga keladi 
// 

#ifdef _MSC_VER
#define J_ALIGN_P   __declspec(align(256))
#define J_ALIGN_S 
#else 
#define J_ALIGN_P  
#define J_ALIGN_S  __attribute__((aligned(8)))
#endif

#include <cstdio>
#include <cstring>

static const int N = 256;


J_ALIGN_P
bool g[ N ][ N ] J_ALIGN_S;

//note:  g[x][y] - true , if x-valve can turn by y-master, false otherwise.


J_ALIGN_P 
bool ans[ N ] J_ALIGN_S;


J_ALIGN_P
char in[ ( 1 << 18 ) ] J_ALIGN_S;
char const* o ;
//bool e_ ;

int n;
int n_ans;

static inline int readInt()
{
    while(*o && *o <= 32)
        ++o;
    
    if (*o == '-') 
    {
       ++o; 
       ++o; // skip '-1'
       return 0;
    }
    int u = 0;
    while(*o >= 48) u = (u<<3) + (u << 1) + (*o ++ - 48);
    return u;
}

void readData()
{
    o = in;
    in[fread(in, 1, sizeof(in)-4, stdin)] = 0;
    
    n = readInt();
    
    for(int x = 0; x != n; ++x)
    {
        while(int u = readInt())
            g[u-1][x] = true;
        
    }
}

bool gauss()
{
    // we have system equation n x n
    // g[i][j] - coefficients , i = 0..n-1, j = 0..n-1 
    // g[i][n] - free part - must be true 
    for(int i = 0; i != n; ++i)
    {
        //BIT_SET( g[ i ], n );
        g[i][n] = true;
    }


    for(int i = 0; i != n; ++i)
    {
        int j = i ;
        
        while( j != n && !g[j][i]) //! BIT_TEST( g[ j ], i) )  
            ++j;
        
        if ( j == n )
            return false;
        
        if (j > i) // swap they 
        {
            bool tmp[ N ]; // 32 --- sizeof(u32) * 8 = 4*8
            memcpy( tmp,    g[ i ], sizeof(tmp));
            memcpy( g[ i ], g[ j ], sizeof(tmp));
            memcpy( g[ j ], tmp,    sizeof(tmp));
        }

        // now: g[i][i] - is true 
        // need xor this value to all others 
        for(int j= i + 1; j != n; ++j)
        {
            bool b = g[j][i];
            for(int k = i + 1; k <= n; ++k)
               g[ j ][ k ] ^= g[ i ][ k ] & b;
        }
    } 

    // ans[n-1] = g[n-1][n]
    // 
    //memset(ans, 0, sizeof(ans));
     for(int i = 0; i != n; ++i)
        ans[ i ] = g[i][n];//BIT_TEST(g[i],n);

    for(int i = n ; i-->0; )
    {
        if ( ans[ i ])
        {
            //ans[ i ] = true;

            for(int j = 0; j != i; ++j)
            {
                ans[ j ] ^= g[ j ][ i ]; // !!BIT_TEST( g[j], i ) ;
            }
        }
        else
        {
            //ans[i] - 0 --> already zero :)

        }
    }
    return true;

}

int solve()
{

    readData();

    if (gauss())
    {
        char *w = in + 4096;
        //*--w = '\n';
        for(int i = n ; i > 0; --i)
        {
            if (ans[i-1])
            {
                unsigned u = i;
                *--w = ' ';
                do *--w = u%10 + '0'; while(u/=10);
            }
        }
        in[4095] = '\n';
        fwrite(w, 1, in + 4096 - w, stdout);
    }
    else
    {
        puts("No solution");
    }
    return 0;
}

int main(int argc, char* argv[])
{

#ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
#endif


    solve();


    return 0;
}
