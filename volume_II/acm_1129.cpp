//1129. Door Painting

/* 1129. Door Painting - http://acm.timus.ru/problem.aspx?num=1129
 *
 * Strategy:
 * Create a graph where every room is a node and every door is an edge. If the degree of every node
 * is even, we can take an Euler tour through the house and color every door that we pass green on
 * one side and yellow on the other, and we satisfy the door balance requirement given since we will
 * always color a door yellow when we enter a room and green when we leave it. If the degrees of
 * some nodes are odd, we can join every pair of odd nodes with an additional edge corresponding to
 * a virtual door that we can use to pass between rooms (there is always an even number of odd rooms
 * by the handshaking lemma). These virtual doors will only upset the hitherto perfect yellow/green 
 * balance by at most one door since there is at most one virtual door per room.
 *
 * Performance:
 * O(N^2), which is optimal since the input is of this size. The solution runs in 0.015s using 500KB
 * memory.
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

const int maxn = 100;

bool color[maxn+1][maxn+1]; // Color assigned to this side of the door
char mult[maxn+1][maxn+1];  // Multiplicity of this edge (could be a normal edge plus a virtual one)

struct node
{
    bool visited;
    node* out[128];
    int no;
    int id;
} v[101];

void addmult(int a, int b, int x) 
{ 
    mult[a][b] += x; 
    mult[b][a] += x; 
}

void addedge(node* a, node* b) 
{ 
    //a->out.push_back(b); 
    //b->out.push_back(a); 
    
    a->out[a->no++] = b;
    b->out[b->no++] = a;
}

void explore(node* u) // Euler tour + assignment of door color
{
    
    std::stack<node*> s;
    
    s.push(u);
    while( ! s.empty() )
    {
        node* v = s.top();
        s.pop();
        v->visited = true;
        
        while(v->no > 0)
        {
            node* w = v->out[--(v->no)];
            //v->out.pop_back();
            if(mult[v->id][w->id])
            {   // If we haven't visited through all multiplicities of this edge, mark it visited
                // by decreasing its multiplicity, and then assign the color
                addmult(v->id, w->id, -1);
                if(!mult[v->id][w->id])
                    color[v->id][w->id] = true;
                v = w;
                s.push( v );
            }
        }
    }
}

void even(int n) // Adds edges between all nodes of odd degree
{
    //std::vector<node*> odd;
    node* odd[128];
    int no = 0;
    for(int i = 1; i <= n; i++)
    {
        if( v[ i ].no & 1)
        {
            odd[no++] = v + i;
        }
    }
    
    for(int i = 0; i < no; i += 2)
    {
        addedge(odd[i], odd[i+1]);
        addmult(odd[i]->id, odd[i+1]->id, 1);
    }
}


char const* o;
char in[65536];

int readInt()
{
    int u = 0;
    while(*o && *o <= 32)++o;
    
    while(*o >='0' && *o <='9') u = (u << 3) + (u << 1) + (*o++ - '0');
    
    return u;
}

int input[128][256];

int main(int argc, char * argv[])
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    int n, m;

    
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    n = readInt();
    
    
    for(int i = 1; i <= n; i++)
        v[i].id = i;

    for(int i = 1; i <= n; i++)
    {
        m = readInt();

        input[i][0] = m;//.reserve( m );
        for(int j = 1; j <= m; j++)
        {
            int u = readInt();
              
            input[i][j] = u;//.push_back(u);
            if(i < u) // Don't add edges twice
            {
                addmult(v[i].id, v[u].id, 1);
                addedge( v+ i ,  v+  u );
            }
        }
    }

    even( n );

    for(int i = 1; i <= n; i++)
    {
        if(!v[i].visited)
        {
            explore( v  +  i );
        }
    }

    char * w = in;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= input[i][0]; j++)
        {
            *w++ = "GY"[ color[ i ][ input[ i ][ j ] ] ];
            *w++ = ' ';
        }
        
        if (input[i][0] > 0)
             w[-1] = '\n';
    }
    
    fwrite(in,1,w-in,stdout);
    return 0; 
}
