 // acm.timus.ru 1130. Nikifor's Walk


#include <cstdio>
#include <cstdlib>

void jassert(bool b)
{
    if (!b)
    {
        printf("%d",1/b);
    }
}

static const int N = 10016;

struct vec
{
    int x;
    int y;
    
    vec():x(),y(){}
    vec(int x_, int y_):x(x_),y(y_){}
};

vec operator - (vec a, vec b)
{
    return vec(a.x - b.x, a.y - b.y);//{a.x - b.x, a.y - b.y};
}

vec operator + (vec a, vec b)
{
    return vec(a.x + b.x, a.y + b.y);//{a.x + b.x, a.y + b.y};
}


char const* o;
char in[1 << 17];

int n, L;
int  adj_a[ N + N ] ;
int  adj_b[ N + N ] ;
bool neg  [ N + N ] ;
vec  v[ N + N];
bool ans[N + N];



int readInt()
{
    unsigned u = 0, s = 0;

    while(*o  && *o<=32)++o;

    if (*o == '-')s = ~0,++o; else if (*o == '+')++o;
    
 //   if (*o && *o <= 32)++o;
    while(*o >='0' && *o <='9') u = (u << 3) + (u << 1) + (*o ++ -'0');

    return (u ^ s) + !!s;
}

int writeAns(bool hasAns)
{
    if (!hasAns)
    {
        puts("WRONG ANSWER");
        //return 0;
    }
    else
    {
        char * w = in;
        *w++ = 'Y'; *w++ = 'E'; *w++ = 'S'; *w++ = '\n';
        for(int i= 0; i != n; ++i)
        {
            *w++ = "-+"[ans[i]];
        }
        *w++ = '\n';
        
        fwrite(in,1,w-in,stdout);
        
        //return 0;
    }
    return 0;
}

int mul[ 512 ];// mul[i] = (i-256)^2 

int  len2(vec v){ return  mul[   v.x  + 256 ] + mul[   v.y  + 256 ]; }

//int stack[ N + N ];

int solve()
{
    //mul[0] = 0256*256;
    for(int i = 0; i< 512; ++i)
        mul[i] = (i-256)*(i-256);//mul[i-1] + i + i - 1;
    
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    n = readInt();
    L = readInt();
    
    
    int const L2 = L * L;
    for(int i = 0; i !=n;++i)
    {
        v[ i ].x = readInt();
        v[ i ].y = readInt();
        
        
    }
    
    if (n < 2)
    {
       for(int i= 0; i <n;++i) 
           ans[i] = true;
        
       writeAns(true);
    }
    else // n > 2
    {
        int const l2 = L * L ;
        int m = n;
        
        vec a = v[ 0 ];
        vec b = v[ 1 ];
       
        int a_i = 0;
        int b_i = 1;
        
        for(int t = 2; t < n; ++t)
        {
            vec c   = v[ t ];
            int c_i = t;
            //        a + b,    a - b,    a + c,   a - c,    b + c,   b - c
            //        m++       m++       m++      m++       m++      m++
            //  a_i = t         t         b_i      b_i       a_i      a_i  
            //  b_i = m         m         m         m         m       m
            
            vec d[ 6 ] = 
            {
                a + b, a - b, a + c, a - c, b + c, b - c
            };
            int d_a[6]    = {a_i, a_i, a_i, a_i, b_i, b_i};
            
            int d_b[6]    = {b_i, b_i, c_i, c_i, c_i, c_i};
            
           // bool d_neg[6] = {false, true, false, true, false, true};
            
            int d_a_i[6] = {t, t, b_i, b_i, a_i, a_i};
            //int d_b_i[6] = {m, m, m,   m,    m,   m };
            
            int k = 0;
            while(k < 6 && len2(d[k]) > l2)++k;
            
            //if (k >= 6 || a_i == b_i )while(true);
            //printf("k = %d a = {%d %d}, b = {%d %d} , result: {%d, %d}\n",k, a.x,a.y, b.x,b.y, d[k].x,d[k].y);
            v[m]       = d  [k];
            adj_a[ m ] = d_a[k];
            adj_b[ m ] = d_b[k];
            neg  [ m ] = k&1; //d_neg[ k ];
            ++m;
            
            a_i = d_a_i[ k ];
            b_i = m - 1;//d_b_i[k];
            
            a = v[ a_i ];
            b = v[ b_i ];
        }
        
        // remain only two  a and b vectors
        if (len2(a+b) <= l2 + l2)
        {
            v[m] = a + b;
            adj_a[m] = a_i;
            adj_b[m] = b_i;
            neg[m] = false;
            ++m;
        }
        else if (len2(a-b) <= l2 + l2)
        {
            v[ m ] = a - b;
            adj_a [ m ]  = a_i;
            adj_b [ m ]  = b_i;
            neg   [ m ]    = true;
            ++m;
        }
        else
        {
            writeAns(false);
            return 0;
        }
        //printf("result vector {%d, %d}\n", v[m-1].x, v[m-1].y);
        // v[m-1] -- result
        int h = 0;
        v[h++].x = m - 1;
        //stack[h++] = m - 1;
        ans[m-1]   = true;
        
        while(h > 0)
        {
            int i = v[--h].x;
            bool i_positive = ans[ i ];
            
            //if ( i < n) continue;
            
            int i_a = adj_a[ i ];
            int i_b = adj_b[ i ];
            bool b_neg = neg[ i ];
            
            // i_positive = true:   ans[i_a] = true   ans[i_b] = !b_neg
            // i_positive = false:  ans[i_a] = false  ans[i_b] = b_neg
            ans[ i_a ] =  i_positive; //i_positive ? true : false;
            ans[ i_b ] =  i_positive ^ b_neg;// ? ( b_neg ? false : true) : (b_neg ? true : false);
                
            if (i_a >= n)
                v[ h++ ].x = i_a;
            if (i_b >= n )
                v[ h++ ].x = i_b;
            
        }
        
        writeAns(true);
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


