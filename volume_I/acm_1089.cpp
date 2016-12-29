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

struct word
{
    char s[ 16 ]; // s[0] = length of word :)
};

word dict[ 100 ];
int ndict;

bool word_match(word const& u, word const& v)
{
    if (u.s[8] != v.s[8])return false;
    int m = 0;
    for(int i = 0; i != 8; ++i)
    {
        m += u.s[ i ] != v.s[ i ];
    }
    return m == 1;
}

char in[ 65536 * 4 ];
char const*o = 0;
char *w ;


int solve()
{
    unsigned ans = 0;
    o  = w = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    memset(dict, 0, sizeof(dict));
    //read dict
    ndict = 0;
    while(*o && *o != '#')
    {
        //read next word
        int n= 0;
        while(*o != '\n')dict[ndict].s[ n++  ] = *o++;
        ++o;//skip '\n';
        
        dict[ndict].s[8] = n;
        ++ndict;
    }
    
    ++o;//skip '#'
    if (*o == '\n')++o;
    
    while( *o )
    {
        while(*o && !(*o >='a' && *o<='z') )*w++ = *o++;//write non-letter symbols
        
        if ( !o[ 0 ] )
            break;
        
        int n = 0;
        word d = {};
        while(*o >= 'a' && *o <='z' && n < 8 )
            d.s[n++] = *o++;
        
        if (*o >= 'a' && *o <= 'z')
        {
            for(int i= 0; i != 8; ++i)*w++ = d.s[i];
            do *w++ = *o++; while(*o >= 'a' && *o <='z');
        }
        else
        {
            int i = 0;
            d.s[ 8 ] = n; // number of symbols.
            while(i != ndict && ! word_match(dict[i], d))++i;
            if (i != ndict)
            {
                //write dict[i]
                n = dict[i].s[8];
                for(int j= 0; j != n; ++j)
                    *w++ = dict[i].s[j];
                ++ans;
            }
            else
            {
                //write word d itself
                for(int j= 0; j != n; ++j)
                    *w++ = d.s[j];
            }
        }
    }
    
    //write number of correction
    {
        unsigned u = ans, v=ans, n =0;
        do ++n;while(v/=10);
        v = n;
        while(n-->0)w[n] =u%10 + '0', u/=10;
        w += v;
        *w++ ='\n';
    }
    
    //flush
    if (w != in)fwrite(in, 1, w - in, stdout);
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

