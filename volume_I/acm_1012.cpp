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

namespace judge {   
	using std::cin; 
	using std::cout; 
	using std::endl; 
	using std::vector; 
	using std::pair; 
	using std::string;
	using std::map;
	}

using namespace judge;

typedef long long i64;
typedef unsigned long long u64;
typedef std::vector<int> vi;
typedef std::pair<int,int> ii;
static const std::size_t N = 100005;
static const i64 MOD  = 1000000007;
static const u64 BASE = 1000000000000000000ULL;

template < typename T > T gcd(T a, T b){ while(b){ T m = a % b; a = b; b = m; } return a; }

int solve()
{
	// F[0] = 1  K + N <= 1800
	 // F[1] = K
	 // F[2] = K^2 - 1    excluded '00' only
	 // F[3] = K^3 - K - K + 1
	 // F[4] = K1*F[3] + K1*F[2], where K1 = K - 1
	 // answer: F[n-1]*(K-1)  - first digit must be in [1..K-1]
	 u64 f[ 3 ][ 128 ] = {}; // 10^n = 10^1800  base = 10^16   1800 / 16 = 120
	 unsigned k,n, k1;
	 std::cin >> n >> k;
	
	 int i_0 = 0, i_1 = 1, i_2 = 2;
	 static const int iii[3] = {1,2,0};
	 f[i_0][0] = 1;
	 f[i_1][0] = k; 
	 // f[2] = (1+k)*(k-1)
	 // f[3] = (1+k)*(k-1)^2 + k*(k-1)
	 // f[4] = (1+k)*(k-1)^3 + k *(k-1)^2 + (1+k)*(k-1)^2 = (1+k)*(K-1)^3 + (2k+1)*(k-1)^2
	 // f[5] = (1+k)*(k-1)^4 + (2k+1)*(k-1)^3 + (1+k)*(k-1)^3 + k*(k-1)^2 = (k+1)*(k-1)^4 + (3k+2)*(k-1)^3 + k*(k-1)^2
	 
	 //f[ 2 ] = k*k - 1;
	 k1 =  k - 1;
	 for(unsigned i = 2; i <= n-1; ++i)
	 {
		 //f[i_2] = (f[i_0] + f[i_1]) * (k-1);
		 u64 carry = 0;
		 for(unsigned j = 0; carry  > 0 || f[i_1][j] > 0; ++j)
		 {
			 carry = carry + (f[i_0][j] + f[i_1][j]) * k1 ;
			 f[i_2][j] = carry % BASE;
			 carry /= BASE;
		 }
		 i_0 = iii[i_0];//(i_0 + 1)%3; 
		 i_1 = iii[i_1];//(i_1 + 1)%3; 
		 i_2 = iii[i_2];//(i_2 + 1)%3;
		 //for(unsigned j = 0; j != 128; ++j)
		 //   f[i_2][j] = 0;
	 }
	 //printf(":HI\n");
	 //return 0;
	 {
		 u64 carry = 0;
		 for(unsigned j = 0; j != 128; ++j)
		 {
			 carry = carry + f[i_1][j] * k1;
			 f[i_1][j] = carry % BASE;
			 carry /= BASE;
		 }
	 }
	 //cout << std::numeric_limits<u64>::max() << '\n';
	 //cout << (BASE-1 + BASE-1)*k1 << '\n';
	 char buff[4096] = {};
	 int nb = 0 ;
	 int nh = 127  ;
	 while(nh > 0 && f[i_1][nh] == 0)
	   --nh;
	
	 u64 last = f[i_1][nh];
	 int last_n = 0;
	 u64 last_t = last;
	 do last_n ++; while( last_t /= 10 );
	 for(int j = last_n - 1; j >= 0; --j)
	    buff[nb + j] = last % 10 + '0', last /= 10;
	 
	 nb += last_n;
	 
	 for(int i = nh - 1; i>=0; --i)
	 {
		 last = f[i_1][i];
		 for(int j = 17; j >= 0; --j)
		 {
			 buff[nb +  j] = last % 10 + '0', last /= 10;
		 }
		 nb += 18;
	 }
	 buff[nb] = '\0';
	 puts(buff);
	 //std::cout << (f[n-1] * (k-1) ) << '\n';
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
