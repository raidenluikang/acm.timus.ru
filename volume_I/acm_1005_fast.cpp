
// acm.timus.ru 1005. Stone Pile O(2^(N/2)*N).  ~2^10*20 = 20 000 
 
#include <cstdio>
#include <algorithm>

#ifdef _MSC_VER
#define JUDGE_ALIGN64_OFFSET  __declspec(align(64))
#define JUDGE_ALIGN64_SUFFIX     
#else
#define JUDGE_ALIGN64_OFFSET   
#define JUDGE_ALIGN64_SUFFIX  __attribute__((aligned(8)))
#endif 


unsigned readInt()
{
	unsigned u = 0;
	int c;
	c = getc(stdin);
	while(c!= EOF && c <= 32) c = getc(stdin);
	while(c >= '0') u = (u << 3) + (u<<1) + c - '0', c = getc(stdin);
	
	return u;
}

int solve()
{
    unsigned n = 0, sum = 0, sum_div_2, n_div_2;
    unsigned w[2][20] = {};
    unsigned x[1024] = {};
    unsigned xn;
    //xn = scanf("%u",&n);
    n = readInt();
    for(unsigned i = 0; i != n; ++i)
    {
		w[1][i] = readInt();
		sum += w[ 1 ] [ i ];	
	}
    
    // if n is odd, add 0 weight :)
    if (n&1)w[ 1 ][ n++ ] = 0;
    
    sum_div_2 = sum / 2 ;
    n_div_2   = n / 2;
    xn = (1 << n_div_2);
    for(unsigned i  = 0, i_max = ( 1 << n_div_2 ); i != i_max; ++i)
    {
		unsigned s = 0;
	    for(unsigned j = 0; j != n_div_2; ++j)
	    {
			s += w[ ( i >> j ) & 1 ][ j ];
		}
		
		x[ i ] = s;
	}
    
    std::sort( x, x + xn );
    
    //swap  w < half >  with w < high half >
    for(unsigned i = 0; i != n_div_2; ++i)
    {
		unsigned t = w[ 1 ][ i ];
		w[ 1 ][ i ] = w[ 1 ][ i + n_div_2];
		w[ 1 ][ i + n_div_2] = t;
	}
	
	unsigned ans = 1000000000;
	for(unsigned i = 0, i_max = (1 << n_div_2); i != i_max; ++i)
	{
		unsigned s = 0;
		for(unsigned j = 0; j != n_div_2; ++j)
		{
			s += w[(i>>j)&1][j];
		}
		
		if (s <= sum_div_2)
		{
			unsigned t = sum_div_2 - s;
			unsigned * px = std::upper_bound(x, x + xn, t);
			// *px >  t
            // px != x  --> because  x[0] = 0  and  0 can't be greater than t >= 0.
            			
			px--;
			
			unsigned diff = sum - 2 * ( s + px[0] );
			ans = std::min(ans, diff);
		}
	}     
	
	printf("%u\n",ans);
	return 0;
}

int main()
{
	
 #ifndef ONLINE_JUDGE
      freopen("input.txt","r",stdin);
      freopen("output.txt","w",stdout);
 #endif 
 
   solve();
   return 0;
}  
