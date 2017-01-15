 // acm.timus.ru 1130. Nikifor's Walk


#include <cstdio>
#include <cstdlib>


static const int N = 10016;

struct vec
{
    int x;
    int y;
};

vec operator - (vec a, vec b)
{
    vec r = {a.x - b.x, a.y - b.y};
    return r;
}

vec operator + (vec a, vec b)
{
     vec r = {a.x + b.x, a.y + b.y};
     return r;
}


char const* o;
char in[N*7];

short n, L;
short  adj_a[ N + N ] ;
short  adj_b[ N + N ] ;
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

static const 
int mul[ 202 ] = 
{0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 
361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 
1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 
2401, 2500, 2601, 2704, 2809, 2916, 3025, 3136, 3249, 3364, 3481, 3600, 3721, 3844, 
3969, 4096, 4225, 4356, 4489, 4624, 4761, 4900, 5041, 5184, 5329, 5476, 5625, 5776, 
5929, 6084, 6241, 6400, 6561, 6724, 6889, 7056, 7225, 7396, 7569, 7744, 7921, 8100, 
8281, 8464, 8649, 8836, 9025, 9216, 9409, 9604, 9801, 10000, 10201, 10404, 10609, 
10816, 11025, 11236, 11449, 11664, 11881, 12100, 12321, 12544, 12769, 12996, 13225, 
13456, 13689, 13924, 14161, 14400, 14641, 14884, 15129, 15376, 15625, 15876, 16129,
16384, 16641, 16900, 17161, 17424, 17689, 17956, 18225, 18496, 18769, 19044, 19321, 
19600, 19881, 20164, 20449, 20736, 21025, 21316, 21609, 21904, 22201, 22500, 22801, 
23104, 23409, 23716, 24025, 24336, 24649, 24964, 25281, 25600, 25921, 26244, 26569,
26896, 27225, 27556, 27889, 28224, 28561, 28900, 29241, 29584, 29929, 30276, 30625,
30976, 31329, 31684, 32041, 32400, 32761, 33124, 33489, 33856, 34225, 34596, 34969, 
35344, 35721, 36100, 36481, 36864, 37249, 37636, 38025, 38416, 38809, 39204, 39601,
200*200, 201*201
};// mul[i] = (i-256)^2 

int  len2(vec v){ return  mul[ abs(v.x) ] + mul[  abs(v.y) ]; }

//int stack[ N + N ];

int solve()
{
    
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
    
    if ( n < 2 )
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
            
            
            int d_a_i[6] = {t, t, b_i, b_i, a_i, a_i};
            
            int k = 0;
            while( len2(d[k]) > l2)
                ++k;
            
            v[m]       = d  [ k ];
            adj_a[ m ] = d_a[ k ];
            adj_b[ m ] = d_b[ k ];
            neg  [ m ] = k & 1; //d_neg[ k ];
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
        else  
        {
            v[ m ] = a - b;
            adj_a [ m ]  = a_i;
            adj_b [ m ]  = b_i;
            neg   [ m ]    = true;
            ++m;
        }
        
        ans[m-1] = true;
        for(int i = m - 1; i >=n;--i)
        {
           ans[ adj_a[ i ] ] = ans[ i ];
           ans[ adj_b[ i ] ] = ans[ i ] ^ neg[i];
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


