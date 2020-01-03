#include <cstdio>
#include <map>

int n;
long long W;
long long a[64], sum[64];

std::map<std::pair<int,long long>, long long> cache;

long long solve_rec(int m, long long w)
{
	if ( m == 0)
	{
		return w == 0 ? 1 : 0;
	}
	if (w < 0) return 0;
	if ( 2 * sum[ m ] < w) return 0;
	if ( 2 * sum[ m ] == w ) return 1;
	
	auto it = cache.find(std::make_pair(m,w));
	if (it != cache.end()){
		return (*it).second;
	}	
	// w <= 2*sum[m]
	return cache[std::make_pair(m,w)] = solve_rec(m-1, w) + solve_rec(m-1, w - a[m-1]) + solve_rec(m-1, w- a[m-1]-a[m-1]);
}

long long solve()
{
	//1. sum of a
	sum[0] = 0;
	for(int i = 0; i < n; ++i)
	{
		sum[i+1] = sum[i] + a[i];
	}
	
	return solve_rec( n, W );	
}

int main(int, char**)
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	
	scanf("%d %lld",&n,&W);
	
	for(int i = 0; i < n; ++i){
		scanf("%lld",a+i);
	}
	// a[i+1] >= 2*a[i] = a[i] + a[i] >= a[i] + 2*a[i-1] = a[i] + a[i-1] + a[i-1] >= a[i] + a[i-1] + 2*a[i-2] >= .... >= a[i] + a[i-1] + a[i-2] + ... + a[1]
	printf("%lld\n", solve());
		
	return 0;
}
