
//acm.timus.ru 1023. Buttons

#include <stdio.h>
#include <string.h>
#include <math.h>

 
int solve(int n)
{
	
	if ( n % 3 == 0) return 2;
	if ( n % 4 == 0) return 3;
	
	int n_s = (int)sqrt(n + .0);
	for(int i = 5, k = 2; i <= n_s; i += k, k ^= 6)
	{
		if (n % i == 0)
		   return i - 1;
	}
	
	if (n % 2 == 0 && n/2 > 2)
	  return (n/2) - 1;
	return n - 1;
}

int main(int argc, char **argv)
{
#ifndef ONLINE_JUDGE
 	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif
	
	int n, ans, f = 1;
	int n_sqrt;
	scanf("%d",&n);
	
	 printf("%d\n",solve(n));
	return 0;
}
