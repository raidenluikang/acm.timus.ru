#include <stdio.h>

int n, smax = 0, lmax;

struct ox
{
	int t1, t2, t3;
} t[101];

//typedef struct ox ox;

void readdata()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d %d %d", &t[i].t1, &t[i].t2, &t[i].t3);
}

void solve()
{
	int i, j;
	struct ox ll;

        //1. sort by T1
	for (i = 0; i < n; i++)
	{	
            for (j = i + 1; j < n; j++)
            {	
                if (t[i].t1 > t[j].t1)
		{
                    ll     = t[ i ];
                    t[ i ] = t[ j ];
                    t[ j ] = ll;
                }
            }
        }
        
        
        //lmax - time when 1-th student is ready.
        lmax = t[0].t1 + t[0].t2;
        
	if (lmax > t[0].t3)
	{
		smax = lmax - t[0].t3;
		for (j = 1; j < n; j++)
			t[j].t3 += smax;
	}
        
	for (i = 1; i < n; i++)
	{
		if (lmax < t[i].t1) 
                    lmax = t[i].t1;
		
                lmax += t[i].t2;
		
                if (lmax > t[i].t3)
		{
			smax += lmax - t[i].t3;
			for (j = i + 1; j < n; j++)  
				t[j].t3 += lmax - t[i].t3;
		}
	}
	printf("%d\n", smax);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
	readdata();
	solve();
	return 0;
}
