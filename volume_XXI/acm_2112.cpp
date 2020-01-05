#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>

int fail(){
	puts("FAKE");
	return 0;
}

void fail_exit(){
	fail();
	exit(0);
}


bool g[1002][1002];
bool visit[1002];
std::vector<int> group;

void dfs(int x)
{
	visit[x] = true;
	group.push_back(x);
	if (group.size() > 4) fail_exit();
	for(int y = 0; y < 1002; ++y){
		if ( !visit[y] && g[x][y]){
			dfs(y);
		}
	}
}

int solve()
{
	
	int n; std::cin >> n;
	std::vector< std::string> names(n);
	std::unordered_map<std::string, int> index_map;
	for(int i = 0; i < n; ++i)
	{
		std::cin >> names[i];
		index_map[names[i]] = i;
	}
	
	std::vector<int> lives(n, 3);
	
	enum { zdorov = 3, ranen = 2, pri_smerti = 1, umer = 0};
	
	std::string xs, ys, w;
		
	int Q;
	std::cin >> Q;
	for(int i = 0; i < Q; ++i)
	{
		int x, y;
		std::cin >> xs >> w >> ys;
		
		if ( !index_map.count(xs)) 
			return fail();
		
		x = index_map[xs];
		 
		if (lives[x] < ranen) return fail(); 
		 
		if (w == "HIT"){
			 // X HIT Y IN BODY
			 if ( ! index_map.count(ys))
				return fail();
			 
			 y = index_map[ys];
			 
			  
			 std::cin >> w;
			 assert(w == "IN");
			 
			 std::cin >> w;
			 
			 if (w == "BODY"){
				lives[y] = std::max( lives[ y ] - 1, 0); 
			 } else if ( w == "HEAD" ){
				lives[y] = std::max(lives[y] - 2, 0);
			 } else {
				 assert(false);
			 }
		} else if (w == "USES") {
			assert(ys == "MEDKIT");
			lives[x] = zdorov;
		} else if (w == "REVIVE"){
			if (!index_map.count(ys)) return fail();
			
			y = index_map[ys];
			
			if (lives[y] != pri_smerti) return fail();
			
			lives[y] ++;
			g[x][y] = g[y][x] = 1;
		} else {
			assert(false);
		}		
	}
	  
	for(int i= 0; i < 1002; ++i)visit[i] = false;
	std::vector< std::vector< int > > d[6];
	//printf("WE ARE HERE (1)\n");
	//fflush(stdout);
	
	for(int i = 0; i < n; ++i)
	{
		if ( ! visit[i] ){
			group.clear();
			dfs(i);
			
			d[group.size()].push_back(group);
		}
	}
	
	//printf("WE ARE HERE (2)\n");
	//fflush(stdout);
	
	//printf("d[3].size = %zu  d[1].size = %zu\n", d[3].size(), d[1].size());
	//fflush(stdout);
	
	if (d[3].size() > d[1].size()) return fail();
	
	
	for(auto d3 : d[3] ){
		d3.push_back(d[1].back()[0]);
		d[1].pop_back();
		d[4].push_back(d3);
	}
	
	while(d[2].size()>=2){
		auto d2 = d[2].back();
		d[2].pop_back();
		
		auto d2_2 = d[2].back();
		d[2].pop_back();
		
		d2.push_back(d2_2[0]);
		d2.push_back(d2_2[1]);
		
		d[4].push_back(d2);
	}
	
	//printf("WE ARE HERE (3)\n");
	//fflush(stdout);
	
	
	if ( ! d[2].empty() )
	{
		if (d[1].size() < 2) return fail();
		
		auto d2 = d[2].back();
		d[2].pop_back();
		
		auto d1 = d[1].back(); d[1].pop_back();
		auto d1_1 = d[1].back();d[1].pop_back();
		
		d2.push_back(d1[0]);
		d2.push_back(d1_1[0]);
		
		d[4].push_back(d2);
	}
	
	//printf("WE ARE HERE (4)\n");
	//fflush(stdout);
	
	
	if (d[1].size() % 4 != 0 ) return fail();
	
	for(size_t i = 0; i < d[1].size(); i += 4)
	{
		auto d1 = d[1][i];
		d1.push_back(d[1][i+1][0]);
		d1.push_back(d[1][i+2][0]);
		d1.push_back(d[1][i+3][0]);
		
		d[4].push_back(d1);
	}
	
	 
	std::cout <<  "CORRECT" << '\n';
	for( const auto& s : d[4] )
	{ 
		 std::cout << names[s[0]] << ' ' << names[s[1]] << ' ' << names[s[2]] << ' ' << names[s[3]] << '\n';
	}
	
	return 0;
}
int main()
{
	#ifndef ONLINE_JUDGE
		 freopen("acm_input.txt", "r", stdin);
		 freopen("acm_output.txt", "w", stdout);
	#endif 
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	
	solve();
 }

