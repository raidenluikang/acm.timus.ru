
// acm.timus.ru 1014. Product of digits. 
 
#include <cstdio>

int main()
{
	    
   int n;
	
	scanf("%d",&n);
	
	if (n == 0) printf("10\n");
	else if (n == 1) printf("1\n");
	else 
	{
		char buf[64] = {'-','1','\0'};
		char * w = buf + 63;
		for(unsigned i = 9; i > 1 && n > 1; --i)
		{
			while (n % i == 0){*--w = i + '0'; n/=i;}
		}
		if (n != 1)w = buf;
		printf("%s\n",w);
	} 
	 
   
   return 0;
}  
