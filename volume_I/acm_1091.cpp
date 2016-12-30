/* 
 * File:   main.cpp
 * Author: asus
 *
 * Created on December 29, 2016, 8:36 PM
 * 
 * acm.timus.ru 
 * 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

static const int primes[16] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};

char in[ 1 << 12 ];
char const* o;

int prime_divisors[64];
int c[ 64 ][ 64 ];
int d[64];

inline unsigned readInt()
{
    unsigned u = 0;
    do u = (u << 3) + (u << 1) + (*o++ - 48); while(*o >= 48);
    return ++o, u;
}
int main(int argc, char** argv) 
{

#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    o  = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;

    unsigned k = readInt();
    unsigned n = readInt();
        
    c[0][0] = 1;
    for(int i= 1; i != 64; ++i)
    {
        c[i][0] = 1;
        for(int j= 1; j != 64; ++j)c[i][j] = c[i-1][j] + c[i-1][j-1];
    }
    
    prime_divisors[ 0 ] = 0;
    prime_divisors[ 1 ] = 0;
    //prime_divisors[ 2 ] = 1;
    for(int i= 2; i != 64; ++i)
    {
        prime_divisors[i] = 0;
        int d = 1;
        for(int j = 0; j != 16; ++j)
        {
            int h = i % primes[j] == 0 ? 1 : 0;
            if (h)d *= primes[j];
            prime_divisors[ i ] += h;
        }
        
        //printf(" i = %d  d = %d\n",i,d);
        if (d != i)
            prime_divisors[ i ] =  0;
    }
    
    
    for(int i = 1; i <= n; ++i)
    {
        d[i] = 0;
        for(int j= i; j <= n; j +=i )
            d[ i ]++;
    }
    
    int ans = 0;
    for(int i = 2; i <=n; ++i)
    {
        if (prime_divisors[i] == 0)continue;
        
        if(prime_divisors[i] & 1) ans += c[d[i]][k];
        else   ans -=c[d[i]][k];
    }
    if (ans > 10000)ans = 10000;
    //printf("%d\n",ans);
    {
        char out[64] = {};
        char * w = out + 64;
        *--w = '\n';
        do *--w = ans % 10 + '0'; while(ans/=10);
        fwrite(w, 1, out + 64 - w, stdout);
    }

    return 0;
}


