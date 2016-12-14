
#include <bits/stdc++.h>


long long Q(int n)
{
	if (n == 0)
	   return 10; // 1 * 0 = 0, and 10 > 0
	if (n < 10)
	   return n;
	long long r = 0, t = 1;
	for(int i = 9; i > 1; --i)
	{
		while(n % i == 0)
		{
			r = r + t * i;
			t = t * 10;
			n = n / i;
		}
	}
	if ( n != 1)
	 return -1;
	else
	  return r;
}
void solve()
{
	int n;
	std::cin >> n;
	std::cout << Q(n) << '\n';
 }

int main(int argc, char **argv)
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	::std::ios::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0);
	solve();
	return 0;
}
