

// acm.timus.ru 1097. Square Country 2

#include <cstdio>
#include <algorithm>

static const int L = 10000;
static const int M = 100;

struct build
{
    int prior ;
    int len   ;
    int row   ;
    int col   ;
};

build d[ M ] ;
int m ;
int len_square, len_build ;
int row_sorted[ M + 1 ];
int col_sorted[ M + 1 ];

char in[65536];
char const* o;

int readInt()
{
    int u = 0;
 
    while(*o && *o <= 32)++o;
    while(*o >= '0' && *o <= '9') u = (u << 3) + (u << 1) + (*o ++ - '0');
    
    return u;
}

int readData()
{
     o = in;
     in[fread(in,1,sizeof(in)-4,stdin)] = 0 ;
    
    len_square = readInt();
    len_build = readInt();
    m = readInt();
    
    for(int i= 0; i != m; ++i)
    {
        d[ i ].prior = readInt() ;
        d[ i ].len   = readInt() ; 
        d[ i ].row   = readInt() ;
        d[ i ].col   = readInt() ;
    }
    return 0;
}

struct cmp_build_col
{
    bool operator()(build const& lhs, build const& rhs)const
    {
        return lhs.col < rhs.col;
    }
};

struct invalid_pos
{
    int limit_pos;
    
    explicit invalid_pos(int l): limit_pos( l )
    {}
    
    bool operator()(int p)const{ return p >  limit_pos; } 
};

int solve()
{
    
    readData();
    
    // sort d[] array by columns
    std::sort(d, d + m, cmp_build_col());
    
    int nrow = 0;
    row_sorted[ nrow++ ] = 1;
    for(int i = 0; i != m; ++i)
        row_sorted[nrow++] = d[ i ].row + d[ i ].len;
    std::sort(row_sorted, row_sorted + nrow);
    nrow = std::unique(row_sorted, row_sorted + nrow) - row_sorted;
    
    // row + len_build - 1 > len_square --> invalid --> row > len_square - len_build + 1
    nrow = std::remove_if(row_sorted, row_sorted + nrow, invalid_pos(len_square - len_build + 1)) - row_sorted;
    
    
    int ncol = 0;
    col_sorted[ncol++] = 1;
    for(int i = 0; i != m; ++i)
        col_sorted[ncol++] = d[i].col + d[i].len;
    
    std::sort(col_sorted, col_sorted + ncol);
    ncol = std::unique(col_sorted, col_sorted + ncol) - col_sorted;
    ncol = std::remove_if(col_sorted, col_sorted + ncol, invalid_pos(len_square - len_build + 1)) - col_sorted;
    
    int ans = 255;
    
    for(int i = 0; i != nrow; ++i)
    {
        for(int j= 0; j != ncol; ++j)
        {
            int row = row_sorted[i];
            int col = col_sorted[j];
            
            int l_ans = 1;
            for(int k = 0; k != m; ++k)
            {
                // check d[k] intersects with square (row,col) (row + len_build-1, col + len_build-1)
                if (d[k].col + d[k].len - 1 >= col &&
                    col + len_build - 1 >= d[k].col &&
                    d[k].row + d[k].len - 1 >= row &&
                    row + len_build - 1 >= d[k].row)
                {
                    l_ans = std::max(l_ans, d[k].prior);
                }
            }
            
            ans = std::min(ans, l_ans);
        }
    }
    
    if (ans > 100)
    {
        puts("IMPOSSIBLE");
    }
    else
    {
        printf("%d\n",ans);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    
#ifndef ONLINE_JUDGE
    freopen( "input.txt", "r", stdin ) ;
    freopen( "output.txt", "w", stdout ) ;
#endif    
    
    solve();
    
    return 0;
}
