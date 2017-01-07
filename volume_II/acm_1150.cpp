

//1150. Page Numbers


#include <cstdio>

int m[ 10 ];
int d[ 10 ];
int t[ 10 ];

int solve()
{
    int n = 0, c;
    //while((c=getc(stdin)) >= 48 && c != EOF)  n = (n << 3) + (n << 1) + c - 48;
    
    scanf("%d",&n);
    for(int i= 0; i != 10;++i)m[i] = 0;
    
    // n = n1n2n3...nk
    
    // i=1..k
    // d[1] = 1..n1-1:   d[i] = 0..9, for i>1
    // 0*C[k-1][0] + 1*C[k-1][1] + 2C[k-1][2]
    // 10^(k-2)
    
    for(int i= 0, m = n; i != 10; ++i)
    {
        d[ i ] = m % 10;
        m /= 10;
    }
    
    t[0] = 1;
    for(int i= 1; i != 10;++i)
        t[i] = 10 * t[i-1];
    
    
    {
        int im = 10;
        while( im > 0 && d[im-1] == 0)--im;
        
        // 0    1      2    .. im-1
        // 10^0 10^1  10^2     10^(im-1)
        
        //
        for(int i = 1; i < d[im-1]; ++i)
        {
            m[ i ] += t[ im - 1 ];
            
            
        }
        if ( im > 1 )
        {
            // i = 1.. d[im-1]  - 1 
            int const s = ( d[ im - 1] ) * ( im - 1 ) * t[ im - 2 ];
            for(int j = 1; j != 10; ++j)
            {
                m[ j ] += s;
            }
            
            m[0] += ( d[ im - 1] - 1) * ( im - 1 ) * ( t [ im - 2 ] );
            
            for(int k = im - 1; k > 1; --k)
            {
                // [][][][] ...[] - k cells
                // first cell can hol only  1..9 : 9 digits
                // others  k-1 cells, we can put there zero with (k-1)*10^(k-2) possible.
                m[0] += 9 * (k - 1 )*t[ k - 2 ];
            }
            // 9 * (im - 3)*10^(im - 3) + 9 * (im-4)*10^(im-4)
            // 0 :  1..9: 9*10^(im-2) + 9*10^(im-3) + 
            //m[0]
        }
        
        // d[im-1] --> n - d[im-1]*10^(im-1) + 1
        // example: n = 534 ,  im = 3, t[im-1] = t[2] = 100
        // example: n = 987 654 321, im = 9, t[im-1] = t[8] = 10^8
        //  500 .. 534 -> 534 - 500 + 1 = 34 + 1 = 35
        n -= d[im-1] * t[im-1];
        m[ d [ im - 1 ] ] += n + 1;
        
        if ( im > 1)
        {
            for(int k = im - 1; k > 0; --k)
            {
                for(int i = 0; i < d[k-1]; ++i)
                {
                    m[i] += t[ k - 1 ];
                    
                }
                
                if (k > 1)
                {
                    // i = 0..d[k-1] - 1 : total= d[k-1]
                    int s = d[ k - 1 ] * ( k -  1 ) * t[ k - 2 ];
                    for(int j = 0; j != 10; ++j)
                    {
                        m[j] += s;
                    }
                }
                
                n -= d[ k - 1 ] * t[ k - 1 ];
                m[ d[ k - 1 ] ] += n + 1;
            }
        }
    }
    
    for (int i= 0; i != 10; ++i) 
      printf("%d\n", m[i]);
    
    return 0;
}

int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    
    solve();
    
    return 0;
}
