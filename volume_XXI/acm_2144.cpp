
#include <cstdio>
#include <algorithm>
#include <vector>

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif 
	
	int n;
	scanf("%d",&n);
	std::vector< std::vector< int > > a(n);
	
	for(int i = 0; i < n; ++i)
	{
		int k;scanf("%d",&k);
		a[i].resize(k);
		for(int j = 0; j < k; ++j)scanf("%d", &(a[i][j]));
		
	}
	
	std::sort(a.begin(), a.end());
	std::vector< int > all;
	for(const auto& v : a ){
		all.insert(all.end(), v.begin(), v.end());
	}
	
	if (std::is_sorted(all.begin(), all.end()))
		puts("YES");
	else 
		puts("NO");
	
}

