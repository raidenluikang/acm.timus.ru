
// acm.timus.ru 1012. K-based number. Version-2. O(log(N)) algo.
 
#include <cstdio>
#include <cstring>
#include <algorithm>

#ifdef _MSC_VER
#define JUDGE_ALIGN64_OFFSET  __declspec(align(64))
#define JUDGE_ALIGN64_SUFFIX     
#else
#define JUDGE_ALIGN64_OFFSET   
#define JUDGE_ALIGN64_SUFFIX  __attribute__((aligned(8)))
#endif 

static const unsigned base = 1000000000;
static const unsigned base_1 = base - 1;

char buffer[4096];


//c[] = a[] + b[],  n - number of digits
unsigned add(const unsigned a[], const unsigned b[], unsigned c[], unsigned n)
{
	unsigned carry = 0;
	for(unsigned  i  = 0 ; i != n; ++i)
	{
		carry += a[i] + b[i];
		c[i]  = carry % base;
		carry  /= base;
	}
	
	if ( carry )
	{
		c[ n++ ] = carry;
	}
	return n;
}

// c[] = a[] - b[],  a[i] - b[i] = a[i] + (BASE - 1 - b[i] ) - ( BASE - 1) 
unsigned sub(const unsigned a[], const unsigned b[], unsigned c[], unsigned n)
{
	// b[i] < base -->  b[i] <= base - 1 -->  base - 1 - b[i] >= 0.  
	unsigned carry = 1; // +1 - offset.
	for(unsigned i = 0; i != n; ++i)
	{
		carry += a[i] + (base_1 - b[i]);
		c[i] = carry % base;
		carry /= base ;
	}
	return n;
}

// c[] = a[] * p,  n - number of digits
unsigned mul(const unsigned a[], unsigned c[], unsigned n,  unsigned long long p)
{
	unsigned long long carry = 0;
	for(unsigned i = 0; i != n; ++i)
	{
		carry += a[i] * p;
		c[i] = carry % base;
		carry /= base;
	}
	
	if (carry){
		c[n++] = carry;
	}
	return n;
}

// c[] = a[] * b[]
unsigned mul_big(const unsigned a[], const unsigned b[], unsigned c[], unsigned n)
{
	unsigned long long carry , ai;
	//std::fill(c, c + n + n, 0);
	memset(c, 0, sizeof( c[ 0 ] ) * ( n + n  ) );
	
   	for(unsigned i = 0; i != n; ++i)
   	{
		carry = 0;
		ai = a[i];
		for(unsigned j = 0; j != n; ++j)
		{
			carry += c[i + j] + ai  * b[ j ];
			c[i+j] = carry % base ;
			carry  /= base ;
		}
		for( unsigned j = n; carry > 0; ++j)
		{
			carry += c[i + j];
			c[i + j] = carry % base;
			carry /= base;
		}
	}

	return ( c[ n + n - 1 ] == 0 ? n + n - 1 : n + n );
}

// c[] = a[] * b[], n - number of digits  , n > 8.  tmp[] - temporary array
// we assume that, n = 2^h
unsigned mul_karasuba(const unsigned a[], const unsigned b[], unsigned c[], unsigned tmp[], unsigned n)
{
	if ( n <= 8 )
	{
		return mul_big( a, b, c, n );
	}
	
	unsigned m = n / 2 ;
	
	// a = a1 * base^m + a0
	// b = b1 * base^m + b0
	// c = a * b = (a1 * base ^ m + a0 ) * ( b1 * base^m + b0 ) = 
	// = (a1 * b1) * base ^(2m) + (a1 * b0 + a0 * b1 ) * base ^ m + a0 * b0
	
	
	// P = (a0 + a1)
	// Q = (b0 + b1)

	// V = a0 * b0
	// G = a1 * b1
	// P * Q = (a0 + a1) * (b0 + b1) = a0* b0  + a0  *b1 + a1 * b0 + a1 * b1
	
	// a1 * b0 + a0 * b1 = P * Q - G - V 
	
	//1. P = a0 + a1 --> c[0..m]
	unsigned lp = add(a, a + m, c, m); // c[0..m-1] - has answer,  c[m] - may or may not use : lp > m -> c[m] - used
	
	//2. Q = b0 + b1  --> c[n..n+m]
	unsigned lq = add(b, b + m, c + n, m); // c[n .. n + m - 1] - Q, c[n+m] - may or may not used: lq > m --> c[n+m] - used
	
	
	//3. P * Q = ( a0 + a1 ) * ( b0 + b1 ) --> tmp[ 0..n ]
	mul_karasuba(c, c + n, tmp, tmp + n, m);
	
	 //TODO: fix when lp > m , lq > m situations.
	
	//1. V = a0 * b0 --> c[0..n]
	mul_karasuba(a, b, c, tmp + n, m);
	
	//2. G = a1 * b1 --> c[n..n+n]
	mul_karasuba( a + m, b + m, c + n, tmp + n, m);
	
	// P * Q - V
	sub(tmp, c, tmp, n);
	// P* Q - V - G
	sub(tmp, c + n, tmp, n);
	
	// (P*Q - V - G) -- c[m..n+m]
	add(tmp, c + m, c + m, n);
	
	return (c[n+n-1] == 0 ? n+n-1 : n + n);
}

