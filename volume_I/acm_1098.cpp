
#include <cstdio>
 
static const int K = 1999;

char in  [ 65536 ];
char const* o;

int main()
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    
     // F(n,k) = ((F(n-1,k) + k - 1) mod n) + 1), with F(1,k) = 1. there k = 1999.
    int n;
    n = fread(in, 1, sizeof(in) - 4, stdin);
    
    in[ n ] = '\0';
    o = in;
#ifndef ONLINE_JUDGE
    printf("n = %d\n",n);
#endif
    
    //remove line breaks
    for( n = 0; *o != '\0'; ++o)
    {
       if (*o != '\n')
           in[n++] = *o; 
    }
    in[n] = '\0';
#ifndef ONLINE_JUDGE
    printf("n = %d  after remove line breaks\n",n);
#endif
    
    int f = 1;// f(1,K) = 1
    for(int i = 2; i <= n; ++i)
    {
        f = ( ( f + K - 1 ) % i ) + 1;
    }
    
#ifndef ONLINE_JUDGE 
    printf("f = %d\n",f);
#endif
    
    if (in[f-1] == '?')
        puts("Yes");
    else if (in[f-1] == ' ')
        puts("No");
    else
        puts("No comments");
    return 0;
}
