

// 1133. Fibonacci Sequence

// F[i+2] = F[i+1] + F[i]  for any integer i.
// given i, F[i], j, F[j], n.  find F[n].
// F[i] = a
// F[j] = b
// F[n] = x -> ??


#include <stdio.h>


int i, j, n, fi, fj, fn;

long long gcd(long long a, long long b)
{
    long long m;
    while (b != 0)
    {
        m = a % b;
        a = b;
        b = m;
    }
    return a;
}

long long fib(int i, long long fi, int j, long long fj, int n)
{
    long long fn;
    if ( n == i ) return fi;
    if ( n == j ) return fj;
    
    // i < j
    if (i  < j - 1)
    {
        // f[i+1] = x
        const long long XM = 200000000008LL;
        long long x_min = -XM;
        long long x_max =  XM;
        while (x_min < x_max)
        {
            long long x =   ( x_min + x_max ) >> 1;
            long long x_0 = fi, x_1 = x, x_2;
        
            for(int k = i + 2; k <= j; ++k)
            {
                x_2 = x_0 + x_1;
                x_0 = x_1; x_1 = x_2;
                
                if (x_1 < -XM || x_1 > XM)
                    break;
                
            }
            
            if (x_1 < fj) 
                x_min = x + 1;
            else 
                x_max = x;
        }
        
        j  = i + 1;
        fj = x_min;
        
        if (j == n)return x_min;
    }
    
    
    if (n > j)
    {
        while( n  > j )
        {
            fn = fi + fj;
            fi = fj;
            fj = fn;
            --n;
        }
    }
    else // n < i
    {
        while ( n < i)
        {
            // fj = fi + fi-1 --> fi-1 = fj - fi
            fn = fj - fi;

            fj = fi;
            fi = fn;

            ++n;
        }
    }
    return fn;
    
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    scanf("%d%d%d%d%d",&i,&fi,&j,&fj,&n);
    
    if (i > j )
    {
        int t;
        t = i; i = j; j = t;
        t = fi; fi = fj; fj = t;
    }
    
    fn = fib(i, fi, j, fj, n);
    printf("%d\n", fn);
    
    
    
    
}
