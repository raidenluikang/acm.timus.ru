

#include <cstdio>
#include <cstring>

 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif
 
    double p,q;
    scanf("%lf",&p);
    scanf("%lf",&q);
    
    int pu = (int)( p * 100 + 0.1 );
    int qu = (int)( q * 100 + 0.1 );
    
    //  pu * ans div 10000 + 1 <= (qu * ans - 1) div 10000
    //  pu * ans + 10000 <= qu * ans - 1 
    //  (pu - qu)*ans <= 9999
    //  ans >= 10001 div (qu - pu);
    int ans = 1;
    int ps = pu, qs = qu; // pu * 1 and qu*1
    //printf("%d\n", ans);
    while(true)
    {
		// p * ans/100 = pu * ans / 10000  , greater than pu*ans/100 is (int)(pu*ans/100) + 1
		int pv = ps / 10000 + 1;
		
		// q * ans = qu * ans/ 100,  less than q*ans is  (int)(pu*ans -1)/100)
		int qv = (qs - 1) / 10000;
		if(pv <= qv)
		{
			printf("%d\n", ans);
			return 0;
		}
		++ans;
		ps += pu;
		qs += qu;
	}
	return 0;   
}  
