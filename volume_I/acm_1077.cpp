// acm.timus.ru 1077. Travelling Tours

#include <cstdio>



// Given N tours and M two-way roads, between any two cities has at most one road.
// Tour is  T1 T2 ... Tk T1   , K > 2  

static const int N = 200;
static const int M = N * N;
static const int COLOR_WHITE = 0 ;
static const int COLOR_GREEN = 1 ;
static const int COLOR_BLACK = 2 ;
static const int PREV_UNUSED = 0xFF;

bool g[ N ][ N ];
int color[ N ];
int stack[ N ];
int prev [ N ];
int n,m;

char in[ 1 << 20 ];
char const*o;
char * w ;

void writeChar(char c){ *--w = c;}

void writeInt(int u)
{
    do *--w = u % 10 + '0'; while(u /= 10);
}

int readInt()
{
    int u = 0;
    while(*o && *o <= 32)++o;
    while(*o >= 48 && *o <= 57) u = (u << 3) + (u << 1) + (*o++ - 48);
    return u;
}

void readData()
{
    w = in + sizeof(in)/sizeof(in[0]);
    
    o = in;
    
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    n = readInt();
    m = readInt();
    for(int i = 0; i != m; ++i)
    {
        int a = readInt() - 1;
        int b = readInt() - 1;
        g[a][b] = true;
        g[b][a] = true;
    }
}


int solve()
{
    
    readData();
    
    for(int i= 0; i != n;++i)
    {
        color[ i ] = COLOR_WHITE;
        prev [ i ] = PREV_UNUSED;
    }
    
    int tours = 0;
    for(int i = 0; i != n; ++i)
    {
        if (color[i] != COLOR_WHITE)continue;
        
        int root = i;
        int u = i, p = PREV_UNUSED;
        int ns = 0;
        stack [ ns++ ] = ( u << 16 ) | ( p << 8 ) | ( 0xFF );
        
        while(ns > 0)
        {
            int e = stack[--ns];
            
            int u = ( e >> 16 )& 0xFF  ;
            int p = ( e >>  8 ) & 0xFF ;
            int i = ( e >>  0 ) & 0xFF ;
            
            if ( i == 0xFF )// start of dfs
            {
                color[ u ] = COLOR_GREEN;
                prev [ u ] = p;
                i = 0;
            }
            
            for ( ; i != n; ++i)
            {
                if (g[u][i])
                {
                    if (i == p) // i - is parent of u , so skip this
                        continue;
                    
                    if (color[i] == COLOR_WHITE) // no visit yet, so visit it
                    {
                        stack[ns++] = (u << 16) | (p << 8) | (i+1); // back to here with i+1 cycle
                        stack[ns++] = (i << 16) | (u << 8) | (0xFF); // start with i-th vertex u-now parent of i-th vertex,
                        break;
                    }
                    
                    if ( color[ i ] == COLOR_GREEN )
                    {
                        // root-------> u
                        //              |
                        //              v 
                        // root ------> i
                        
                        // i - is parent of parent of ... parent of u
                        // so if we go throu parent[u]   parent[parent[u]] --> get to i
                        ++tours;
                        int v = u;
                        int k = 0;
                        char c = '\n';
                        //writeChar('\n');
                        while(v != i )
                        {
                            writeChar(c);
                            writeInt(v+1);
                            v = prev[ v ];
                            c = ' ';
                            ++k;
                        }
                        //v == i
                        writeChar(c);
                        writeInt(i+1);
                        ++k;
                        
                        writeChar(' ');
                        writeInt(k);
                    }
                    else 
                    {
                        // color[i] == COLOR_BLACK --> it's impossible
                    }
                }
            }
            
            if (i != n)continue;
            
            //there i == n so end of function dfs
            // set black color
            color[ u ] = COLOR_BLACK;
        } // end while(ns > 0)
    } // end for(i = 0; i != n; ++i)
    
    writeChar('\n');
    writeInt(tours);
    
    fwrite(w, 1, in + sizeof(in)/sizeof(in[0]) - w, stdout);
    return 0;
}
int main(int argc, char* argv[])
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    
    solve();
    return 0;
}
