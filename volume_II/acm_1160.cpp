

 // 1160. Network

#include <cstdio>
#include <algorithm>


static const int N = 1000;
static const int M = 15000;

struct edge
{
    int cost;
    int a, b;
};

int n, m, l_min ;
char const* o;
char *w ;

edge e[M];
int parent[ N ];
int rank  [ N ];

char in[ 1 << 19 ]; // M *  22 = 3*10^5


void readData();
int readInt();
void writeInt(int u , char c);


int get_parent(int x)
{
    if (parent[x] != x)
        parent[x] = get_parent(parent[x]);
    return parent[x];
}

bool join_dsu(int x, int y)
{
    x = get_parent(x);
    y = get_parent(y);
    if (x != y)
    {
        if (rank[x] < rank[y])
        {
            parent[x] = y;
        }
        else
        {
            parent[y] = x;
            if (rank[ x ] == rank[y])
                ++rank[ x ];
        }
        
        return true;
    }
    return false;
}

void readData()
{
    w = in + sizeof(in);
    o  = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    n = readInt();
    m = readInt();
    for(int i= 0; i != m; ++i)
    {
        e[i].a = readInt() - 1;
        e[i].b = readInt() - 1;
        e[i].cost = readInt() ;
    }
}

int readInt()
{
    int u = 0;
    while(*o && *o <= 32)++o;
    while(*o >='0') u  = (u << 3) + (u << 1) + (*o++ - '0');
    return u;
}

void writeInt(int u , char c)
{
    *--w = c;
    do *--w = u % 10 + '0'; while(u /= 10);
}


struct cmp_edge
{
    bool operator()(edge const& lhs, edge const& rhs)
    const
    {
        return lhs.cost < rhs.cost;
    }
};

int main()
{
    
#ifndef ONLINE_JUDGE
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    readData();
    
    std::sort(e, e + m, cmp_edge() ); // sort by cost
    
    for(int i = 0; i != n; ++i)parent[i] = i;
    
    l_min = 0;
    int i_min = 0;
    for(int i = 0; i != m; ++i)
    {
        if ( join_dsu( e[ i ].a, e[ i ].b ) )
        {
            l_min = e[i].cost;
            i_min = i + 1;
        }
    }
    
    for(int i = i_min; i > 0; --i)
    {
        writeInt(e[i-1].b+1, '\n');
        writeInt(e[i-1].a+1, ' ');
    }
    writeInt(i_min, '\n');
    writeInt(l_min, '\n');
    
    fwrite(w, 1, in + sizeof(in) - w, stdout);
    
    return 0;
}
