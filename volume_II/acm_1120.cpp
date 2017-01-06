//1120. Sum of Sequential Numbers


#include <cstdio>
#include <cmath>
#include <cstring>

int main()
{
#ifndef ONLINE_JUDGE
    
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    
    int n;
    scanf("%d",&n);
    
    // 1 + 2 + 3 + .. + p = p(p+1)/2 = n
    // p^2 <  p*(p+1) = 2n
    // p < sqrt(2n) < sqrt(2*10^9) = sqrt(20)*10^4 < 45000
    
    // p2 = 0 + 1 + 2 + ... + p - 1 
    
     // p  = 10 : 10*9/2 = 5*9 = 45 , 45%10 = 5
    // p = 6 :   6*5/2 = 3*5 = 15 
    // p - 1 - even number so, p2 - is divided to p --> n must be divided to p
    // p - 1 - odd number so, p2 % p = p / 2
    // 1. need to find: maximum odd divisor of n in range[ 1..sqrt(2n)]
    // 2. or need to find such even p, which n % p = p / 2
    // p = 2m,   n = p*t + p/2 = 2mt + m = m (2t+1), --> find divisor m 
    // n/m - odd number ==>  2t+1 -> also odd divisor
    
    // p < sqrt(2n)  -->  n/p > sqrt(n/2) --> 2t + 1 > sqrt( n / 2 )
    
    // 2m < sqrt(2n) --> m < sqrt( n / 2 ) 
    
    if ( !( ( n & ( n - 1 ) ) )  || n == 1) // n  = 2 ^ k -- no solution , except p = 1
    {
        printf("%d 1\n",n);
        return 0;
    }
    
    
    // 2AP + P(P-1) = 2n
    
    // P( 2A + P - 1) = 2n --> find maximum divisor P of 2n
    
    
    
    // 45000 / 8 < 6000
    int const n2 = n + n;
    int uplimit = sqrt(n + n + .0 );
   
    int m = n2;
    
    static const unsigned char MASK[8] = {1,2,4,8,16,32,64,128};
    unsigned char p[ 6000 ];
    memset(p, 0x55, sizeof(p));
    p[0] = 0x53;
    //sqrt(45000) < 220
    for(int i = 3; i < 220; i += 2)
    {
        if (!(p[i>>3] & MASK[i&7]))
        {
            for(int j = i * i, i2 = i << 1 ; j < 45000; j += i2)
            {
                p[j>>3] |= MASK[j&7];
            }
        }
    }
    
    int pv[16];
    int dv[16];
    int v = 0;
    
    for(int i = 0; i <= uplimit; ++i)
    {
        if (!(p[i>>3] & MASK[i&7])) // i -is prime number
        {
            if (m % i == 0)
            {
                pv[ v ] = i ;
                dv[ v ] = 0 ;
                
                do dv[v]++; while( ( m /= i ) % i == 0);
                
                ++v;
            }
        }
    }
    
    if ( m > 1)
    {
        pv[v] = m;
        dv[v] = 1;
        v++;
    }
    
    // we have 2 n = pv[ k ] ^ dv[ k ], k = 0..v-1
    int d[ 4096 ] ;
    int dn = 0;
    d[dn++] = 1; // 1 - is first divisor of 2n
    int ans = 0;
    
    int t2 = 0;
    m = n2;
    while (!(m & 1 ) )
        ++t2, m >>= 1;
    m = (1u << t2)- 1;
      
    
    for(int i = 0; i != v; ++i)
    {
        //int dm    = dn;
        int prime = pv[ i ];
        
        for(int rep = 0, da = 0, db = dn; rep != dv[i]; ++rep, da = db, db = dn)
        {
            for(int j = da; j != db; ++j)
            {
                int dj = d[ j ] * prime;
                if (dj <=  uplimit)
                {
                    d[ dn++ ] = dj;
                    
                    // ans will update
                    //1. dj > ans
                    //2. dj - is odd  or
                    //3. dj - is even, but 2n/dj - also even
                    ans = ( (dj > ans) && ((dj&1) || ( ( dj >> t2) & 1 ) && ( 0 == ( m & dj ) ) ) )? dj : ans;
                }
            }
        }
    }
    
    // n > 2 -->  n>= 3,  if n==3:   sqrt(2n) = sqrt(6) = 2    6/2 = 3.  A = ( 2 n / p - ( p - 1 ) )  / 2
    // ans = maximum divisor of 2n, which less than sqrt(2n)
    {
        //n = 14, n2 = 28, ans = 2
        // sqrt(n2) = 5
        // ans = 4.  n2/4 = 7     
        // 7 - 3 = 4
        int a = (n2)/ans - (ans - 1);
        
        a/=2;
        printf("%d %d\n",a,ans);
        
    }
}
