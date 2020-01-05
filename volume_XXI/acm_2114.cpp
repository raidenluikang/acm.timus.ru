
#include <cstdio>
#include <algorithm>

int N, M, Q;
int a[512][512];
long long s[512][512];
long long d[512][512];
int qk[55];
long long sum_all = 0;

struct TResult
{
	long long ans;
	int x;
	int y;
};

void prepare()
{
	for(int i= 1 ; i <  512; ++i){
		for(int j = 1; j <  512; ++j){
			s[i][j] = a[i][j] + s[i-1][j] + s[i][j-1] - s[i-1][j-1];
		}
	}
	
	for(int ss = 0; ss < 1024; ++ss)
	{
		// x + y = s
		// 1 <= x <  512
		// y = s - x
		//  1 <= y < 512
		//  1 <= s - x < 512
		//  1 - s <= -x < 512 - s
		//  s - 512 <= x <= s - 1
		 
		for(int x = 1; x < 512; ++x)
		{
			int y = ss - x;
			if ( !(y >= 1 && y < 512) ) continue;
			
			d[x][y] = d[x-1][y+1] + s[x][y] - s[x][y-1];
		}
	}
}

long long area(int xa, int ya, int xb, int yb)
{
	return s[xb][yb] - s[xa-1][yb] - s[xb][ya-1] + s[xa-1][ya-1];
}

long long sum(int x, int y, int K)
{
	if (x + y + K >= N + M){
		return area(x, y, N, M);
	}
	
	if (x + K > N)
	{
		int yk = y + (x + K - N); // yk <  M , because y + x + K < N + M
		long long r = d[ N ][ yk ];
		
		r += area(x, y, N, yk - 1);
		if (y + K > M)
		{
			r -= area(1, yk, x-1, M);
		} else {
			r -= area(1, yk, x-1, y + K - 1);
			r -= d[x][y+K];
			r += a[x][y+K];
		}
		return r;
	} 
	else
	{
		long long r = d[x+K][y];
		if (y + K > M)
		{
			r -= area(1, y, x-1, M);
		}
		else
		{
			r -= area(1, y, x-1, y + K - 1);
			r -= d[x][y+K];
			r += a[x][y+K];
		}
		return r;
	}
	
}

TResult solve(int K)
{
	TResult result  = {-1,0,0} ;
	
	// (1,1)   (N,M)    N + M <= 1 + 1 + K --> K >= N + M - 2 
	if (K >= N + M - 2 ) return TResult{s[N][M],1,1};
	 
	for(int x = 1; x <= N; ++x)
	{
		for(int y = 1; y <= M; ++y)
		{
			long long w = sum(x, y, K);
			
			if (w > result.ans)
			{
				result.ans = w;
				result.x = x;
				result.y = y;
			}
		}
	}	
	
	return result;
}

int solve()
{
	scanf("%d%d", &N, &M);
	
	for(int i = 1; i <= N; ++i){
		for(int j = 1; j<= M; ++j){
			scanf("%d", &(a[i][j]));
		}
	}
	
	prepare();
	
	scanf("%d", &Q);
	
	for(int i= 0; i < Q; ++i)
		scanf("%d", &(qk[i]));
	
	for(int i = 0; i < Q; ++i){
		TResult result = solve(qk[i]);
		printf("%lld %d %d\n", result.ans, result.x, result.y);
	}
	return 0;
}

int main()
{
	#ifndef ONLINE_JUDGE
		 freopen("acm_input.txt", "r", stdin);
		 freopen("acm_output.txt", "w", stdout);
	#endif 
	
	solve();
 }

