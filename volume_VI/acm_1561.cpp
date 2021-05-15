#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <numeric>
#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <random>
#include <cmath>
#include <cassert>
#include <map>
#include <queue>
#include <set>
#include <utility>

constexpr int N = 1040;
constexpr int MOD = 7;
constexpr int Inv[7] = { 0,1,4,5,2,3,6 };

struct Gauss
{
	std::vector<int> v[N]; 
	int vl[N];
	
	Gauss() 
	{
		std::fill(vl, vl + N, 0);
		for (int i = 0; i < N; ++i)
			v[i].resize(N);
	}

	bool check(std::vector<int>  x)
	{
		int m = x.size();
		for (int i = 0; i < m; i++)
		{
			if (x[i])
			{
				if (!v[i][i])return true;
				int inv_xi = Inv[x[i]];
				for (int j = i; j <  m; j++)x[j] = x[j] * inv_xi % MOD;
				for (int j = i; j <  m; j++)x[j] = (x[j] - v[i][j] + MOD) % MOD;
			}
		}
		return false;
	}

	int query(std::vector<int>  x)
	{
		int m = x.size();
		int r1 = 0, r2 = 1, r = 0;
		for (int i = 0; i <  m; i++) 
		{
			if (x[i])
			{
				if (!v[i][i])return -1;
				
				r = x[i]; 
				r2 = r2 * r % MOD;
				r1 = r1 * Inv[r] % MOD;

				for (int j = i, now = Inv[x[i]]; j < m; j++)x[j] = x[j] * now % MOD;
				r1 = (r1 + vl[i]) % MOD;
				for (int j = i; j < m; j++)x[j] = (x[j] - v[i][j] + MOD) % MOD;
			}
		}
		return r1 * r2 % MOD;
	}

	void push(std::vector<int>  x, int vl0)
	{
		int m = x.size();
		for (int i = 0; i <  m; i++) 
		{
			if (x[i])
			{
				vl0 = vl0 * Inv[x[i]] % MOD;
				
				for (int j = i, now = Inv[x[i]]; j <  m; j++)x[j] = x[j] * now % MOD;

				if (!v[i][i]) 
				{
					v[i] = x;
					v[i].resize(N);
					vl[i] = vl0;
					break; 
				}
				
				vl0 = (vl0 - vl[i] + MOD) % MOD;
				
				for (int j = i; j <  m; j++)
					x[j] = (x[j] + MOD - v[i][j]) % MOD;
			}
		}
	}
};
 
static int solve()
{
	int N;
	std::cin >> N;
	std::string cmd;
	
	std::vector<int> honeys;
	 

	static const std::map<std::string, int> weekdays =
	{
		{"Sunday", 0},
		{"Monday", 1},
		{"Tuesday", 2},
		{"Wednesday",3},
		{"Thursday", 4},
		{"Friday", 5},
		{"Saturday", 6},
	};
	static const std::vector<std::string> weekday_names = 
	{
		"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
	};
	
	
	bool already_crazy = false;
	Gauss gauss;

	auto Learn = [&](std::vector<int>& As, int S, int E)
	{
		// (S + x[0] * As[0] + x[1] * As[1] + ... + x[k] * As[k] ) % 7 = E
		
		int w = (E - S + 7) % 7;
		 
		if (!gauss.check(As))
		{
			if (gauss.query(As) != w)already_crazy = true;
		}
		else
		{
			gauss.push(As, w);
		}

	};

	auto Eat = [&](const std::vector<int> & As, int S) -> std::string
	{	
		if (already_crazy) return "Already crazy";

		if (gauss.check(As)) return "Don't know";
		int res = (S + gauss.query(As)) % MOD;
		return weekday_names[res];
	};
	

	for (int i = 0; i < N; ++i)
	{
		std::cin >> cmd;
		if (cmd == "Add")
		{
			honeys.push_back(-1);
		}
		else if (cmd == "Learn")
		{
			std::vector<int> As;
			std::string S, E;
			int K = honeys.size();
			for (int i = 0; i < K; ++i)
			{
				int A;
				std::cin >> A;
				As.push_back(A % 7);

			}
			std::cin >> S >> E;

			Learn(As, weekdays.at(S), weekdays.at(E));
		}
		else if (cmd == "Eat" ) 
		{
			std::vector<int> As;
			std::string  S;
			int K = honeys.size();
			for (int i = 0; i < K; ++i)
			{
				int A;
				std::cin >> A;
				As.push_back(A % 7);
			}

			std::cin >> S;
			std::cout << Eat(As, weekdays.at(S)) << std::endl;
		}
	}
	return 0;
}
 
int main(int argc, char* argv[])
{

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif //ONLINE_JUDGE
	
 	int tc = 1;
	//scanf("%d", &tc);
	while (tc--)
	{
		solve();
	}
	return 0;
}
