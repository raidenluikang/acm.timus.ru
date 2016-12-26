


// acm.timus.ru 1039. Anniversary Party
// author solution: c_pp.
// date: 26.12.2016 14:11:40 :)

#include <cstdio>

static const unsigned N = 6666;

int rating [ N ];
int parent [ N ];
int head   [ N ];
int nxt    [ N + N ];
int dst    [ N + N ];
int dp     [ N ][ 2 ]; // dp[i][0] - maximum rating, when i-th employee does not attent, dp[i][1]- maximum rating, when i-th attent.
bool visited[N];

int n;

char in[1<<18];
char const* o;

void init_in()
{
    unsigned m;
    m = fread(in, 1, sizeof(in) - 4, stdin);
    in[m] = 0;
    o = in;
}

int readInt()
{
    unsigned u = 0;
    unsigned s = 0;
    while(*o && *o <= 32)++o;
    if (*o == '-') s = ~0u, ++o;
    else if (*o == '+') ++o;
    while(*o>=48) u = (u<<3) + (u << 1) + *o++ - 48;

    return (u ^ s) + !!s;
}

void readData()
{
    init_in();
    n = readInt();
    for(int i = 0; i != n; ++i)
    {
        rating[ 1 + i] = readInt();
        head[ 1 + i ] = 0;//no head.
        parent [1 + i] = 0;
        visited[ 1 + i ] = false;
    }

    {
        int k ,l, p = 0;
        for(;;)
        {
           l = readInt();
           k = readInt();
           if(k == 0 && l == 0) break;
           // K - is parent of L
           parent[ l ] = k;

           ++p;// a new edge (k,l)
           nxt  [ p ] = head[ k ];
           head [ k ] = p;
           dst  [ p ] = l; 
        }

        for(int i= 1; i <= n;++i)
        {
            if (!parent[i]) 
            {
                // so i - is child of presedent :)
                parent[i] = 0;
                int root = 0;
                ++p;
                nxt[p] = head[ root ];
                head[root] = p;
                dst[p] = i; 
            }
        }
    }

}

int max_(int x, int y){ return x > y ? x : y;}

void dfs( int v ) // current vertex 
{
    visited[ v ] = true;
    dp[v][0] = 0; // nothing attent, yet. 
    dp[v][1] = rating[v]; // attent only v-th employee.

    for(int h = head[v]; h != 0; h = nxt[h])
    {
        int u = dst[ h ];
        if ( ! visited[ u ] )
        {
            dfs( u );

            // dp[v][0] - v-th no attent 
            dp[ v ][ 0 ] += max_( dp[ u ][ 0 ], dp[ u ][ 1 ] );
            dp[ v ][ 1 ] += dp[ u ][ 0 ]; // if v-th attent, so u - child of v can not attent.
        }
    }
}

int solve()
{
    readData();
    dfs( 0 );
    printf("%d\n", dp[0][0]); 

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
