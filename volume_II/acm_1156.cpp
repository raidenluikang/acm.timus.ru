

// 1156. Two Rounds

#include <cstdio>

struct scanner
{
    char const* o;
    char in[16384];
    
    void init()
    {
        o = in;
        in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    }
    int readInt()
    {
        int u = 0;
        while(*o && *o <= 32)++o;
        while(*o >='0') u = (u << 3) + (u << 1) + (*o++ -'0');
        return u;
    }
}sc;

struct writer
{
    char * w;
    char out[4096];
    writer() : w(out + sizeof(out)){}
    
    void write(int u, char c)
    {
        *--w = c;
        do *--w = u % 10 + '0'; while(u/=10);
    }
    void flush()
    {
        fwrite(w, 1, out + sizeof(out) - w, stdout);
    }
}pw;

int n, level;
int v  [ 128  ];// v[i] = 0 - not defined yet, +1 - if it's given first tour , +2 - if second tour
bool g [ 128 ][ 128 ];
int que[128];
struct node
{
    int id_white ;
    int id_black ;
    
    int n_white ;
    int n_black ;
}
nodes[ 128 ];

unsigned char dp[ 128 ][ 64 ][ 64 ];

int readData()
{
    int m;
    sc.init();
    
    n = sc.readInt();
    m = sc.readInt();
    
    for(int i= 0; i != m; ++i)
    {
        int x,y;
        x = sc.readInt();
        y = sc.readInt();
        g[x][y] = true;
        g[y][x] = true;
    }
    return 0;
}


int bfs()
{
    int h, t, id;
    level = 0;
    
    id = 4;
    
    for(int i = 1; i <= n + n ;++i)
    {
        if ( v[ i ] == 0)
        {
            ++level;
            
            nodes[ level ].id_white = id ;
            nodes[ level ].id_black = id + 1;
            nodes[ level ].n_white  = 0 ;
            nodes[ level ].n_black  = 0 ;
            
            v [ i ] =  id ; // id and id + 1 
             
            id += 2;
            
            h = 0 ;
            t = 0 ;
            que[ t++ ] = i;
            
            while( h < t )
            {
                int u = que[ h++ ];
                
                ( v[ u ] & 1) ? nodes[level].n_black++ : nodes[level].n_white ++; 
                
                for(int j = 1; j <= n + n; ++j)
                {
                    if (g[ u ][ j ] ) // u and j  can't put together.
                    {
                        if ( v[ j ] == 0 )
                        {
                            v [ j ] = v[ u ] ^ 1; // we put 4 if j - is identical with i, 5 - if can't put together
                            
                            que[ t++ ] = j;
                        }
                        else if ( v [ j ] == v[ u ] ) // if u and j already has id, and they are equal, so impossible to make problems.
                        {
                            //puts("IMPOSSIBLE");
                            return 0;
                        }
                    }
                }
            }
            
            if (nodes[level].n_black > n || nodes[level].n_white > n)
                return 0;
            
        } // end if v[i] == 0
    } // end for i = 1..n + n
    
    return 1;
}

int dp_calc()
{
    dp[0][0][0] = 0xFF;
    
    for(int l = 1; l <= level; ++l)
    {
        int nw = nodes[ l ].n_white;
        int nb = nodes[ l ].n_black;
        
        for(int i = 0; i + nw <= n; ++i)
        {
            for(int j = 0; j + nb <= n; ++j)
            {
                if ( dp[ l - 1][ i ][ j ] != 0 )
                {
                    if ( ! dp[ l ][ i + nw ][ j + nb ] )
                    {
                        dp[ l ][i + nw][ j + nb ] = 1;
                    }
                    if ( ! dp[ l ][ i + nb ][ j + nw ] )
                    {
                        dp[ l ][ i + nb ][ j + nw ] = 2;
                    }
                }
            }
        }
    }
    
    return dp[level][n][n] != 0 ? 1 : 0;
}


int makeResult()
{
    int nw = n, nb = n, l = level, i, iw, ib;
    
    for( ; l > 0; -- l)
    {
        if (nw < 0 || nb < 0)
            return 0;
        
        switch(dp[l][ nw ][ nb ] )
        {
            case 0: return 0;
            case 1: // white vertexes to first group, black vertexes to second group
            {
                iw = nodes[l].id_white ;
                ib = nodes[l].id_black ;
                for(i = 1; i <= n + n; ++i)
                {
                    if(v[i] == iw)
                        v[i] = 1;
                    else if (v[i] == ib) 
                        v[i] = 2;
                }
                
                nw -= nodes[l].n_white;
                nb -= nodes[l].n_black;
            }
            break;
            case 2: // white vertexes to second group, black vertexes to first group
            {
                iw = nodes[l].id_white;
                ib = nodes[l].id_black;
                
                for(i = 1; i <= n + n; ++i)
                {
                    if (v[i] == iw)
                        v[i] = 2;
                    else if (v [i] == ib )
                        v[i] = 1;
                }
                
                nw -= nodes[l].n_black;
                nb -= nodes[l].n_white;
            }
            break;
        }
    }
    
    return 1;
}

int writeResult()
{
   for(int x = 1; x <= 2; ++x)
    {
        char c = '\n';
        for(int i = n + n; i > 0; --i)
        {
            if (v[i] == x)
            {
                pw.write(i, c);
                c = ' ';
            }
        }
    }
    pw.flush();
    return 0;
}

int solve()
{
    int i = 0, j = 0;
    readData();
    
    i = bfs();
    if (i)
        j = dp_calc();
    
    if (i && j )
    {
        makeResult();
        writeResult();
    }
    else
    {
        //printf("bfs: %d\t dp_calc: %d\n", i, j);
        puts("IMPOSSIBLE");
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
