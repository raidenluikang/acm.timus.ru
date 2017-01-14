

// 1290. Sabotage

#include <cstdio>

static const int N = 25000 + 256;

int n;
int p[ N ];
int q[ N ];

char in[ N * 10 ];

struct scanner
{
    const char* o;
    scanner():o(in)
    {
        in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    }
    int readInt()
    {
        int u = 0;
        while(*o && *o <= 32)++o;
        while(*o >= '0' && *o <= '9') u = (u << 3) + (u << 1) + (*o++ - '0');
        return u;
    }
    
};
struct writer
{
    char *w ;
    writer(): w(in + sizeof(in)){}
    void writeInt(int u, char c)
    {
        *--w = c;
        do *--w = u % 10 + '0'; while(u/=10);
    }
    ~writer(){ if (w < in + sizeof(in)) fwrite(w,1,in+sizeof(in) - w, stdout);}
};

int solve()
{
    int m;
    scanner sc;
    writer  pw;
    n = sc.readInt();
    if (n==0)return 0;
    for(int i = 0; i!=n;++i)
    {
        p[ sc.readInt() ]++;
    }
    
    for(int i = N - 1, h = 0; i >= 0;--i)
    {
        int t      = p[ i ];
        p  [ i ]   = h;
        h         += t;
    };
    
    m = 0;
    q[m++] = n;
    for(int i = 1; i < N && p[i] > 0; ++i)
    {
        q[ m++ ] = p[ i ];
    }
    
    for(int i = 0; i < N; ++i)
        p[i] = 0;
    
    
    // 2-step
    for(int i= 0; i < m; ++i)
    {
        p[ q[ i ] ]++;
    }
    
    for(int i = N-1, h = 0; i >= 0;--i)
    {
        int t = p[ i ];
        p[ i ] = h;
        h    += t;
    }
    
    n = 0;
    q[n++] = m;
    for(int i= 1; i < N && p[i] > 0; ++i)
    {
        q[n++] = p[ i ];
    }
    
    for(int i= n-1; i >= 0;--i)
    {
        pw.writeInt(q[i], '\n');
    }
    return 0;
}
int main(int argc, char * argv[])
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt", "w",stdout);
#endif 
    
    solve();
    
    return 0;
}
