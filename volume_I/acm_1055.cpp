
//acm.timus.ru 1055. Combinations

#include <stdio.h>
 
int main(int argc, char **argv)
{
#ifndef ONLINE_JUDGE
 	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif
	 
	 unsigned n,m;
	 scanf("%u%u",&n,&m);
     // N,M   1<= M < N <= 50'000
     //1. prime numbers
     // C(N,M) = N!/(M! * (N-M)!)
     bool pbits[50005] = {};
     for(unsigned i = 2; i != 250; ++i)
     {
		 if (!pbits[i]){
			 for(unsigned j = i * i; j < 50005; j+=i)
			   pbits[j] = true;
		 }
	 }
	 
	 unsigned result = 0;
	   
	 // (7,3) = 7!/3!*4! = 
	 
	 //1. for i = 2
	 //
	 {
		 unsigned d=  0;
		 unsigned i_n = n;
		 unsigned i_m = m;
		 unsigned i_k = n - m;
		 do
		 {
			 d += i_n >>= 1;
			 d -= i_m >>= 1;
			 d -= i_k >>= 1;
		 }while(i_n);
		 result += !!d;
	 }
	 for(unsigned i = 3; i <= n ;  i+=2)
	 {
	   if ( !pbits[ i ] )
	      {
			  unsigned d = 0;
			  //unsigned i_pow =  i;
			  unsigned i_n = n; // 7 
			  unsigned i_m = m;  // 3
 			  unsigned i_nm = n - m; // 4
			  do
			  {
				  i_n /= i;     // 7/5 = 1      3/2 = 1    1/2 = 0  
				  i_m /= i;     // 3/5 = 0      1/2 = 0    0/2 = 0
				  i_nm /= i;    // 4/5 = 0      2/1 = 1    1/2 = 0
				  //i_n - i_m - i_nm = 0           0 
				  d += i_n - i_m - i_nm;
			  }while(i_n > 0 || i_m > 0 || i_nm > 0);
			  
			  result += !!d ;
			   
		  }
	  }
	  
	 printf("%u\n",result);
	

	return 0;
}
