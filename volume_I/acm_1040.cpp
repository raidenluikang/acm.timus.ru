


// acm.timus.ru 1040. Airline Company

#include <cstdio>
#include <cstring>

static const int N = 64;

int g[ N ][ N ];
int id[ N * N ];
bool visited[ N * N ];
int n,m;

char in[ 65536 ];
char const* o;

void init_in()
{
    o = in;
    in[fread(in, 1, sizeof(in)-4,stdin)] = 0;
}

int readInt()
{
    int u = 0;
    while(*o && *o <= 32)++o;
    while(*o >= 48) u = (u<<3) + (u<<1) + (*o++ - 48);
    return u;
}

int gcd(int x, int y){
    int z;
    while(y != 0)
    {
        z = x % y;
        x = y;
        y = z;
    }
    return x;
}
int solve()
{
    init_in();
    n = readInt();
    m = readInt();

    memset(visited, 0, sizeof(visited));
    memset(g, 0, sizeof(g));
    memset(id, 0, sizeof(id));

    for(int e = 1; e <= m; ++e)
    {
        int u = readInt();
        int v = readInt();

        g[u][v] = e;
        g[v][u] = e;
    }

    for(int u = 1; u <= n; ++u)
    {
        int ne = 0;
        for(int v = 1; v <= n; ++v)
            ne += !!g[u][v];
        
        if ( ne < 2 )
            continue;

        int c = 0;
        int nz = 0;
        for(int v = 1; v <= n; ++v)
        {
            if (int e = g[u][v] )
            {
                if (id[ e ] == 0)
                  ++nz;
                else 
                   c = gcd(c, id[e]);
            }
        }

        if ( c == 1 ) continue; //already made.

        if (nz == 0) // c > 1 and all edges numbered, fail 
        {
            puts("NO");
            return 0;
        }
        
        if (c == 0) 
        {
            // nz > 1
            if ( ! visited[ 1 ] )
            {
                for(int v = 1; v <= n; ++v)
                {
                    if (int e = g[ u ][ v ])
                    {
                        id[ e ] = 1;
                        break;
                    }
                }
                visited[1] = true;
                continue;
            }
            //1. get find x and x+1
            int new_id = 0;
            for(int e = 2; e < m; ++e)
            {
                if (!visited[e] && ! visited[e+1])
                {
                    new_id = e;
                    break;
                }
            }

            if (new_id != 0)
            {
                for(int v = 1, h = 2; v <= n && h > 0; ++v)
                {
                    if (int e = g[u][v])
                    {
                        visited[new_id] = true;
                        id[e] = new_id++;
                        --h;
                    }
                }
                continue;
            }

            puts("NO");
            return 0;
        }

        // there c > 1 
        int new_id = 0;
        for(int e = 1; e <= m; ++e)
        {
            if (!visited[e] && gcd(c, e) == 1)
            {
                new_id = e;
                break;
            }
        }

        if (new_id == 0)
        {
            puts("NO"); 
            return 0;
        }

        for(int v = 1; v <= n; ++v)
        {
            if (int e = g[u][v])
            {
                if (!id[e])
                {
                    id[e] = new_id;
                    visited[new_id] = true;
                    break;
                }
            }
        }
    }


    for(int u = 1, im = 1; u <= n; ++u)
    {
        for(int v = 1; v <= n; ++v)
        {
            if (int e = g[u][v])
            {
                if (!id[e])
                {
                    while(im <=m && visited[im])++im;
                    visited[im] = true;
                    id[e] = im;
                }
            }
        }
    }

    char* w = in + 65536;
    for(int v = m; v > 0; --v)
    {
        int d = id[v];
        *--w = ' ';
        do *--w = d%10 + '0'; while(d/=10);
    }

     *--w = '\n';
     *--w = 'S';
     *--w = 'E';
     *--w = 'Y';
   
    in[65535] = '\n';
    fwrite(w, 1, in + 65536 - w, stdout);

    return 0;
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
    #endif 
    solve();
    return 0;
}
