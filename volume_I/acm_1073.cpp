
//acm.timus.ru 1073. Square Country

#include <stdio.h>
#include <string.h>
#include <math.h>
 

// n = m ^ 2  --> ans = 1
// n = 4k+1   prime number  or all prime numbers are 4k+1 --> ans = 2
// n = (8k+7)*4^m -> ans = 4
int solve(int n)
{
	 
	int m;
	while( !( n & 3 ) )
	   n >>= 2;
	   
	if (( n & 7) == 7)
	   return 4;
	
	m = sqrt(n + .0);
	
	if (m * m == n) return 1;
	
	// ans = 2: only if  4k+3  primes number is even number;
	// n <= 60 000  --> m = sqrt(n) == sqrt(6)*100 = 250
	// find primes < 250
	bool primes[256] = {};
	for(int i = 3; i < 16; i += 2)
	{
		if (!primes[i])
		  for(int j = i * i; j < 256; j += i+i)
		    primes[j] = true;
	}
	 
	
	while( !( n & 1 ) ) 
	    n >>= 1;
	
	for(int i = 3; i < 256; i += 6)
	{
		if (!primes[i])
		{
			int d = 0;
			while(n % i == 0){++d; n/=i;}
			
			if(d & 1) return 3;
		}
	}
	
	if ((n&3) == 3) return 3;
	else return 2;
	
}
int main(int argc, char **argv)
{
#ifndef ONLINE_JUDGE
 	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif
	
    int n = 0;
    scanf("%d\n", &n);
    printf("%d\n", solve(n));
    
	return 0;
}

