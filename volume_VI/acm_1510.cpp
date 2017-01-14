// 1510. Order


#include <cstdio>


char const* o;
char in[65536];

unsigned readInt_i()
{
    unsigned u = 0;
    while(*o && *o <= 32)++o;
    while(*o >= '0' && *o <= '9') u = (u << 3) + (u << 1) + (*o++ - '0');
    return ++o, u;
}

unsigned readInt()
{
    unsigned u;
    u = readInt_i();
    if (*o == '\0') // end reach
    {
        bool z = o[-1] == '\0' ;
        int m;
        o = in;
        m = fread(in,1,sizeof(in)-4,stdin);
        in[m] = in[m+1] = '\0';
        
        if (z) // continue to read the int
        {
            while(*o >='0') u = (u << 3) + (u << 1) + (*o++ - '0');
        }
    }
    return u;
}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    
    int n,p,k,i,a;
    o = in;
    n = fread(in,1,sizeof(in)-4,stdin);
    in[n] = in[n+1] = 0;
    
    n = readInt();
    k = 0;
    for(i = 0 ; i != n; ++i)
    {
        a = readInt();
        if (k == 0){
            p = a;
            ++k;
        }
        else if (a == p) ++k ;else --k;
    }
    printf("%d\n",p);
}
