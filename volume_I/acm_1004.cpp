
#include <cstdio>
#include <cstring>

static const int mxi = 100000000;
static inline int min_(int x, int y){ return x < y ? x : y;}

int a[128][128];
int w[128][128];
int p[128][128];

int solve()
{
    int n,m;
    while(scanf("%d%d",&n,&m), n > 0)
    {
        
        for(int i = 0; i < n;++i)
        {
            for(int j = 0; j < n; ++j)
                p[ i ][ j ] = -1, w[i][j] = mxi;
            w[i][i] = 0;
        }
        
        for(int i = 0; i<m;++i)
        {
            int a,b,l;
            scanf("%d%d%d",&a,&b,&l);
            --a;
            --b;
            if (l < w[a][b])
            {
                w[a][b] = l;
                w[b][a] = l;
                p[a][b] = b;
                p[b][a] = a;
            }
            
        }
        
        memcpy(a, w, sizeof(w));
        
        for(int k = 0; k<n;++k)
        {
            for(int i = 0; i<n;++i)
            {
                for(int j = 0; j < n;++j)
                {
                    if (w[i][j] > w[ i ][ k ] + w[k][j])
                    {
                        w[  i ][ j ] = w[ i ][ k ] + w[k][j];
                        //if (p[i][k] == -1)printf("ERROR\n");
                        p[  i ][ j ] = p[ i ][ k ];
                    }
                }
            }
        }
        
        int ans_min = mxi;
        int ans_i = -1 , ans_j = -1, ans_k = -1;
        
        for(int i = 0; i < n; ++i)
        {
            for(int j = i+1; j < n; ++j)
            {
                if (a[ i ][ j ] == mxi)
                    continue;
                
                for(int k = 0; k < n ; ++k)
                {
                    if (j == k || i == k)continue;
                    
                    if (w[i][k] == mxi || w[j][k] == mxi)continue;
                    
                    if (p[ i ][ k ] == j || p[ j ][ k ] == i)continue;
                    
                    if ( a[ i ][ j ] + w[ j ][ k ] + w[ k ][ i ] < ans_min)
                    {
                        ans_min = a[ i ][ j ] + w[ j ][ k ] + w[ k ][ i ];
                        ans_i = i;
                        ans_j = j;
                        ans_k = k;
                    }
                }
            }
        }
        
        if (ans_min == mxi)
        {
            printf("No solution.\n");
            continue;
        }
        
       // printf("min = %d,  ans_i = %d, ans_j = %d, ans_k = %d\n", ans_min, 1+ans_i, 1+ans_j, 1+ans_k);
        // ans_i --> ans_j --> ans_k --> ans_i
        
        while(ans_i != ans_k)
        {
            printf("%d ", 1 + ans_i);
            ans_i = p[ans_i][ans_k];
        }
        while(ans_i != ans_j)
        {
            printf("%d ", 1 + ans_i);
            ans_i = p[ans_i][ans_j];
        }
        printf("%d\n",1+ans_i);
        
    }
    
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
