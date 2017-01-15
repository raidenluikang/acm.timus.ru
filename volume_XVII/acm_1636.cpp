#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <utility>
#include <functional>
#include <algorithm>
#include <list>
#include <queue>
#include <iomanip>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

typedef long long i64;
typedef unsigned long long u64;
typedef std::vector<int> vi;
typedef std::pair<int,int> ii;
static const std::size_t N = 100005;

template < typename T > T gcd(T a, T b){ while(b){ T m = a % b; a = b; b = m; } return a; }
template < typename T > T fast_pow(T x, unsigned n){ T r = T(1); while(n>0){if (n&1)r = r * x; x = x*x; n/=2; } return r; }
template < typename T , typename Op> T fast_pow(T x, unsigned n, Op op){ T r = T(1); while(n>0){if (n&1) r = op(r,x); x = op(x,x); n/=2;} return r;}


int solve()
{
	unsigned t1, t2;
	std::cin >> t1 >> t2;
	for(unsigned i = 0; i != 10; ++i)
	{
		unsigned t;
		std::cin >> t;
		// t2 - t*20 < t1 -->so debug
		if (t2 < t1 + t*20)
		{
			puts("Dirty debug :(");
			return 0;
		}
		t2 -= t * 20;
	}
	
	puts("No chance.");
	
	return 0;
}
int main() 
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
    ::std::ios::sync_with_stdio(false); ::std::cin.tie(0); ::std::cout.tie(0);
    solve();
    return 0;
}

