#include <cstdio>
#include <cstring>
#include <cassert>
#include <map>
#include <utility>

void my_assert(bool b){ if (!b)printf("%d", 1/(int)b);}

using int64 = long long;
constexpr int seventeen = 17;
constexpr int seventeen_mask = (1<<seventeen) - 1;
constexpr int twenty = 20;
constexpr int64 twenty_mask = (1ll<<twenty) - 1;
constexpr int ans_start[ 4 ] = { 0,   10,   20,  30 };
constexpr int CACHE_MAX_SIZE = 1<<19;
int n;
int bc[1<<17];
int64 adj[ 64 ];
int ans[4][1<<20];
int64 adjGroup[3][1<<17];
std::map<int64, int64> cache;

void fill_ans()
{
	for(int step = 0; step < 4; ++ step)
	{
		const int start = ans_start[step];
			
		ans[step][0] = 1;
		for(int mask =  1; mask < (1ll << twenty); ++mask)
		{
			int i = 0;
			while(!(mask & (1<<i)))
				++i;
			// i -th bit is 1  of mask
			const int64  i_adj =  adj[ i + start ] >> start ;
			ans[step][mask] = ans[step][ mask ^ ( 1 << i ) ] + ans[step][ mask & i_adj];
		}
	}
} 
static int popcount(int64 mask)
{
	return bc[mask & seventeen_mask] + bc[ (mask>>17) & seventeen_mask] + bc[(mask>>34)&seventeen_mask];
}

int64 solve_rec(int pos, int64 mask )
{
	for(int step = 0; step < 4; ++ step)
	{
		const int start = ans_start[step];
		const int64 step_mask = twenty_mask << start;
		if ( (mask & step_mask) == mask) 
			return ans[step][ (mask >> start) & twenty_mask ];
	}
	
	int64 res = 0; 
	const int64 adjg = adjGroup[0][mask & seventeen_mask] & adjGroup[1][ (mask >> 17) & seventeen_mask]  & adjGroup[2][ (mask>>34) & seventeen_mask]; 
	
	if ((adjg & mask) == mask) 
	{
		return 1ll << popcount(mask);
	}
	
	if ((adjg & mask) > 0)
	{
		const int cnt = popcount(adjg & mask);
		return solve_rec(pos, mask & ~adjg )  << cnt;
	}	
	
	if (auto it = cache.find(mask); it != cache.end()) 
	    return (*it).second;
	
	while(!(mask & (1ll << pos)))
	 --pos;
	res = solve_rec(pos-1, mask ^ (1ll << pos)) + solve_rec(pos-1, mask & adj[pos]);
	
	if (cache.size() < CACHE_MAX_SIZE)
	  cache[mask] = res;
	
	return res;
}
 
int solve()
{
	char buf[128] = {};
	
	while (scanf("%d", &n) == 1) 
	{
		for(int i = 0 ; i <  n; ++i) 
		{
			adj[i] = 0;
			scanf("%s", buf);	
			for(int j = 0; j < n; ++j)
			 if (i != j && buf[j] == '1')
			   adj[i] |= 1ll << j;
		}
		
		for(int mask =0; mask <   1<<17; ++mask) 
		{
			bc[mask] = mask == 0 ? 0 : 1+bc[mask&(mask-1)];
			
			for(int i = 0; i < 3; ++i) 
			{
				adjGroup[i][mask] = (1ll << n ) - 1 ;
				for(int j = 0 ; j < 17; ++j) 
					if ((mask&(1<<j)) && 17*i+j < n)
						adjGroup[i][mask] &= adj[ 17 * i + j ]|( 1ll << (17*i+j));
			}
		}


		fill_ans();
		int64 res = solve_rec(n-1, (1ll << n)-1);
		printf("%lld\n", res);
	}

	return 0;
}

int main() 
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	solve();

}
