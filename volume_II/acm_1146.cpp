#include <cstdio>
#include <cstring>

static int max_(int a,int b){ return a > b ? a : b; }


char in[1<<16];
char const* o;
signed char M[100][100];
int N;
int dp[ 128 ];

static
signed char readInt()
{
    unsigned char u = 0, s = 0;
    //while(*o && *o <= 32)++o;
    if (*o == '-') s = 0xFF, ++o; else if (*o == '+')++o;
    while(*o >='0' && *o <= '9') u = (u << 3) + (u << 1 ) + (*o ++ - '0');
    ++o;
    return static_cast<signed char>( ( u ^ s ) + !!s);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    //scanf("%d",&N);
    N = readInt();
    
    //memset(M, 0xFF, sizeof(M));
    for(int i = 0;i < N;++i)
        for(int j = 0;j <  N;++j)
           M[i][j] = readInt(); //scanf("%d",&M[i][j]);
    
    bool neg = true;
    int ans = M[0][0];
    
    for(int i = 0; i != N; ++i)
    {
        for(int j= 0; j!=N; ++j)
        {
            neg = neg && M[i][j] <= 0;
            ans = max_(ans, M[i][j]);
        }
    }
    if (neg)
    {
        printf("%d\n",ans);
        return 0;
    }
    
    for(int i= 0; i < N; ++i)
    {
        memset(dp, 0, sizeof( dp ));
        
        // dp[k] = M[j][k],  j = i..n-1
        for(int j = i; j < N; ++j)
        {
            int s;
            s = dp[ 0 ] += M[j][0];
            ans = max_(ans, dp[0]);
            
            for(int k = 1; k < N; ++k)
            {
                dp[k] += M[j][k];
                s = max_(0, s) + dp[k];
                ans = max_(s, ans);
            }
        }
    }
    
     printf("%d\n",ans);
    
     
    return 0;
}
