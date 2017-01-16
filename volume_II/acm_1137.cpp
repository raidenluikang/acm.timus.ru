

// 1137. Bus Routes
// AC 0.001s 748Kb.

#include <cstdio>
#include <cstddef>

static const int N = 100;
static const int M = 1000; // so maximum edges nor more than 10^5
char in [ 1 << 19 ] ;
char out[ 1 << 19 ] ;

struct scanner
{
    scanner()
    {
        load();
    }
    unsigned readInt()
    {
        bool z;
        unsigned u;
        u = readInt_i();
//        if (!o[0]) // re-load content
//        {
//            z = !o[-1];
//            load();
//            if (z){ 
//                while(*o >='0' && *o <='9') u = (u << 3) + (u << 1) + (*o ++ - '0');
//                ++o;
//            }
//        }
        return u;
    }
private:
    unsigned readInt_i()
    {
        unsigned u = 0;
        while(*o >='0' && *o<='9')u = (u << 3) + (u << 1) + (*o ++ - '0');
        return ++o, u;
    }
    void load()
    {
        size_t m;
        m = fread(in,1,sizeof(in)-4,stdin);
        in[m] = in[m+1] = 0;
        o = in;
    }
private:
    
    const char* o;
    
};

struct writer
{
    writer(): w(out + sizeof(out)){}
    ~writer(){ flush();}
    
    void writeInt(unsigned u, char c)
    {
    //    if ( w - out < 8 )
     //       flush();
    
        *--w = c;
        do *--w = u % 10 + '0';while( u /= 10 );
    }
    
    void flush()
    {
        if (w != out + sizeof(out))
        {
            fwrite(w, 1, out + sizeof(out) - w, stdout);
            w = out + sizeof(out);
        }
    }
private:
    
    char * w;
};

int n, m, ne , stop_id;
int head[ 10008 ];
int next[ N * M + 8 ];
int dst [ N * M + 8 ];

int readData()
{
    scanner sc;
    n = sc.readInt();
    ne = 0;
    for( int i = 1; i <= n;++i)
    {
        int s, t; // s - source, t - target
        m = sc.readInt();
        s = sc.readInt();
        for(int j = 0; j < m; ++j)
        {
            t = sc.readInt();
            
            // add edge from s --> t
           ++ne;
           next[ ne ] = head[ s ];
           head[ s  ] = ne       ;
           dst [ ne ] = t        ;
           
           s = t;// now t - is source 
        }
    
    }
    stop_id = 0;
    while(head[stop_id] == 0 && stop_id < 10008) 
        ++ stop_id;
    
    return 0;
}

int stack[1<<17];

int eulerCycle()
{
    int n  = 0 , u, v, t = 0, h, val;
    
    stack[n++] = stop_id ;
    writer pw;
   // pw.writeInt(stop_id, ' ');
    while( n > 0 )
    {
        u = stack[n - 1 ];
        h = head[ u ];
        
        if (h == 0)
        {
            //degree of u is 0
            // add u to answer
            ++t;
            pw.writeInt(u, ' ');
            
            --n;//pop stack
        }
        else
        {
            v = dst[h];
            head[u] = next[h];//remove (u--> v) edge
            stack[n++] = v;//add v to stack.
        }
    }
    pw.writeInt(t-1,' ');
    pw.flush();
    
    return 0;
}

int solve()
{
    readData();
    eulerCycle();
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
