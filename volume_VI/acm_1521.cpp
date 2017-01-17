
#include <cstdio>

static const int N = 100000;
static const int SH = 17;
static const int SH_N  = 1 << SH;






int tree[ SH_N * 2 + 2 ];

void add(int x, int d)
{
    x += SH_N;
    while(x > 0)
    {
        tree[x] += d;
        x >>= 1;
    }
}

int kth_max(int x)
{
    int result = 1;
    while(result <=  SH_N)
    {
        result += result;
        if (tree[result] < x)
        {
            x -= tree[result];
            result ++;
        }
    }
    return result - SH_N;
}


int ans[N];

char out[1<<20];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    
#endif
    
    int n,k;
    scanf("%d%d",&n,&k);
    
    for(int i = 1; i <= n; ++i)
        add(i,1);
    
    int p = 1;
    k--;
    for(int i = 0, m = n, j; i < n;++i)
    {
        p = 1 + (p + k - 1 ) % m;
        j = kth_max( p );
        ans[i] = j;
        m--;
        add(j,-1);
    }
    
    //print ans
    {
        char * w = out + sizeof(out);
        char c = '\n';
        
        for(int i =n-1; i>=0;--i)
        {
            int u = ans[i];
            *--w = c;
            do *--w = u % 10 + '0'; while(u/=10);
            c = ' ';
        }
        
        fwrite(w, 1, out + sizeof(out) - w, stdout);
    }
}
   
