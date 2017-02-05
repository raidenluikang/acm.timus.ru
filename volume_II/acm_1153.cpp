

// 1153. Supercomputer

// Use long arithmetic.
// limits:  n < 10^600

#include <cstdio>    // printf/ scanf
#include <cstddef>   // size_t
#include <cstring>   // memset, memcpy
#include <algorithm>  // std::max
#include <cassert>
#include <cmath>

typedef long long ll;
typedef unsigned u32;

static const u32 base = 1000000000;



void writeBigint(u32 const* a, size_t n);

//



u32 add(u32 const* a, u32 const* b, size_t n,  u32 * c)
{
    ll q = 0;
  
    for(size_t i= 0; i != n ; ++i)
    {
       q += a[ i ] + b[ i ];
       c[ i ] = q % base;  
       q /= base;
    }
    return q;
}

u32 sub(u32 const* a, u32 const* b, size_t n, u32 * c)
{
    u32 q = 1; // +1 offset
    for(size_t i = 0; i != n ; ++i)
    {
      q += ( a[i] + base - b[i] ) - 1;
      c[i] = q % base;
      q /= base;
    }
    return 1 - q;
}

u32 div2(u32 * a, size_t n)
{
    u32 q = 0;
    for(size_t i = 0; i != n; ++i)
    {
            q  = q * base + a[ n - i - 1 ];
            a[ n - i - 1 ] = q >> 1;
            q = q & 1;
    }
    return q;
}

// b[] = a[] * p
ll mulx(u32 const* a, size_t n, u32 p, u32 * b)
{
	ll q = 0 ;
	for(size_t i = 0; i != n; ++i)
	{
		q += a[i] * 1LL * p;
		
		b[ i ] = q % base;
		q /= base;
	}
	return q;
}

int compare(u32 const* a, u32 const* b, size_t n)
{
	for(size_t i = n ; i>0;--i)
	{
		if (a[i-1] != b[i-1]) return (int)a[i-1]  -  (int)b[i-1]; 
	}
	
	return 0;
}

// c[] = a[] / b[] ,  p and t - temporary arrays.
ll div(u32 const* a, size_t n, u32 const* b, size_t m, u32 * c, u32 * p, u32 * t)
{
    const size_t nc = n - m + 1;
 
    // p[] = a[],  because p[] will be changed.
    memcpy(p, a, sizeof( *a ) * n );

    for(size_t i = 0; i != nc; ++i)
    {
        u32 * pi = p + ( nc - i - 1 ) ;
        ll q = (p[n-i] *1ll* base + p[n-i-1]);
        
        u32 digit = 0;
        
        u32 d_min = q/(1+b[m-1]), d_max = std::min( (ll)base, 1 + q / (b[m-1]));
        
        while(d_min + 1 < d_max )
        {
            digit = ( d_min + d_max ) >> 1;
            
            // t[] = b[] * digit
            mulx(b, m + 2, digit, t);
            
            if ( compare(t, pi, m + 2 ) > 0 ) // t[] > pi[], 
                d_max = digit;
            else
                d_min = digit;
        }
        
        digit = (d_min);
        
        mulx(b, m + 2, digit, t);
        
        sub(pi, t, m + 2, pi);
        
        c[ nc - i - 1 ] = digit;
    }
    return 0;
}


// c[] = sqrt(a[]).  
size_t sqrt_bigint(u32 const* a, size_t n,  u32 * c, u32 * x0, u32 * x1, u32 * t, u32 * p)
{
	//printf("sqrt_bigint. n = %d\n", (int)n);
	size_t m = (n+1)/2;
	
	//printf("a = "); writeBigint(a, n);
	//set x0 = 1
	memset(x0, 0, sizeof(*x0)*m);
	x0[0] = 1;
	
	//set x1 = a  first m digits
	memcpy(x1, a + ( n - m ), sizeof(*x1) * m);
	
	int lp = 0;
	while( compare(x0, x1, m) != 0 )
	{
		// x0 = (x1 + a/x1) / 2
		
		//printf("x0 = ");writeBigint(x0, m);
		//printf("x1 = ");writeBigint(x1, m);
		//1. c = a / x1
		div(a, n, x1, m, c, p, t);
		//printf(" a / x1 = ");writeBigint(c,  n-m+1);
		
                //2. x0 = c + x1
		u32 carry = add(c, x1, m, x0);
                size_t has = carry > 0 ? 1 : 0;
                if (has)x0[m] = 1;
                //printf(" c+x1 = ");writeBigint(x0, m+has);
		
		//3. x0 = x0 / 2
		div2(x0, m + has );
		//printf("(c+x1)/2 = ");writeBigint(x0,m);
                //printf("\n-----\n");
                
		//swap x0 and x1
		{
			u32 * h = x0;
			x0 = x1;
			x1 = h;
		}
		
                //++lp;
		//if (lp ++  == 113)break;
		//break;
	}
	
	memcpy(c, x1, sizeof(*c)* (m));
	
       // printf("total loop: %d\n", lp);
	return m;
}

u32 parseInt(char const* s, size_t n)
{
	u32 a = 0;
	for(size_t i = 0; i != n; ++i)
	{
		a = a * 10 + s[i] - '0';
	}
	return a;
}

char s[1024];

size_t readBigint(u32 * a )
{
	size_t n;
	fgets(s, 1024, stdin);
	n = 0; while(s[n]>='0' && s[n] <='9')++n;
	
	size_t m = 0;
	for(int j = n; j > 0; j-=9)
	{
		int delta = j >= 9 ? 9 : j;
		a[m++] = parseInt(s + j - delta, delta);
	}
	return m;
}

void writeBigint(u32 const* a, size_t n)
{
	while(n > 1 && a[n-1] == 0) 
	   -- n;
	size_t m = 0;
	
	{
		u32 d = a[n-1];
		int i = 16;
		char t[16] ;
		do t [ --i ] = d % 10 + '0' ; while(d/=10);
		do s[m++] = t[i++]; while(i < 16); 
	}
	
	for(int i = n - 2; i >= 0; --i)
	{
		u32 d = a[i];
		for(int j= 0; j < 9; ++j)s[m + 8 - j] = d % 10 + '0', d/=10;
		m += 9;
	}
	
	s[ m ] = '\0';
	
	puts(s);
}


u32 a[128], b[128], c[128], x0[128], x1[128], t[128], p[128];

int solve()
{
   size_t n;
   n = readBigint(a);
	
   // a = a + a
   
   ll q;
   q = add(a, a, n, a);
   if ( q )
      a[ n++ ] = 1;

   
   size_t m;
   
   m = sqrt_bigint(a, n, c, x0, x1, t, p);
   
   writeBigint(c, m);
   
   return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif 

	solve();
	
        return 0;
}
