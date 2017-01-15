
// acm.timus.ru 1108. Heritage

//1)  1/a[1] >= 1/a[2] >= 1/a[3] >= ... >= 1/a[n]
// a[1] <= a[2] <= a[3] <= ... <= a[n]

//2) sum(1/a[i]) < 1

//3) 1 - sum(1/a[i]) -- minimal

// example: n = 1 .  a[1] = 2
//          n = 2 .  a[1] = 2, a[2] = 3

//         n = 3        2 3 7 

// SOLUTION: 
//  a[1] = 2.  a[i] = a[i-1]*( a[ i - 1 ]-1) + 1
//  a[i] = a[i-1] ^ 2 - a[i-1] + 1



#include <cstdio>
#include <cstring>

void judge_assert(bool b)
{
    if ( ! b )
    {
        printf("%d\n",1/b); // division by zero.
    }
}

typedef unsigned size_type ;
typedef unsigned value_t   ;
typedef const value_t const_value_t;

static const value_t T = 1000000000;
static const value_t T_1 = T - 1;

struct bigint
{
    size_type n;
    value_t d[ 4096 ];
};

size_type stretch_size(const_value_t a[], size_type n)
{
    while( n > 1 && a[ n - 1 ] == 0u )
        --n;
    return n;
}

char out[ 65536 ];
char * w ; 

int print_bigint(bigint const& a)
{
    size_type n = stretch_size(a.d, a.n);
    const_value_t * d = a.d;
    
    // last digit first printed.
    {
        value_t    u =  d[ n - 1];
        value_t    v = u;
        size_type  m = 0;
         
        do ++m; while( v /= 10 );
        
        for(size_type j = 0; j < m; ++j )
            w[m - j - 1] = u % 10 + '0',  u/=10;
        
        w += m;
    }
    
    if ( n > 1)
    {
        for(size_type i = n - 1; i > 0; --i)
        {
            value_t u =  d[ i - 1 ];
            for(size_type j = 0; j != 9; ++j)
                 w[ 8 - j ] = u % 10 + '0', u /= 10;
            w += 9;
        }
    }
    
    
    *w++  = '\n';
    return 0;
}

// c[] = a[] * b[] ,  where n <= 8
// return carry - is always equal to 0.
value_t mul_simple(const_value_t a[], const_value_t b[], size_type n, value_t c[] )
{
    unsigned long long carry = 0, t;
    
    memset(c, 0u, sizeof( c[ 0 ] ) * ( n  + n ) );
    
    for(unsigned i = 0; i != n; ++i)
    {
        t = a[i];
        for(unsigned j = 0; j != n; ++j)
        {
            carry += c[i + j] + t * b[j];
            c[i + j] = carry % T;
            carry /= T;
        }
        for(unsigned j = n; carry  > 0; ++j)
        {
            carry += c[i + j]; // b[j] == 0
            c[ i + j ] = carry % T;
            carry /= T;
        }
    }
    return 0;
}


// c[] = a[] + q ,   0<= q < T
// return carry
value_t  add(const_value_t a[], size_type n, value_t q, value_t c[])
{
    for(size_type i = 0; i < n && q > 0 ;++i)
    {
        q += a[i];
        c[i] = q >= T ? q - T : q;
        q    = q >= T ? 1 : 0;
    }
    return q;
}

// c[] = a[] + b[]
// return carry.
value_t add(const_value_t  a[], const_value_t  b[], size_type n, value_t c[])
{
    value_t carry = 0;
    for(size_type i = 0; i != n; ++i)
    {
        carry  += a[i] + b[ i ];
        c[ i ]  = carry  >= T ? carry - T : carry;
        carry   = carry  >= T ? 1 : 0;
    }
    return carry;
}

// c[] = a[] - b[]
// return carry with offset +1:  0 -> means carry = -1.  1 -> means carry = 0
value_t sub( const_value_t  a[], const_value_t b[], size_type n, value_t c[] )
{
    value_t carry = +1; // +1 offset
    for(size_type i = 0; i != n; ++i)
    {
        carry += a[i] + ( T_1 - b[ i ]  ); // T_1 = T - 1
        c[i]  = carry  >= T ? carry - T : carry;
        carry = carry  >= T ? 1 : 0;
    }
    return carry;
}