void print_bigint(const unsigned digits[] )
{
    char* w = buffer + sizeof(buffer);
    unsigned n = 256;
    while( n > 1 && digits[n-1] == 0) 
       -- n;
    
    // n >= 1 
    
    *--w = '\n';
    for(unsigned i = 0; i != n - 1; ++i)
    {
		unsigned u = digits[i];
		
		*--w = u % 10 + '0' , u /= 10 ;
		*--w = u % 10 + '0' , u /= 10 ;
		*--w = u % 10 + '0' , u /= 10 ;
		*--w = u % 10 + '0' , u /= 10 ;
		*--w = u % 10 + '0' , u /= 10 ;
		*--w = u % 10 + '0' , u /= 10 ;
		*--w = u % 10 + '0' , u /= 10 ;
		*--w = u % 10 + '0' , u /= 10 ;
		*--w = u % 10 + '0' , u /= 10 ;
	}
	
	unsigned u = digits[n-1];//last digit
	do *--w = u % 10 + '0'; while(u/=10);
    
    fwrite(w, 1, buffer + sizeof(buffer) - w, stdout); 	
}



int solve()
{
	int n,k;
	//A = [ [0 1] [ k-1 , k -1]] ^ n
	scanf("%d%d",&n,&k);
	k--;
	
	unsigned a11[256] = {}, a12[256] = {}, r11[256] = {}, r12[256] = {};
	unsigned a21[256] , a22[256], v[256], x[256], u[256];
	unsigned l = 1;
	
	a11[0] = 0;
	a12[0] = 1;
	
	r11[0] = 1;
	r12[0] = 0;
	
	while(n > 0 )
	{
		memset(a21, 0, sizeof(a21));
		memset(a22, 0, sizeof(a22));
		memset(v, 0, sizeof(v));
		memset(u, 0, sizeof(u));
		memset(x, 0, sizeof(x));
		
		// l - maximum number of digits of a11, a12, r11, r12
		
		if ( n & 1 )
		{
		  //1. calculate a21 and a22
		  
		  // 1.1 a21 = a12 * k
		   mul( a12, a21, l , k ); // may l + 1 digits
		  
		  // 1.2 a22 = a11 + a21
		  add( a11, a21, a22, 256 );
		  
		  //2. calculate r11  and r12
		  
		  // 2.1 r11 = = r11 * a11 + r12 * a21
		       // 2.1.1 :  r11 * a11 -> v
		       mul_big(r11, a11, v, l  );
		       // 2.1.2 :  r12 * a21 --> u
		       mul_big(r12, a21, u, l + 1);
		       
		       // 2.1.3: v + u ==> x, because we need r11 later
		       add(v, u, x, 256);
		       
		       
		  // 2.2 r12 = = r11 * a12 + r12 * a22
		       //2.2.1:  r11 * a12 --> v
		       mul_big(r11, a12, v, l);
		       
		       //2.2.2: r12 * a22 --> u
		       mul_big(r12, a22, u, l+1);
		       
		       //2.2.3: u + v --> r12
		       add(u, v, r12, 256);
		      
		  // 3. x - is r11.
		       memcpy(r11, x, sizeof(x));
		  
		   //find l.
		    l = 256;
		    while ( l > 1 && r11[ l - 1 ] == 0 && r12[ l - 1 ] == 0 && a11[l-1] == 0 && a12[l-1] == 0)
		      --l;
		    
		   n--;
		}
		else
		{
			// a = a * a
			
			// a11 = a11 * a11 + a12 * a21
			// a12 = a11 * a12 + a12 * a22
			
			//1. calculate the a21 and a22
			
		     // 1.1 a21 = a12 * k
		       mul( a12, a21, l , k ); // we assume result is l + 1 :)
		  
		      // 1.2 a22 = a11 + a21
		       add( a11, a21, a22, 256 );
			
			//2.1. a11 * a11 -> v
			mul_big(a11, a11, v, l);
			//2.2. a12 * a21 - > u
			mul_big(a12, a21, u, l+1);
			add(u,v,x,256);
			
			mul_big(a11, a12, v, l );
			mul_big(a12, a22, u, l + 1);
			
			add(u, v, a12, 256);
			
			memcpy(a11, x, sizeof(x));
			
			//find l: 
			 l = 256;
		    while ( l > 1 && r11[ l - 1 ] == 0 && r12[ l - 1 ] == 0 && a11[l-1] == 0 && a12[l-1] == 0)
		      --l;
			
			n /= 2;
		}
	}
	// we need r22 = r11 + r21 = r11 + k*r12
	memset(x, 0, sizeof(0));
	mul(r12, x, l, k);
	add(r11, x, x, 256);
	
	print_bigint(x);
	return 0;
}

#ifndef ONLINE_JUDGE
#include <chrono>
struct auto_cpu_timer
{
	typedef std::chrono::high_resolution_clock::time_point point;
	point start, end;
	auto_cpu_timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	~auto_cpu_timer()
	{
		end = std::chrono::high_resolution_clock::now();
		long int nu = std::chrono::duration_cast< std::chrono::microseconds>(end - start).count();
		printf("elapsed %-4d microseconds\n",nu);
	}
};
#else
struct auto_cpu_timer{};
#endif

int main()
{
	
 #ifndef ONLINE_JUDGE
      freopen("input.txt","r",stdin);
      freopen("output.txt","w",stdout);
 #endif 
 
   {
	   auto_cpu_timer tm;
	   solve();
   }
   return 0;
}  
