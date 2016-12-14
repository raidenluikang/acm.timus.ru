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
     unsigned p[1024] = {};
     unsigned n = 0;
     std::cin >> n;
     for(unsigned i = 1; i <= n ; ++i)
        std::cin >> p[i];
     
     unsigned res = 1;
     for(unsigned i = 1; i<=n; ++i)
     {
		 if (p[i] == 0)continue;
		 unsigned rn = 0;
		 unsigned j = i;
		 while(p[j] != 0)
		 {
			 unsigned p_j = p[j];
			 ++rn;
			 p[j] = 0;
			 j = p_j;
		 }
		 unsigned d = gcd(res, rn);
		 rn /= d;
		 res *= rn;
	 }
	 std::cout << res << '\n';
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
