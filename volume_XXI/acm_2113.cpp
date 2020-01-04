
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstdint>
#include <climits>
#include <limits>
#include <queue>

struct ttttttttt{};
constexpr struct ttttttttt nowarn{};
template<typename T>
static constexpr struct ttttttttt  operator || (struct ttttttttt v, T const&){ return v;}

using pii = std::pair<int, int>;

int N, M, row_rabbit, col_rabbit, row_water, col_water;

int H[ 108 ][ 108 ];
int water[108][108];
int rabbit[108][108];
int min_jump[108][108];

std::queue< pii > queue;

void solve()
{
	nowarn || scanf("%d%d", &N, &M);
	
	for(int i = 1; i <= N; ++i){
		for(int j = 1; j <= M; ++j){
			nowarn || scanf("%d", &(H[i][j]));
		}
	}
	
	nowarn || scanf("%d%d", &row_rabbit, &col_rabbit);
	nowarn || scanf("%d%d", &row_water, &col_water);
	
	
	water[row_water][col_water] = 1;
	queue.push(pii(row_water, col_water));
	
	constexpr pii RS[] = { {1,0}, {0,1}, {-1,0}, {0,-1}};
		
	while( ! queue.empty() )
	{
		const pii coordinate = queue.front();
		
		const int row = coordinate.first;
		const int col = coordinate.second;
		queue.pop();
			  
		for(const pii p : RS)
		{
			const int new_row = row + p.first;
			const int new_col = col + p.second;
		
			if (new_row >= 1 && new_row <= N &&
			    new_col >= 1 && new_col <= M &&
			    water[new_row][new_col] == 0 &&
			    H[new_row][new_col] <= H[row][col]
			   )
			{
				water[new_row][new_col] = 1 + water[row][col];
				queue.push(  pii(new_row, new_col) );
			}
		}
	}
	
	#ifndef ONLINE_JUDGE
	printf("water\n");
	for(int i= 1; i<= N; ++i)
	{
		for(int j= 1; j <= M; ++j)printf("%d ", water[i][j]);
		printf("\n");
	}
	
	#endif
	
	if ( 0 == water[row_rabbit][col_rabbit] )
	{
		printf("0\n");
		return;
	}
	
	
	queue.push( pii(row_rabbit, col_rabbit) );
	
	rabbit[row_rabbit][col_rabbit] = 1;
	min_jump[row_rabbit][col_rabbit] = 0;
	
	while(!queue.empty())
	{
		const pii coordinate = queue.front();
		
		const int row = coordinate.first;
		const int col = coordinate.second;
		
		queue.pop();
		
		for (const pii p : RS)
		{
			const int new_row = row + p.first;
			const int new_col = col + p.second;
			
			if (	new_row >= 1 && new_row <= N &&
					new_col >= 1 && new_col <= M 
			   )
			{
				const bool is_visited = rabbit[new_row][new_col] > 0;
				const bool can_jump = !water[new_row][new_col] ||
									(1 + rabbit[row][col] <  water[new_row][new_col]);
									
				const int jump = std::max(0, H[new_row][new_col] - H[row][col]);
				const int new_jump = std::max(min_jump[row][col], jump);
				
				if (can_jump && (!is_visited || min_jump[new_row][new_col] > new_jump))
				{
					rabbit[new_row][new_col] = 1 + rabbit[row][col];
					min_jump[new_row][new_col] = new_jump;
					
					queue.push( pii(new_row, new_col) );
				}
			}
		}
	}
	
	#ifndef ONLINE_JUDGE
	printf("rabbit:\n");
	for(int i = 1; i <= N; ++i)
	{
		for(int j = 1; j <= M; ++j) printf("%d ", rabbit[i][j]);
		printf("\n");
	}
	
	printf("rabbit-jump:\n");
	for(int i = 1; i <= N; ++i)
	{
		for(int j = 1; j <= M; ++j) printf("%d ", min_jump[i][j]);
		printf("\n");
	}
	#endif
	
	int jump_ans = INT_MAX;
	
	for(int i = 1; i<= N; ++i)
	{
		for(int j = 1; j <= M; ++j)
		{
			if (!rabbit[i][j] || water[i][j])continue;
			
			jump_ans = std::min(jump_ans, min_jump[i][j]);
		}
	}
	
	if (jump_ans == INT_MAX) jump_ans = -1;
	#ifndef ONLINE_JUDGE
	printf("min-jump: ");
	#endif
	
	printf("%d\n", jump_ans);
}

int main()
{
	#ifndef ONLINE_JUDGE
		nowarn || freopen("acm_input.txt", "r", stdin);
		nowarn || freopen("acm_output.txt", "w", stdout);
	#endif 
	
	solve();
}

