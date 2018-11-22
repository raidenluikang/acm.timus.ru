

#include <cstdio>
#include <cstddef>
#include <cstring>
#include <algorithm>


static const size_t N = 256;

bool g[N][N];
bool used[N];
bool visit[N];
int match[N];
int p[N];
int base[N];
int que[N];
bool blossom[N];

int n;

char in[1<<17];
struct scanner
{
	char const* o;
	scanner(): o(in){ load() ; }
	void load(){  in[fread(in,1,sizeof(in)-4,stdin)] = 0;}
	unsigned readInt(){ 
		unsigned u = 0;
		while(*o && *o <= 32)++o;
		while(*o>='0' && *o<='9') u = (u << 3) + (u << 1) + (*o++ - '0');
		return u;
	}
};
struct writer
{
	char * w;
	char t[20];
	writer(): w(in){}
	~writer(){ flush(); }
	void flush(){ if ( w!=in)fwrite(in, 1, w - in, stdout), w = in;}
	void writeInt(unsigned u, char c)
	{
		int i = 20;
		do t[--i] = u % 10 + 48 ; while(u/=10);
		do *w++ = t[i++] ; while(i!=20);
		*w++ = c;
	}
};

void readData()
{
	scanner sc;
	n = sc.readInt();
	//scanf("%d",&n);
	int a,b;
	int m = 0;
	while( a = sc.readInt(), b = sc.readInt() )
	{
		g[a][b] = true;
		g[b][a] = true;

		++m;
	}

	while (m > 20050);
}


static int lca(int  match[], int  base[], int  p[], int a, int b) 
{
	//bool * used = visit;
  //  boolean[] used = new boolean[match.length];
    memset(visit, 0, sizeof( visit) ) ;
    
    while (true) 
    {
	      a = base[ a ] ;

	      visit[ a ] = true ;
	      
	      if (match[ a ] == -1) 
	      	break;
	      
	      a = p[ match[ a ] ] ;
    }

    while (true) 
    {
	      b = base[ b ];
	      
	      if (visit[ b ]) return b;

	      b = p[ match[ b ] ] ;
    }

}


static void markPath(int match[], int base[], bool blossom[], int p[], int v, int b, int children) 
{
    for (    ; base[ v ] != b; v = p[ match[ v ] ] ) 
    {
        blossom[ base[ v ] ] = blossom[ base[ match[ v ] ] ]  = true;
        
        p[ v ] = children;
        
        children = match[ v ];
    }
}



static int findPath( int match[], int p[], int root) 
{
    //int n = graph.length;
    //boolean[] used = new boolean[n];
    //Arrays.fill(p, -1);
    memset(p, 0xFF, sizeof(*p) * N );
    memset(used, 0, sizeof(used));
    
    //int[] base = new int[n];
    //std::iota(base, base + n, 0);
    for(int i= 1; i<=n;++i)
    	base[i] = i;

    used[ root ] = true;
    
    int qh = 0;
    int qt = 0;
    //int[] q = new int[n];
    
    int *q = que;
    
    q[qt++] = root;
    
    while (qh < qt) 
    {
      int v = q[ qh++ ];

      for (int i= 1; i <=n;++i ) 
      {
      	  //if (!g[v][i])continue;
      	  int to = i;

          if ( !g[v][to] || base[v] == base[to] || match[ v ] == to) 
          	   continue;

          if ( to == root || ( match[ to ] != -1 && p[ match[ to ] ] != -1 ) ) 
          {
	          int curbase = lca( match, base, p, v, to);
	          //boolean[] blossom = new boolean[n];
	          memset(blossom, 0, sizeof(blossom));

	          markPath(match, base, blossom, p, v, curbase, to);
	          markPath(match, base, blossom, p, to, curbase, v);
	          
	          for (int i = 1; i <= n; ++i)
	          {
	            if ( blossom[ base[ i ] ] ) 
	            {
	                base[ i ] = curbase;

	                if ( ! used[ i ]) 
	                {
	                   used[ i ] = true;
	                   q[ qt++ ] = i;
	                }
	            }
	          }
          } 
          else if (p[to] == -1) 
          {
	          p[ to ] = v;

	          if (match[to] == -1)
	            return to;
	          
	          to = match[ to ];
	          
	          used[ to ] = true;
	          
	          q[ qt++ ] = to;
          }
      }
    }
    return -1;
}





static int maxMatching() 
{
    //int n = graph.length;
   // int[] match = new int[n];
    //Arrays.fill(match, -1);
    //int[] p = new int[n];
    memset( match, 0xFF, sizeof( match ) ) ;

    for (int i = 1; i <= n; ++i) 
    {
	      if (match[ i ] == -1) 
	      {
	        
		        int v = findPath ( match, p, i ) ;
		        
		        while ( v != -1 ) 
		        {
			          int pv = p[ v ];
			          int ppv = match[pv];
			          match[v] = pv;
			          match[pv] = v;
			          v = ppv;
		        }
	      }
    }

    int matches = 0;
    for (int i = 1; i <= n; ++i)
      if (match[ i ] != -1)
        ++matches;
    return matches / 2;
  }



int solve()
{
	readData();

	int c = maxMatching();

	//printf("%d\n",c*2);
	writer pw;
	pw.writeInt(c*2, '\n');

	memset(used, 0 , sizeof(used));
	for(int i= 1; i<=n;++i)
	{
		if (match[i] != -1)
		{
			int to = match[i];
			if (used[to] || used[i])continue;
			used[ to ] = true;
			used[ i ] = true;
			pw.writeInt(i, ' ');
			pw.writeInt(to, '\n');
			//printf("%d %d\n", i, to);
		}
	}

	return 0;
}
int main(int argc, char * argv[])
{

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif 

	solve();

  	return 0;
}
