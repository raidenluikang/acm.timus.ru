#include <stdio.h>
#include <algorithm>
 

int a[1<<17];
void solve()
{
	a[ 0 ] = 0;
	a[ 1 ] = 1;
	
	for(int i = 2; i + 1 < (1<<17); i += 2)
	{
		a[i] = a[i>>1];
		a[i+1] = a[i>>1] + a[ (i >> 1 ) + 1 ] ;
	}
	for(int i = 1; i < (1<<17); ++i)
	   a[i] = std::max(a[i], a[i-1]);
	
	int n = 0;
	do
	{   scanf("%d",&n);
            if (n>0)printf("%d\n", a[n]);
	}while(n > 0);
}

int main(int argc, char **argv)
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	 
	solve();
	return 0;
}
