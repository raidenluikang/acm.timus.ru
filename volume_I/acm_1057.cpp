

// acm.timus.ru 1057. Amount of Degrees.

#include <cstdio>
#include <cstring>

unsigned c[ 36 ][ 36 ] = {};
unsigned t[ 64 ];
unsigned solve(unsigned n, unsigned k, unsigned b)
{
   unsigned m = 0;
   unsigned r = 0;
   memset(t, 0, sizeof(t));
   
   do  
      t[m++] = n % b ; 
   while( n /= b );
   //n = 20:  t[] : [0 0 1 0 1] , m = 5
   // r = c[4][2] + c[2][1] = 6 + 2 = 8
   
   // n = 16: t[] : [0 0 0 0 1], m = 5
   // r = c[4,2] = 6


   // 0..m-1
   while( m > 0 && k > 0)
   {
       // all k combination in [0..m-1] positions.
       if ( t[ m - 1 ] > 1 || ( t[ m - 1 ] == 1 && k == 1 ) )
       {
          return r += c[ m ][ k ];
       }

       // all k combinations in [0..m-2] positions, and decrease k by one.
       if ( t [ m - 1 ]  == 1 )
       {
           r += c[ m - 1 ][ k ];
           k--;
       }
       --m;
   }

   return r;
    
}
int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

unsigned x,y,k,b,r;
c[0][0] = 1;
for(unsigned x = 1; x < 36; ++x)
{
    c[x][0] = 1;
    for(unsigned y = 1; y < 36; ++y)
    c[x][y] = c[x-1][y] + c[x-1][y-1];
}

    while(4 == scanf("%u%u%u%u",&x,&y,&k,&b) )
    {

        unsigned ry = solve(y,k,b);
        unsigned rx = solve(x-1,k,b);
       // printf("ry = %u\trx = %u\n",ry,rx);
        r = ry - rx;
    
        printf("%u\n",r);
        break;
    }
    return 0;
}
