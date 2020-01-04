
#include <cstdio>
#include <algorithm>
#include <vector>

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	int n;scanf("%d",&n);
	
	std::vector<int>a(n);
	for(int i = 0; i < n; ++i)scanf("%d",&(a[i]));
	
	long long ans = 0;
	long long smax[2] = {0, 0};
	long long smin[2] = {0, 0};
	long long s = 0;
	
	for(int i = n - 1; i >= 0; --i)
	{
		s = a[i] - s;
		
		ans = std::max(ans, std::max(s - smin[i&1], s + smax[(i&1)^1]));
		
		if (i == n-1){
			smax[i&1] = s;
			smin[i&1] = s;
		} else {
			smax[i&1] = std::max(smax[i&1], s);
			smin[i&1] = std::min(smin[i&1], s);
		}
	}	
	
	printf("%lld\n", ans);
}

