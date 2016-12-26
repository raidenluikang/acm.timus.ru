


//acm.timus.ru Problem 1056. Computer Net


#include <cstdio>
#include <cstring>

static const unsigned N = 16384;

unsigned head[N];
unsigned nxt[N+N];
unsigned dst[N+N];
bool visited[N];
unsigned que[N];
unsigned dist[N];
unsigned prev[N];

unsigned n, qh, qt;

char in[131072];

char const* o;

int main(int argc, char* argv[])
{
 #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
 #endif

    o = in;
    in[fread(in, 1, sizeof(in)-4, stdin)] = 0;

    n = 0;
    //read n
    while(*o && *o <= 32)++o;
    while(*o >= 48)n=(n<<3) + (n<<1) + *o++ - 48;

    // now read edges 
    for(unsigned i = 2, p = 0 ; i<= n; ++i)
    {
        unsigned u = i;
        unsigned v = 0;
        while(*o && *o <= 32)++o;
        while(*o>=48) v = (v<<3) + (v<<1) + *o++ - 48;

        ++p;
        nxt[p] = head[u];
        head[u] = p;
        dst[p] = v;

        ++p;
        nxt[p]  = head[v];
        head[v] = p;
        dst[p]  = u;
    }

    memset(visited, 0, sizeof(visited));

    //que[0] = 1;
    qh = qt    = 0;
    que[qt++]  = 1;
    visited[1] = true;
    unsigned v;
    while(qh < qt )
    {
        v = que[qh++];

        for(unsigned h = head[v]; h != 0; h = nxt[h])
        {
            unsigned u = dst[h];
            if (!visited[u])
            {
                visited[ u ] = true;
                que[ qt++ ] = u;
            }
        }
    }
#ifndef ONLINE_JUDGE 
//only debug purpose
printf("v = %d\n",v);
#endif 
    // v - very far vertex 
    memset(visited, 0, sizeof(visited));
    qh = qt = 0;
    que[qt++] = v;
    visited[v] = true;
    dist[v] = 0;
    prev[v] = 0;
    while(qh < qt)
    {
        unsigned v = que[qh++];
        for(unsigned h = head[v]; h != 0; h = nxt[h])
        {
            unsigned u = dst[h];
            if(!visited[u])
            {
                visited[u] = true;
                dist[u]  = 1 + dist[v];
                prev[u]  = v;
                que[qt++] = u;
            }
        }
    }


    unsigned dist_max = dist[ que[ qt - 1 ] ];
    unsigned middle = dist_max / 2;
    
    memset(visited, 0, sizeof(visited));
    
    for(  ;qt > 0 && dist[ que[ qt - 1 ] ] == dist_max; --qt)
    {
        for(unsigned u =  que[ qt - 1 ] ; u != 0 && ! visited[ u ]; u = prev[ u ])
        {
            visited[ u ] = true;
        }
    }

    char * w = in;
    for(unsigned i= 1; i<=n;++i)
    {
        #ifndef ONLINE_JUDGE
            // only debug purpose
            printf("dist[%d] = %d\n",i,dist[i]);
        #endif
        
        if ( !visited[i]) continue;

        if ( dist[i] == middle ||
            (dist[i] == middle + 1 && ( dist_max & 1) ))
            {
                //write they
                unsigned u = i, v = i, vn = 0;
                do vn++; while(v/=10);
                v = vn;
                while(v-->0)w[v] = u%10 + '0', u/=10;
                w += vn;
                *w++ = ' ';// separate by space 
            }
    }

    if (w != in)
    {
        w[-1] = '\n';
        fwrite(in, 1, w - in, stdout);
    }

    return 0;
}
