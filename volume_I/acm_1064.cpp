
//acm.timus.ru 1064. Binary Search

#include <stdio.h>
#include <string.h>
#include <math.h>
 
const double pi = 3.1415926535897932384626433832795;



int main(int argc, char **argv)
{
#ifndef ONLINE_JUDGE
 	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif

    int ith, deep;
    scanf("%d%d",&ith,&deep);
    //int a[10000];
    //for(int i= 0; i != 10000; ++i)a[i] = i;
    
    bool flag[10005] = {};
    for(int n  = ith; n <= 10000; ++n)
    {
		int d = 0, fnd = 0;
		int l = 0, r = n - 1; 
		// 1. l = 0, r = 11
		// 2.  m = 5  -> l = 6, r = 11
		// 3.  m = 8  -> l = 9, r = 11
		// 4.  m = 10 -> 
		while( l <= r )
		{
			int m = (l+r)>>1;
			++d;
			if ( m == ith )
			{
				fnd = 1;
				break;
			}
			if ( m  < ith) l = m + 1; else r = m - 1;
		}
		
		flag[ n ] = ( d == deep ) && fnd;
	}
	
	int rn = 0;
	for(int i = 1; i<= 10000; ++i)
	  rn += (flag[i] && !flag[i-1]);
	
	
	char out[65536] = {};
	char * w = out + sizeof(out)/sizeof(out[0]);
	//*--w = '\n';
	  
    //printf("%d\n",rn);
    if (rn > 0)
    {
		for(int i = 10000; i>=1; --i)
		{
			if (flag[i] && !flag[i+1]) // end
			{
				unsigned u = i;
				*--w = '\n';
				do *--w = u % 10 + '0'; while(u/=10);
			}
			
			if (flag[i] && ! flag[i-1]) // start
			{
				unsigned u = i;
				*--w = ' ';
				do *--w = u % 10 + '0'; while(u/=10);
			}
		}
	}
	
	*--w = '\n';
	do *--w = rn % 10 + '0'; while(rn/=10);
    	
	fwrite(w, 1, out + sizeof(out)/sizeof(out[0]) - w, stdout);
 	return 0;
}
