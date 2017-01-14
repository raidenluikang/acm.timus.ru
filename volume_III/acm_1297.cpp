 // 1297. Palindrome


#include <cstdio>


char s[1024];
int d1[1024];
int d2[1024];

int n;

int min(int x, int y){ return x < y ? x : y;}

int solve()
{
    s[fread(s,1,1000,stdin)] = 0;
    n = 0;
    while(n < 1024 && (s[n] >='a' && s[n] <='z'  || s[n] >='A' && s[n] <='Z') )
        ++n;
    
    // algorithm Manaker
     
    for (int i= 0, l = 0, r = -1; i<n; ++i) 
    {
	int k = ( i > r ? 1 : min (d1[ l + r - i ], r - i ) );
	while (i+k < n && i-k >= 0 && s[i+k] == s[i-k])  ++k;
	d1[i] = k;
	if ( i + k - 1 > r)
		l = i - k + 1,  r = i + k - 1;
    }
    
    
    for(int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 0 : min(d2[l+r-i+1], r - i +1);

        while(i + k < n && i - k - 1 >= 0 && s[i+k] == s[i - k - 1]) k++;
        
        d2[  i ] = k;

        if( i + k - 1 > r)
            l = i - k, r = i + k - 1;
    }
    
    
    // find max
    int d1_max = -1, d1_i = 0;
    for(int i= 0; i < n; ++i)
    {
        if (d1[i] > d1_max)
        {
            d1_max = d1[i];
            d1_i = i;
        }
    }
    
    int d2_max = -1, d2_i = 0;
    for(int i= 0; i< n;++i)
    {
        if (d2[i] > d2_max)
        {
            d2_max = d2[i];
            d2_i = i;
        }
    }
    
    if (d1_max * 2 - 1 >  d2_max * 2)
    {
        // odd
        s[d1_i + d1_max] = 0;
        puts(s + d1_i - d1_max + 1);
    }
    else
    {
        //even
        s[d2_i + d2_max] = 0;
        puts(s + d2_i - d2_max);
    }
    
    
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    
    solve();
    
    return 0;
}
