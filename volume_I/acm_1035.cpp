

// acm.timus.ru 1035. Cross-stitch


#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>

static const int N = 256;
static const int M = 256;

char in[ 131072 ];

unsigned char a[ N * M ][ 2 ] = { };
int s[ N * M ]      = { };
int p[ N * M ]      = { };
int rank[ N * M ]   = { };

int parent(int x)
{
    return (p[x] == x ? x : ( p[ x ] = parent( p[ x ] ) ) );
}


void join(int u, int v)
{
    u = parent(u);
    v = parent(v);
    if ( u != v )
    {
        if (rank[u] < rank[v])
        {
            p[ u ] = v;
        }
        else 
        {
            p[v] = u;
            if ( rank[u] == rank[v]) 
                ++ rank[u];
        }
    }
}
int nrow, ncol;

void readData()
{
    const char * o = in;
    in[ fread(in, 1, sizeof(in)- 4, stdin)] = 0;

    // read nrow 
    nrow = 0;
    while(*o && *o <= 32)++o;
    while(*o>=48) nrow = (nrow << 3)+ (nrow << 1) + (*o++ - 48);

    //read ncol
    ncol = 0;
    while(*o && *o <= 32)++o;
    while(*o >= 48) ncol = (ncol << 3) + (ncol << 1) + (*o++ - 48);
    while(*o != '\n')++o;
    ++o;    
    for(  int i = 0; i != N * M; ++i) 
        p[ i ] = i;

    // 
    for(int side = 0; side != 2; ++side )
    {
        for(int  row = 0; row <  nrow; ++row)
        {
            for(int col =  0; col <  ncol; ++col)
            {
                char c = *o++;
                int ul = col | (row << 8);
                int ur = ul + 1;
                int dl = ul + 256 ;
                int dr = dl + 1;

                if (c == 'X' || c == '\\')
                {
                    a[ ul ][ side ]++;
                    a[ dr ][ side ]++;
                    join(ul, dr);
                }

                if (c == 'X' || c == '/')
                {
                    a[ur][side]++;
                    a[dl][side]++;
                    join(ur, dl);
                }
            }
            ++o;//skip line break
        }
    }
    

}


void judge_assert(bool b){ if (!b)printf("%d\n",1/b);}

int minimum_path_cover()
{
    int ans = 0;
    //int max_a = 0;
    static const unsigned char matrix[5][5] = 
    {
        {0, 1, 2, 3, 4},
        {1, 0, 1, 2, 3},
        {2, 1, 0, 1, 2},
        {3, 2, 1, 0, 1},
        {4, 3, 2, 1, 0}
    };
    for( int i = 0; i != N * M ; ++i)
    {
        s[ parent( i ) ] += matrix[ a[ i ][ 0 ] ][ a[i][1] ];//abs( (int)a[ i ][ 0 ] - (int)a[ i ][ 1 ]);
    }
    for( int i = 0; i != N * M; ++i)
    {
        if( (a[i][0] || a[i][1]) && p[i] == i )
            ans += s[i] ? (s[ i ] / 2 ) : 1;
    }
    return ans;
}

int solve()
{
    readData();
    int r = minimum_path_cover();
    char * w = in + 16;
    *--w  = '\n';
    do *--w = r % 10 + '0'; while(r/=10);

    fwrite(w, 1, in + 16 - w, stdout);
    //printf("%d\n", minimum_path_cover());
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
