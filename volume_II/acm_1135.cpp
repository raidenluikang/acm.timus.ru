
// acm.timus.ru 1135. Recruits

#include <cstdio>
#include <cmath>

static const unsigned g[ 2 ] = { 0, ~0u };

char in[65536];
char const *o ;
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 

    unsigned n;
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    //1. read n
    n = 0;
    while(*o && *o <= 32)++o;
    while(*o >='0' && *o<='9')
        n = (n << 3) + (n << 1) + (*o++ - '0');
    
    
    unsigned ans = 0;
    for(unsigned i = 0, p = 0; i != n; ++i)
    {
        char c;
        do c = *o++; while(!(c == '<' || c == '>' || c == 0));
        //while( ( c = fgetc(stdin) ) != '<' && c != '>' && c != EOF);
        
        //if (in[i] == '>')
        // ans += p & g[c == '<'];
        // p   += c == '>';
        if (c == '<')
            ans +=p;
        else
            ++p;
    }
    
    printf("%d\n",ans);
    return 0;
}
