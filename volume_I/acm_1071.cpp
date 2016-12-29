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

int solve()
{
    int x, y;
    char in[128];
    char const* o = in;
    char* w = in;
    in[fread(in,1,sizeof(in)-4, stdin)] = 0;
    
    x = 0;
    while(*o && *o<=32)++o;
    while(*o>=48 && *o <= 57)x = (x<<3) + (x<<1) + (*o++ - 48);
    
    y = 0;
    while(*o && *o <= 32)++o;
    while( *o >= 48 && *o <= 57)y = (y << 3) + (y << 1) + (*o++ - 48);
    
    int ans = 0;
    
    for(int base = 2; base <= 1000; ++base )
    {
        char xw[ 24 ] = {};
        char yw[ 24 ] = {};
        int ix = 0, iy = 0;
        int xx = x;
        int yy = y;
        do xw[ix++] = xx % base; while( xx /= base);
        do yw[iy++] = yy % base; while( yy /= base);
        
        int nx = ix, ny = iy;
        ix = 0;
        
        iy = 0;
        
        for( iy = 0; iy != ny;++iy)
        {
            while(ix != nx && xw[ix] != yw[iy])++ix;
            if (ix != nx)++ix; else break;
        }
        
        if(iy == ny)// all found
        {
            ans = base;
            break;
        }
    }
    
    if (!ans && x > 1000)
    {
        // base > 1000 
        //
        // x1 = x/base  x2 = x%base 
        // y1 = y/base  y2 = y%base
        
        //1. base <= y -->  y1 > 0
        //  y1 == x1  && y2 == x2 -->  y == x -> never 
        // 2. base > y  --> y1 = 0,  y2 = y
        // y == x/base || y == x%base
        if (y > 1000)
        {
            //  y != x / base , because  when base > 1000 , x/base < 1000 (x up limit 10^6)
            // so y = x % base 
            // x = base * t + y
            // (x-y)% base = 0
            if (x <= y + y) 
            {
                //no solution
            }
            else
            {
                int dif = x - y; // dif > y
                int t = 1000;
                
                while( t > 0 && (dif % t != 0 || dif / t <= y ) )
                    --t;
                
                ans = dif / t; // there dif % t = 0 && dif/t  > y
            }
        }
        else // y <=1000
        {
            // y = x / base ||  y = x % base 
            // x / base = y --> x = base*y + q ,  q < base .
            // base * y > 1000*y
            if (y * 1000 > x) // so there only y = x%base 
            {
                if (x <= y + y )
                {
                    
                }
                else
                {                    
                    int dif = x - y; // dif > y

                    int t = 1000;

                    while( t > 0 && (dif % t != 0 || dif / t <= y ) )
                        --t;

                    ans = t > 0 ? dif / t: 0; // there dif % t = 0 && dif/t  > y
                }
            }
            else
            {
                // so there may be 
                int base = x / y;
                int q = x % y ;
                while( q >= base || base <= y)++base;
                
                // y * 1000 > x --> x > y + y
                int dif = x - y;
                int t = 1000;
                while(t > 0 && ( dif % t != 0 || dif/t <= y))
                    --t;
                int b2 = dif / t;
                if (b2 < base)base = b2;
                
                ans = base;
            }
        }
    }
    
    if (ans != 0)
    {
        unsigned u = ans, v = ans, n = 0;
        do ++n ; while(v/=10);
        v = n;
        while(n-->0)w[n] = u % 10 + '0', u /=10;
        w += v;
        *w++ = '\n';
    }
    else
    {
        *w++ = 'N';
        *w++ = 'o';
        *w++ = ' ';
        *w++ = 's';
        *w++ = 'o';
        *w++ = 'l';
        *w++ = 'u';
        *w++ = 't';
        *w++ = 'i';
        *w++ = 'o';
        *w++ = 'n';
        *w++ = '\n';
    }
    fwrite(in,1,w-in,stdout);
    return 0;
}
int main(int argc, char** argv) {

#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    solve();
    return 0;
}

