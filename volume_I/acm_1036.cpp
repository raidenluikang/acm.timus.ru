

#include <cstdio>
#include <cstring>

 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif
 
    int n, s;
    scanf("%d %d",&n,&s);
    if ( ( s % 2 == 1 ) || ( s > n * 18 ) ) // 2*n * 9 = 18*n
    {
		puts("0");
		return 0;
	}
	
	const unsigned base = 1000000000;
    unsigned sum[ 512 ][ 6 ] = {};
    sum[0][0] = 1;
    s = s / 2;
    // 50*500*10 = 500^2	
	for(int i= 1; i <= n ;++i)
	{
		for(unsigned r = s + 10; r --> 0; )
		{
			//unsigned rs = sum[ r ];
			for(unsigned d = 9; d > 0; --d )
			{
				//sum[ r + d ] += rs;
				// sum[r + d ] += sum[r];
				unsigned carry = 0;
				for(unsigned j = 0; j != 6; ++j)
				{
					carry += sum[ r + d][ j ] + sum[ r ][ j ];
					sum[r+d][j] = carry % base;
					carry /= base;
				}
			}
			// if d == 0 :  sum[ r ] --> sum[ r ] became to same.
		}
	}
	
	unsigned t[16] = {}, v[16] = {};
	for(unsigned j = 0; j != 6; ++j)
	   t[j] = sum[s][j];
	 // v - t * t
	unsigned long long carry = 0;
	for(unsigned j = 0; j != 8; ++j)
	{
		unsigned long long tj = t[j];
		for(unsigned k= 0; k != 8; ++k)
		{
			carry += v[j+k] + tj * t[k];
			v[j+k] = carry % base;
			carry /= base;
		}
	}
	
	int h = 15;
	while(h>0 && v[h] == 0) --h;
	printf("%u", v[h]);
	for(int i = h-1; i>=0;--i)
	   printf("%09u",v[i]);
	printf("\n");
	return 0;   
}  
