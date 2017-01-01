

// acm.timus.ru 1070. Local Time



#include <cstdio>

static const int N = 100;
static const int K = 5;

char in[65536];
const char* o ;

int cn[N];
unsigned ip[N][K];
unsigned mask[N][K];
bool g[N][N];
bool visited[N];
int que[N];
int prev[N];

int n;
int source , target;

unsigned readInt()
{
    unsigned u = 0;
    while(*o && *o <= 32)++o;
    while(*o >= 48 && *o <= 57)u = (u << 3) + (u << 1) + (*o ++ - 48);
    return u;
}
unsigned readIP()
{
    unsigned u0,u1,u2,u3;
    u0 = readInt(); ++o;
    u1 = readInt(); ++o;
    u2 = readInt(); ++o;
    u3 = readInt(); ++o;
    return (u0 << 24) | (u1 << 16) | (u2 << 8) | (u3 << 0);
}
void readData()
{
    
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
 
    n = readInt();
    for(int i = 1; i <= n;++i)
    {
        cn[i] = readInt();
        for(int j = 0; j != cn[i]; ++j)
        {
            ip[i][j] = readIP();
            mask[i][j] = readIP();
        }
    }
    
    source = readInt();
    target = readInt();
}

void solve()
{
    readData();
    for(int i = 1; i <= n; ++i)
    {
        for(int j = i + 1; j <=n;++j)
        {
            bool c = false;
            for(int k = 0; k != cn[i]; ++k)
            {
                for(int l = 0; l != cn[j]; ++l)
                {
                    c = c || (ip[i][k] & mask[i][k]) == (ip[j][l] & mask[j][l]);
                }
            }
            g[i][j] = g[j][i] = c;
            
        }
        g[i][i] = false;
    }
    
    
    for(int i= 1; i<=n;++i){
        visited[i] = false;
        prev[i] = 0;
    }
    
    int h = 0, t = 0;
    que[t++] = source;
    visited[source] = true;
    while(h < t )
    {
        int u = que[h++];
        for(int v = 1; v <= n; ++v)
        {
            if (!visited[v] && g[u][v])
            {
                prev[v] = u;
                visited[v] = true;
                
                que[t++] =v;
            }
        }
    }
    
    char * w = in + 4096;
    if (!visited[target])
    {
        *--w = '\n';
        *--w = 'o';
        *--w = 'N';
    }
    else
    {
        //*--w = '\n';
        while(target != 0)
        {
            unsigned u = target;
            *--w = ' ';
            do *--w = u % 10 + '0'; while( u /= 10 );
            
            target = prev[target];
        }
        *--w = '\n';
        *--w = 's';
        *--w = 'e';
        *--w = 'Y';
        in[4095] = '\n';
    }
    
    fwrite(w, 1, in + 4096 - w, stdout);
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
