

// acm.timus.ru 1045. Funny Game


#include <cstdio>
#include <cstring>

static const int N = 1024;

bool visit[N] = {};
int h[ N ] = {};
int g[ N ][ 24 ] = {};
int n, root;
int que[N];
int tq, hq;

bool win[ N ];
int  win_pos[ N ];

char in[ 65536 ];
char const* o;

void readData()
{
    o = in;
    in[fread(in,1,sizeof(in)-4, stdin)] = 0;

    n = 0;
    while(*o && *o <=32)++o;
    while(*o >=48) n = (n<<3) + (n<<1) + (*o++ - 48);

    root = 0;
    while(*o && *o <= 32)++o;
    while(*o >= 48) root = (root << 3) + (root <<1 ) + (*o ++  - 48);

    for(int i = 0; i != n - 1; ++i)
    {
        int a,b;
        a = 0;
        while(*o && *o <= 32)++o;
        while(*o >= 48) a = (a << 3) + (a << 1) + (*o++ - 48);

        b = 0;
        while(*o && *o <= 32)++o;
        while(*o >= 48)b = (b<<3) + (b<<1) + (*o++ - 48);

        g [ a ][ h[ a ]++ ] = b;
        g [ b ][ h[ b ]++ ] = a;
    }
}

int solve()
{
    readData();

    hq = tq = 0;
    que[tq++] = root;
    visit[root] = true;

    // bfs 
    while(hq < tq)
    {
        int u = que[hq++];

        for(int i = 0; i != h[u]; ++i)
        {
            int v = g[u][i]; // u -> v edge 
            if (!visit[v]) 
            {
                visit[v] = true;
                que[tq++] = v;
            }
        }
    }

    //all visit is true,
    for(int i= tq; i--> 0; )
    {
        int u = que[ i ];
        win[u] = false;
        win_pos[u] = -1;
        visit[u] = false;
        for(int j = 0; j != h[u]; ++j)
        {
            int v = g[u][j];
            if ( !visit[ v ] ) // if visit[v] == true  so  v is parent of u.
            {
                if ( !win[ v ])
                {
                    if ( win[ u ] )
                    {
                        if (win_pos[ u ] > v)
                              win_pos[ u ] = v;
                    }
                    else
                    {
                        win[u] = true;
                        win_pos[ u ] = v;
                    }
                }
            }
        }
    }

    char *w = in + 128;
        
    if (win[root])
    {
        unsigned u = win_pos[root];
        *--w = '\n';
        do *--w = u % 10 + '0'; while(u/=10);
        w -= sizeof("First player wins flying to airport");
        memcpy(w, "First player wins flying to airport ", sizeof("First player wins flying to airport"));
        //printf("First player wins flying to airport %d\n", win_pos[root]);
    }
    else
    {
        //First player loses
        //puts("First player loses");
        w -= sizeof("First player loses");
        memcpy(w, "First player loses\n", sizeof("First player loses")); 
    }

    fwrite(w, 1, in + 128 - w, stdout);
    
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
