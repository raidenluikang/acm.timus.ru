#include <bits/stdc++.h>


void solve()
{
	int w[32];
	int n;
	std::cin >> n;
	for(int i = 0; i < n; ++i)
	   std::cin >> w[i];
	int res = 1000000000;
	for(int k= 0; k < (1<<n); ++k)
	{
		int a[2] = {};
		for(int i= 0; i < n; ++i)
		{
			a[ (k>>i) & 1] += w[i];
		}
		res =  std::min(res , std::abs(a[0] - a[1]));
		  
	}
	std::cout << res << '\n';
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
