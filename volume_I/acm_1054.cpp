//acm.timus.ru 1053. Pinocchio


#include <cstdio>



char in[65536];
const char* o;

unsigned readInt()
{
    unsigned u = 0;
    while(*o && *o <= 32)++o;
    while(*o >= 48) u =(u << 3) + (u<<1) + *o++ - 48;
    return u;
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif

    o  = in;
    in[fread(in, 1, sizeof(in)-4, stdin)] = 0;

    unsigned n;
    unsigned d[32];
     n = readInt();
     for(unsigned i = 1; i <= n; ++i)
     {
         d[i] = readInt();
     }

     unsigned ans = 0;
     for(unsigned i = n , a = 1, b = 2, c = 3; i > 0; --i)
     {
         if (d[i] == c)
         {
             puts("-1");
             return 0;
         }
         if (d[i] == b)
         {
             ans += 1u << ( i - 1 );

             // (a,b,c) --> ( c b a ) 
             unsigned tmp = a;
             a = c;
             c = tmp; 

         }
         else // d[i] == a 
         {
             // (a,b,c) --> (a,c,b)
             unsigned tmp = b;
             b = c;
             c = tmp;
         }
     }
     printf("%u\n",ans);
}
