
#ifndef _MSC_VER
#include <bits/stdc++.h>

#else
#include <cstddef>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>
#endif

void solve()
{
    std::vector<double> v;
    v.reserve(1<<18);
    long long a;
    while( std::cin >> a)
    {
		v.push_back( std::sqrt( a + .0) );
	}
	std::reverse(v.begin(), v.end());
	
	for(std::size_t i = 0, n = v.size(); i < n; ++i)
	{
			std::cout << std::fixed << std::setprecision(4) << v[i] << '\n'; 
	}	
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
