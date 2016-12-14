

// 	ACM.TIMUS.RU 1049.
#include <cstdio>
 
static const int PRIMES[25] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int solve()
{ 
	int primes[ 10 ] = {};
	int degree[ 35 ] = {};
	int n = 0;

    for(int i = 0; i != 10; ++i)
    {
		int a;
		scanf("%d",&a);
		
		for(int k = 0; k != 25; ++k)
		{
			int const p = PRIMES[ k ];
			if ( a % p == 0)
			{
				int d = 0;
				do { d++; a /= p; }while( a % p == 0);
				
				degree[ k ] += d;
			}
		}
		
		if (a > 1) // a-is prime  greater than 100.
		{
			int p = a;
			int d = 1;
			
			int j = 0;
			while(j < n && primes[ j ] != p )
			   ++j;
			
			if ( j >=n )//a new prime
			{
			   primes[ n ] = p;
			   degree[ n + 25 ] = d;
			   ++n;	
			} 
			else // exist
			{
				degree[j + 25] += d;
			}
		}
	}
	
	
	int result = 1;
	for(int i = 0; i != 25 + n; ++i)
	{
		result = result * (1 + degree[ i ]);
		result = result % 10;
	}
	
	printf("%d\n", result);
	    	 
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
