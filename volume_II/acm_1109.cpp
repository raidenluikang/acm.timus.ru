//1109. Conference

#include <cstdio>
#include <cstring>


static const int N = 1024;

char in[ 1 << 23 ];
struct scanner
{
  const char* o;
  scanner(): o(in)
  {
      in[fread(in,1,sizeof(in)-4,stdin)] = 0;
  }
  int readInt()
  {
      int u= 0;
      while(*o && *o<=32)++o;
      while(*o >='0' && *o <='9') u = (u << 3) + (u << 1) + (*o++ - '0');
      return u;
  }
};

struct edge
{
    int next;
    int v;
};

edge edges[ N * N ];
bool visited[N + N];
int match[N + N];
int adj[N+N];
int n ;
int m ;
int k ;

bool find(int u)
{
    for(int e = adj[u]; e != 0; e = edges[e].next)
    {
        int v = edges[e].v;
        if (!visited[v])
        {
            visited[v] = true;
            if (match[v] == -1)
            {
                match[u] = v;
                match[match[u]] = u;
                return true;
            }
            else
            {
                find(match[v]);
                if (match[match[v]] != v)
                {
                    match[u] = v;
                    match[match[u]] = u;
                    return true;
                }
            }
        }
    }
    
    return false;
}
	
int solve()
{
    scanner sc;
    n = sc.readInt();
    m = sc.readInt();
    k = sc.readInt();
    //scanf("%d%d%d",&n,&m,&k);
    
    
    for(int i = 1; i <= k;++i)
    {
        int a,b;
        //scanf("%d%d",&a, &b);
        a = sc.readInt();
        b = sc.readInt();
        b += n ;
        
        edges[i+i-1].v    = b;
        edges[i+i-1].next = adj[a];
        adj[a] = i + i-1;
        
        edges[i+i].v = a;
        edges[i+i].next = adj[b];
        adj[b] = i + i;
    }
    
    int ans = n + m;
    
    for(int i= 0; i< N + N; ++i)
        match[i] = -1;
    
    memset(visited, 0, sizeof(visited));
    
    for(int i = 1; i <= n + m; ++i)
    {
        if ( match[i] == -1)
        {
            memset(visited,0,sizeof(visited));
            find(i);
            if (match[i] != -1)
                --ans;
        }
    }
    printf("%d\n",ans);
    
    return 0;
}
int main(int argc, char * argv[])
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin ) ;
    freopen("output.txt", "w", stdout ) ;
#endif     
    
    solve();
    return 0;
}
