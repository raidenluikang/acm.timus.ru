

// 	ACM.TIMUS.RU 1087.
#include <cstdio>
 
int solve()
{ 
	int n,m;
	int w[50];
	bool dp[10001] = {};
	scanf("%d%d",&n,&m);
	for(int i = 0; i != m; ++i)scanf("%d",w+i);
	
	// n = 0 :  1 
	// n = 1
	dp[0] = true; // 1-win
	for(int i = 1; i <= n; ++i)
	{
		//dp[i] = true  if only if  for some w[k]<=i ,  dp[ i - w[ k ] ] = false
		dp[i] = false;
		for(int k = 0; k != m; ++k)
		  dp[i] |= w[k] <= i && !dp[ i - w[ k ] ];
	}
	
	if (dp[n])
	   puts("1");
	else
	   puts("2");
	 
	return 0;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif

    solve();
    
    return 0;
}  
