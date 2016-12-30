
#include <cstdio>
 
char in  [ 65536 ];
char const* o;
  

int a[ 1024 ];
int b[ 1024 ];
bool visit[1024] ;
int que [ 1024 ] ;
int dist[ 1024 ] ;
int prv [ 1024 ];
int n; // number of bus
int n_q;

int nxt[ 2048 ] ;
//int dst[ 2028 ] ;
int head[2048 ] ;

static int readInt()
{
    int u = 0;
    while(*o && *o <= 32)++o;
    while(*o >= 48 && *o <= 57) u = (u << 3) + (u << 1) + (*o ++ - 48);
    return u;
}

int readData()
{
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    //1. n 
    n = readInt();
    for(int i = 1; i <= n; ++i)
    {
        a[i] = readInt();
        b[i] = readInt();
         
    }
        
    n_q = readInt();
    a[n+1] = readInt();
    b[n+1] = readInt();
    return 0;
}

int bfs()
{
    for(int i = 0 ;i != 1024; ++i)
    {
        visit[i] = false;
        prv[i]  = 0;
        dist[i] = 1024;
    }
    for(int i = 0; i != 2048; ++i) head[i] = 0;
    for(int i= 1 ; i <=n;++i)
    {
        // i = 1 : p = 2  and 3
        // i = 2 : p = 4  and 5 and etc.
        //++p;
        nxt[i] = head[a[i]];
        head[a[i]] = i;
        //dst[ p ]   = i;
        
        //++p;
        //nxt[p] = head[b[i]];
        //head[b[i]] = p;
    }
    int h = 0, t = 0;
    que[t++] = n + 1;
    
    visit[n+1] = true;
    dist[n+1] = 0;
    while( h < t )
    {
        int u = que[h++];
        int au = a[u];
        int bu = b[u];
        for(int e = head[au]; e != 0; e = nxt[e])
        {
            int v = e ;
            if (!visit[v])
            {
                visit[v] = true;
                dist[v] = 1 + dist[u];
                prv[v] = u;
                
                que[t++] = v;
            }
        }
        if (au != bu)
        {
           for(int e = head[bu]; e != 0; e = nxt[e])
           {
               int v = e;
               if (!visit[v])
               {
                   visit[v] = true;
                   dist[v] = 1 + dist[u];
                   prv[v] = u;
                   
                   que[t++] = v;
               }
           }
        }
    }
    
    int ans = 0;
    int deep = 1024;
    for(int i = 1; i <= n; ++i)
    {
        if (visit[i] && (n_q == a[i] || n_q == b[i]))
        {
            if ( deep > dist[ i ] )
            {
                ans = i;
                deep = dist[i];
            }
        }
            
    }
    return ans;
}

int writeData(int ans)
{
    if (ans == 0)
    {
        puts("IMPOSSIBLE");
        return 0;
    }
    
    int h = 0;
    int cur = ans;
    char * w = in + 16384;
    while(cur != n + 1)
    {
        ++h; // number of changes
        *--w = '\n'; 
        int u = cur;
        do *--w = u % 10 + '0'; while(u/=10);
        cur      = prv[cur];
    }
    //now number of changes
    *--w = '\n';
    do *--w = h % 10 + '0'; while(h/=10);
    fwrite(w, 1, in + 16384 - w, stdout);
    return 0;
}
int solve()
{
    int ans;
    readData();
    ans = bfs();
    writeData(ans);
    return 0;
}

int main()
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    
    solve();
    
    return 0;
}
