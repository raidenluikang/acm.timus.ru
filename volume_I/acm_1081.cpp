

#include <cstdio>


 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif
 
	 unsigned int n,k;
	 scanf("%d %d",&n,&k);
	 unsigned f[46] = {};
	 
	 f[0] = 1;
	 f[1] = 2;
	 
	 for(int i = 2; i != 46; ++i)
	   f[i] = f[i-1] + f[i-2];
	   
	 
	 // n = 1:  0; 1  -> 2 - f[1]
	 // n = 2:  00 01 10  -> 3  -- f[2]
	 // 
	 //printf("%lld\n", f[45]);
	 char buf[ 64 ] = {};
	  
	 if (k > f[n])
	 {
		 puts("-1");
		 return 0;
	 } 
	 // k <= f[n]
	 for(unsigned i= 0; i != n; ++i)
	 {
		 if ( k > f[ n - i - 1] )
		 {
			 buf[i] = '1';
			 k-= f[ n - i - 1 ];
		 }
		 else
		 {
			 buf[i] = '0';
		 }
	 }
	 puts(buf);
}  
