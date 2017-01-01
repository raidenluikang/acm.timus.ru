

// acm.timus.ru 1065. Frontier



#include <cstdio>
#include <cstring> 
#include <cmath>

// 3 <= N <= 50
// 0 <= M <= 1000

static const unsigned N = 50;
static const unsigned M = 1000;

template<typename T> T max_(T a, T b){ return a > b ? a : b;}
template<typename T> T min_(T a, T b){ return a < b ? a : b;}

struct point
{
    int x;
    int y;
};

point operator - (point a, point b){
    point c = {a.x - b.x, a.y - b.y};
    return c;
}
point operator + (point a, point b){
    point c = {a.x + b.x, a.y + b.y};
    return c;
}
int operator * (point a, point b){
    return a.x * b.x + a.y * b.y;
}
int operator ^ (point a, point b){
    return a.x * b.y - a.y * b.x;
}
double dist(point a, point b)
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt( dx * dx + dy * dy + .0);
}

int n,m;
point mouments[M];
point guards[ N ];
double d[ N ][ N ];
double dg[ N ][ N ];

char in[ 1 << 16 ];
char const* o;

int readInt()
{
    unsigned u = 0, s = 0;
    
    while( *o && *o <= 32 )
        ++o;
    
    if ( *o == '-' ) s = ~0, ++o; else if ( *o == '+' ) ++o ;
    
    while( *o >= 48 && *o <= 57 ) u = ( u << 3 ) + (u << 1) + ( *o ++ - 48 ) ;
    
    return static_cast<int>( ( u ^ s ) + !!s );
}

int readData()
{
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    n = readInt();
    m = readInt();
    
    
    for(int i = 0; i != n;++i)
    {
        guards[i].x = readInt();
        guards[i].y = readInt();
    }
    
    for(int i=0; i!= m; ++i)
    {
        mouments[i].x = readInt();
        mouments[i].y = readInt();
    }
    
    return 0;
}

int solve()
{
    
    for(int i = 0; i != n; ++i)
    {
        for(int j = 0; j != n; ++j)
            d[ i ][ j ] = dist( guards[ i ], guards[ j ]);
    }
    
    for(int i = 0; i !=n;++i)
    {
        for(int j = 0; j != n; ++j)
            dg[i][j] = 1.0E+12;
        
        dg[ i ][ i ] = 0.0;
    }
    
    for(int i= 0; i != n; ++i)
    {
        // find dg[i][j]  j = 0 .. n
        if (m == 0)
        {
            for(int j = 0; j != n; ++j)
                dg[i][j] = d[i][j];
        }
        else
        {
            int k = 0;
            point u = mouments[0] - guards[i]; 
            
            for(int j = 1; j != m; ++j)
            {
                point v = mouments[j] - guards[i]; 
                if (u.x * v.y - u.y * v.x > 0)
                {
                    u = v;
                    k = j;
                }
            }
            
            for(int j = 1; j != n; ++j)
            {
                int k = ( i + j ) % n;
                point v = guards[k] - guards[i]; 
                if (u.x * v.y - u.y * v.x > 0)
                {
                    dg[ i ][ k ] = d[ i ][ k ];
                }
                else
                {
                    break;
                }
            }
        }
    }
    
    
    //Ford Bellman
    for(int len = 2; len != n; ++len)
    {
        for(int i= 0; i != n; ++i)
        {
            // dg[ i ][ ( i + len ) % n]  
            int ii = (i + len ) % n;
            
            if ( fabs( dg[ i ][ ii ] - d[ i ][ ii ] ) < 1.0E-10 )
                continue;
            
            for(int l = 1; l != len; ++l)
            {
                int il = ( i + l ) % n;
                dg[i][ii] = min_(dg[i][ii], dg[i][il] + dg[il][ii]);
            }
            
        }
    }
    
    double ans = 1.0E+12;
    for(int i = 0; i != n; ++i)
    { 
        for(int j = i + 1; j != n; ++j)
        {
            for(int k = j + 1; k != n; ++k)
            {
                point u = guards[j] - guards[i];
                point v = guards[k] - guards[i];
                if (!(u ^ v))continue;
               ans = min_(ans, dg[i][j] + dg[j][k] + dg[k][i]);
            }
        }
    }
    
    printf("%.2lf\n", ans);
        
    
    return 0;
}

int main(int argc, char* argv[])
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    
    readData();
    solve();
    
    return 0;
}
