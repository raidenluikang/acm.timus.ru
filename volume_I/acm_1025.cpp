
#include <bits/stdc++.h>


void solve()
{
	int n;
	int a[128];
	
	std::cin >> n;
	
	for(int i = 0; i < n;++i)
	   std::cin >> a[ i ];
	
	std::sort(a, a + n); 
	int s = 0;
	
	for(int i = 0; i < (n+1)/2 ; ++i)
	{
		int h = (1 + a [ i ] ) / 2;
		s += h;
	}
	std::cout << s << '\n';
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