// c[] = a[] * b[] ,  where n may greate as 1000.
// t[] - is temporary array, need for inner calculations.
// return carry, i.e. 0.
value_t mul_karasuba(const_value_t a[], const_value_t b[], size_type n,  value_t c[], value_t t[] )
{
    size_type m;
    value_t  ma, mb, mt;
    // n - 2^k 
    if ( n <= 8 )
    {
        return mul_simple(a, b, n, c);
   }
    
    m = n >> 1 ; // m = n / 2
    
    //|-------------------------------------------------------------------------------------------
    //|1. a[0..n] = a[0..m] * T^m + a[m..n]
    //|2. b[0..n] = b[0..m] * T^m + b[m..n]
    //|-----------------------------------------------------------------------------------------
    //|Theory: 
    //|      A = a1 * T^m + a0
    //|      B = b1 * T^m + b0
    //|
    //|      C = A * B
    //|    -------------------------------------------------------------
    //|      C = A * B = (a1 * T^m + a0) * (b1 * T^m + b0) = a1*b1 * T^(2m) + (a0*b1 + a1*b0)*T^m + a0*b0
    //| 
    //|      Let P = a1 * b1
    //|          Q = a0 * b0
    //|          S = (a0 + a1) * ( b0 + b1) = a0 * b0 + a0*b1 + a1*b0 + a1 * b1
    //| 
    //|       so  a0 * b1 + a1 * b0 == S - P - Q
    //|
    //|      C = P * T^(2m) + (S - P - Q) *T^m + Q
    //| 
    //| we can product A and B only with 3 multiplication and one add, 2 subtract operations.
    //|------------------------------------------------------------------------------------------
    
    //| c[0..m]   = a0 + a1
    //| c[n..n+m] = b0 + b1
    
    ma = add(a, a + m, m, c);    // c[0..m] = a[0..m] + a[m..n]
    
    mb = add(b, b + m, m, c + n); // c[n..n+m] = b[0..m] + b[m..n]
    
    //Note that:  ma == 0  or ma ==   1
    //            mb == 0  or mb ==   1
    
    // t[ 0..n ] = c[ 0 .. m ] * c[ n .. n + m ]
    
    mt = mul_karasuba( c, c + n, m, t, t + n); // t[ n ... n + n ] -- temporary usage
    
    
    if (ma > 0  && mb > 0)
    {
        // Let c0 = c[0..m]
        //     c1 = c[n..n+m]
        // (T^m + c0)*(T^m + c1) = T^(2m) + (c0 + c1)*T^m + c0*c1
        // c0 * c1 = t[0..n] - already calculated
        
        // t[m..n] = t[m..n] + c[0..m] 
        ma = add(c    , t + m , m , t + m);
        
        // t[m..n] = t[m..n] + c[n..n+m]
        mb = add(c + n, t + m , m , t + m);
        
        mt = ma + mb + 1;
    }
    else if (ma > 0)
    {
        // (T^m + c0) * c1 = c1*T^m + c0*c1
        mt = add(c + n, t + m, m, t + m);
        
    }
    else if (mb > 0)
    {
        //c0 * (T^m + c1) = c0*T^m + c0*c1
        mt = add(c, t + m, m, t + m);
    }
    else
    {
        mt = 0;
    }
    // now (a0 + a1)*(b0 + b1) = mt*T^(2m) + t[0..n]
    
    //2. step: a0 * b0 --> c[0..n]
    
    mul_karasuba(a , b, m, c, t + n); // t[n..n+n] - is temporary usage
    
    //3. step: a1* b1 --> c[n .. n + n]
    mul_karasuba(a + m, b + m, m, c + n, t + n); // t[n..n+n] - is temporary usage
    
    // S = (a0 + a1)*(b0+b1),  P = a0*b0,  Q = a1 * b1
    // S = mt*T^(2m) + t[0..n], P = c[0..n] , Q = c[n..n+n]
    
    // S - P - Q
    ma = sub(t, c, n, t); // t[0..n] = t[0..n] - c[0..n]
   
    mb = sub(t, c + n, n , t); // t[0..n] = t[0..n] - c[n..n+n]
    
    judge_assert( mt >= ( 1- ma ) + ( 1 - mb ) ) ;
    
    mt -= ( 1 - ma ) + (1 - mb );
    
    // S- P - Q =  mt * T ^( 2m ) + t[0..n]
    
    // need add t[0..n] to c[ m..n + m ]
    // i.e. c[m..n+m] = c[m..n+m] + t[0..n]
    ma = add(c + m, t, n, c + m);
    
    // c[n + m] += ma + mt
    mt += ma;
    if (mt > 0)
    {
        // c[ n + m .. n + m + m] = c[ n + m .. n + m + m] + mt.  length of array = m.
        mb = add(c + n + m, m,  mt,  c + n + m);
        
        judge_assert( mb == 0 );
    }
    return 0;
}

static inline 
bool is_pow2(unsigned n){ return  0u == (n & (n - 1) ); }

bigint t; // temporary
// a = b * b
value_t sqr(bigint& a, bigint const& b)
{
    size_type   n = stretch_size(b.d, b.n);
    while(  !is_pow2( n ) )
            ++n;
    
    mul_karasuba(b.d , b.d,  n, a.d, t.d );
   
    a.n = n + n;
    return 0;
}

//it's guaranteed fill with zero.
bigint ans[ 20 ];


int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    ans[ 0 ].n = 1;
    ans[ 0 ].d[ 0 ] = 1;
    
    ans[1].n    = 1;
    ans[1].d[ 0 ] = 2;
    
    for(int i = 2; i <= 18; ++i)
    {
        int n, c;
        // a[i] = a[i-1]^2 - a[i-1] + 1
        sqr(ans[i], ans[i-1]); // now ans[i] = ans[i-1] ^ 2
        
        n = ans[i].n;
        
        //ans[i] = ans[i] - ans[i-1]
        sub(ans[i].d, ans[i-1].d,  n, ans[i].d);
        
        // ans[i] = ans[i] + 1
        c = add(ans[i].d, ans[ 0 ].d,  n, ans[ i ].d );
        
        ans[i].n = stretch_size(ans[i].d, n + c);
        
    }
    
    int n;
    scanf("%d\n",&n);
    
    w = out;
    for(int i= 1; i<=n;++i)
    {
         print_bigint(ans[i]);
    
    }
 
    fwrite(out, 1, w - out, stdout);
    
    return 0;
}
