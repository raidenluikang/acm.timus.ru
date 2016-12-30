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

char in[1<<20];
char const* o;
unsigned short fenwick[10008];

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
    unsigned n = readInt();
    unsigned k = readInt();
    
    unsigned ans = 0;
    int ans_s = -1;
    
    for(unsigned i = 0;i  != k; ++i)
    {
        int s = 0;
        memset(fenwick, 0, sizeof(fenwick));
        
        for(int j = 0, x = 0; j != n; ++j)
        {
            //scanf("%d",&x);
            x = readInt()-1;
            //s += abs(x-j);
            x = n  - x;
            
            for(int k = x - 1; k > 0; k -= (k & -k)) 
                s += fenwick[k];
            
            for(int k = x; k <= n; k += (k & -k)) 
                ++fenwick[k];
        }
        
        if(s  > ans_s)
        {
            ans_s = s;
            ans = i + 1;
        }
    }
    
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


