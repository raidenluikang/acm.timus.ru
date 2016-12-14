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
template< typename T > T gcd(T a, T b){ while(b){ T m = a % b; a = b; b = m; } return a; }

int solve()
{
	 // F[0] = 1
	 // F[1] = K
	 // F[2] = K^2 - 1    excluded '00' only
	 // F[3] = K^3 - K - K + 1
	 // F[4] = K1*F[3] + K1*F[2], where K1 = K - 1
	 // answer: F[n-1]*(K-1)  - first digit must be in [1..K-1]
	 u64 f[20] = {};
	 unsigned k,n;
	 std::cin >> n >> k;
	 
	 f[0] = 1;
	 f[1] = k;
	 f[2] = k*k - 1;
	 for(unsigned i = 3; i!= 20; ++i)
	 {
		 f[i] = (f[i-1] + f[i-2])*(k-1);
	 }
	 std::cout << (f[n-1] * (k-1) ) << '\n';
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
