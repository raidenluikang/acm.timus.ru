
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
	int p;
	
	scanf("%d",&n);
	
	std::vector<int>a(n);
	std::vector<int>b(n);
	
	for(int i = 0; i < n; ++i)scanf("%d",&a[i]);
	for(int i = 0; i < n; ++i)scanf("%d", &b[i]);
	
	scanf("%d", &p);
	
	
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	
	// if a[0] >= b[i] -->  a[0] <= a[1] <= a[2] <...<=a[i]  ==> b[i] <= a[i]
	int ans = 1;
	for(int i = 0, j = 0; i < n; ++i)
	{
		while(j < n && a[i] >= b[j])++j;
		
		// a[i] < b[j] but a[i] >= b[0], a[i] >= b[1], ..., a[i] >= b[j-1]
		ans = (ans * 1ll*( j - i ) ) % p;
	}
		
	printf("%d\n", ans);
}

