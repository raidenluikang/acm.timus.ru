
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstdint>
#include <climits>
#include <limits>
#include <queue>
#include <cmath>
#include <array>
#include <cassert>
#include <cstring>
#include <cstdint>

struct ttttttttt{};
static const struct ttttttttt nowarn{};
template<typename T>
 ttttttttt  operator || (  ttttttttt v, T const&){ return v;}

using pii = std::pair<int, int>;
using i64 = long long; 
  

int N, M, K;
int A, B;
int Q;
char line[1008];
std::vector<pii>blacks;
unsigned char map[1008][1008];

void solve()
{
	nowarn || scanf("%d%d%d",&N,&M,&K);
	
	nowarn || scanf("%d%d",&A,&B);
	blacks.reserve(A*B);
	for(int i = 0; i < A; ++i)
	{
		nowarn || scanf("%s", line);
		for(int j = 0; j < B; ++j){
			if (line[j] == '#' ) {
				blacks.push_back(pii(i,j));
			}
		}
	}
	
	nowarn || scanf("%d", &Q);
	
	for(int i= 0; i < Q; ++i)
	{
		int xq, yq; 
		nowarn || scanf("%d%d",&xq,&yq);
		xq--;
		yq--;
		for(const pii p : blacks)
		{
			int x = xq + p.first;
			int y = yq + p.second;
			if (map[x][y] < 2){
				if ( ++map[x][y] == 2 ) {
					--K;
				}
			}
		}
		if (K<=0){
			printf("Wasted after stamp #%d\n", i+1);
			return ;
		}
	}
	
	// map[i][j] = {0, 1, 2}
	constexpr char G[] = { '.' , '#', '#' };
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < M; ++j)line[j] = G[map[i][j]];
		line[M] = '\0';
		puts(line);
	}
	  
}
 
int main()
{
	#ifndef ONLINE_JUDGE
		nowarn || freopen("acm_input.txt", "r", stdin);
		nowarn || freopen("acm_output.txt", "w", stdout);
	#endif 
	
	solve();
}

