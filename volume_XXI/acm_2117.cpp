
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstdint>
#include <climits>
#include <limits>
#include <queue>
#include <cmath>

struct ttttttttt{};
static const struct ttttttttt nowarn{};
template<typename T>
 ttttttttt  operator || (  ttttttttt v, T const&){ return v;}

using pii = std::pair<int, int>;
using i64 = long long; 

static i64 isqrt(i64 n)
{
	i64 x = (i64)sqrt( n + .0);
	while ( x * x > n ) --x;
	while ( x * x < n ) ++x;
	return x;
}

static i64 icbrt(i64 n)
{
	i64 x = (i64)std::cbrt (  n + .0);
	while (x*x*x>n)--x;
	while (x*x*x<n)++x;
	return x;
}

static bool is_sqr(i64 n)
{
	i64 x = isqrt(n);
	return x *x == n;
}

static i64 solve(i64 n)
{
	if (n == 0 || n == 1 ) 
		return 1;
	
	if (n < 1000000000)
	{
		for(int s = isqrt(n)+1; s >= 1; --s)
		{
			if (n % (s*s) == 0) return 1 + s/2;
		}
	}
	
	const i64  n3 = 1000000 + 128;
	
	i64 s = n3;
	while( s > 0 && (n % ( s * s ) != 0))
	  --s;
	 
	i64 t = 1;
	
	// sqrt(n/t) > s --> n/t > s^2 --> t < n/s^2
	
	const i64 t_max = n3 ;
	
	while( t <= t_max && !( n % t == 0 && is_sqr( n / t ) ) )
	   ++t;
	
	 if (n % t == 0 && is_sqr(n/t) ){
		 s = std::max(s, isqrt(n/t));
	 }
	 
	 return  1 + s/2;
	
	
}

static void solve()
{
	i64 c;
	nowarn || scanf("%lld", &c);
	printf("%lld\n", solve(c));
}

int main()
{
	#ifndef ONLINE_JUDGE
		nowarn || freopen("acm_input.txt", "r", stdin);
		nowarn || freopen("acm_output.txt", "w", stdout);
	#endif 
	
	solve();
}

