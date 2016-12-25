

//acm.timus.ru 1018. Binary Apple Tree

#include <cstdio> // fread/fwrite  printf scanf
#include <cstring> // memset, memcpy

#ifdef _MSC_VER 

#define JUDGE_ALIGN_P   __declspec(align(64))
#define JUDGE_ALIGN_S    

#else 

#define JUDGE_ALIGN_P   
#define JUDGE_ALIGN_S __attribute__((aligned(64)))

#endif

static const unsigned N = 108;

JUDGE_ALIGN_P
int w [ N ][ N ] JUDGE_ALIGN_S;

JUDGE_ALIGN_P
bool g[ N ][ N ] JUDGE_ALIGN_S;

JUDGE_ALIGN_P
int dp[ N ][ N ] JUDGE_ALIGN_S;

JUDGE_ALIGN_P
char in[ 262144 ] JUDGE_ALIGN_S;

JUDGE_ALIGN_P
bool visited[N] JUDGE_ALIGN_S;

JUDGE_ALIGN_P 
int edges[ N ] JUDGE_ALIGN_S;

const char* o   ;
unsigned n, q   ;

void init_in()
{
    unsigned m;
    m = fread(in, 1, sizeof(in)-4, stdin);
    in[m] = '\0';
    o = in;
}
unsigned readInt()
{
    unsigned u = 0;
    while(*o && *o <= 32)++o;
    while(*o >= 48) u = (u<<3) + (u<<1) + *o++ - 48;
    return u;
}

void dfs(unsigned v)
{
    visited[ v ] = true ;
    edges[ v ]   = 0    ;
    // find dp[v][i] , i = 1.. q 
    for(unsigned u = 1; u <= n; ++u )
    {
        if ( g[ v ][ u ] )
        {
            if (visited[u]) // so u - parent of v 
            {
                g[ v ][ u ] = false;
                w[ v ][ u ] = 0;
            }
            else // u - child of v 
            {
                dfs( u );
                edges[v] += 1 + edges[ u ]; // edge from (v,u) + number of edges of u vertex.
            }
        }
    }

    
    int const ni = edges[ v ];
    
    //printf("edges[%d] = %d\n",v,ni);
    dp[ v ][ 0 ] = 0; // save 0 edges, i.e. remove all edges, gives 0 apples.
    for(unsigned u = 1; u <= n; ++u)
    {
        if ( g[ v ][ u ]) // u - child of v 
        {
            int const apple_u = w[ v ][ u ]; // number of apples in (v,u) edge.
            
            for(int i = ni; i > 0; --i)
            {
                for(int k = 0; k < i; ++k)
                {
                    // apple_u  -> (v,u) edge apples 
                    // dp[u][k] -> maximum number of apples, when presave k-edges from u vertex
                    // dp[v][i-k-1] -> maximum number of apples, when presave i - k - 1 edges from v vertex, and 
                    //              this value doesn't contain apples from u vertex, because, i -> ni .. 1 decreasing order

                    int const apples = apple_u + dp[ u ][ k ] + dp[ v ][ i - k - 1 ] ;
                    if (apples > dp[v][i])
                       dp[ v][ i ] = apples;
                }
            }
        }
    }
}

int solve()
{
    memset(w, 0, sizeof(w));
    memset(g, 0, sizeof(g));
    memset(dp,0, sizeof(dp));
    memset(visited, 0, sizeof(visited));

    init_in();
    n = readInt();
    q = readInt();

    for(int i = 1; i <= n - 1; ++i)
    {
        unsigned int a, b, c;
        a = readInt();
        b = readInt();
        c = readInt();
        
        w[ a ][ b ] = c;
        w[ b ][ a ] = c;

        g[ a ][ b ] = true;
        g[ b ][ a ] = true;
    }
    dfs( 1 );

    printf("%d\n", dp[1][q]);
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
