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

using str = std::string;

using pair_str = std::pair<str, str>;

class Solver
{
public:
	void set_number(str num)
	{
		number = num;
	}

	pair_str solve()
	{
		pair_str ss;
		const int n = size() / 2;
		for (int index = n * 2; index >= 0; --index)
		{
			if (solve(index, ss, false))
			{
				return ss;
			}
		}
		return {};
	}
	 
	pair_str solve_rec()
	{
		str a = number;
		str b;
		int const n = size() / 2;
		
		while (true)
		{
			b = a;
			if (!inc(b))
				break;
			if (is_lucky(a) && is_lucky(b))
				return pair_str(a, b);
			a = b;
		}
		return {};
	}
	pair_str min_cc(pair_str a, pair_str b)
	{
		if (a.first.empty()) return b;
		if (b.first.empty()) return a;
		if (a.first < b.first)return a;
		return b;
	}

	bool solve(int index, pair_str& res, bool incremented)
	{
		const int n = size()/2;
		
		if (index == n * 2 ) 
		{
			res.first  = number;
			res.second = number;
			if (inc(res.second) && is_lucky(res.first) && is_lucky(res.second))
				return true;
			return false;
		}
		 
		if (index >= n)
		{
			pair_str cc[2];
			
			std::pair<int, int> EF = find_A(index, incremented);
			cc[0] = fill(EF.first, EF.second, index, incremented);
			EF = find_B(index, incremented);
			cc[1] = fill(EF.first, EF.second, index, incremented);
			//if (std::min(EF.first, EF.second) / 9 <= (2 * n - index + 1))
			{
				EF.first += 9;
				EF.second += 9;
				pair_str ccv = fill(EF.first, EF.second, index, incremented);
				cc[1] = min_cc(cc[1], ccv);
				//if (ccv.first.size())break;
			}
			res = min_cc(cc[0], cc[1]);
			return !res.first.empty();
		}

		// index <  n
		//assert(n - index < 3);
		struct on_exit_t 
		{ 
			str dump; 
			Solver * this_; 
			~on_exit_t() { this_->number = dump; } 
		} on_exit = { number, this };

		for (int i = index + 1; i < n * 2; ++i)number[i] = '0';
		int c_start = number[index] + (incremented ? 0 : 1);
		for (int c = c_start; c <= '9'; ++c)
		{
			number[index] = c;
			int new_index = index + 1;
			if (solve(new_index, res, true))
			{
				return true;
			}
		}
		return false;
	}
	
	std::pair<int, int> find_A(int index, bool incremented)
	{
		const int n = number.size() / 2;

		int C = 0, D = 0, E = 0, F = 0;
		for (int i = 0; i < n; ++i) {
			if (i % 2 == 0) C += number[i] - '0'; else D += number[i] - '0';
		}
		for (int i = n; i <= index; ++i) {
			if (i % 2 == 0) E += number[i] - '0'; else F += number[i] - '0';
		}

		// C + D == E + F
		// C + E + 1 == D + F - 9
		// C - D = F - E - 10
		// 2*F = 2*C + 10

		// F = C + 5 = (C - 4) + 9

		// E = D - 5
		int min_F = 9;
		if (index == 2 * n - 1)
			min_F = '9' - number[index];

		int Fq = C + 5 - F;
		int Eq = D - 5 - E;

		if (Fq < min_F || Eq < 0) return { -1, -1 };
		return { Eq, Fq };
		// [ 0.. n-1 ][ n .. index ] [index + 1 ... 2n - 1]
		//Fq += 9;
	}

	pair_str fill(const int Eq, const int Fq, int index, bool incremented)
	{
		int const n = number.size() / 2;
		pair_str ss;
		int min_F = 9;
		if (index == 2 * n - 1)
			min_F = '9' - number[index];

		if (Eq < 0 || Fq < min_F) return ss;

		ss.first = number;
		
		str& a = ss.first;
		
		for (int i = index + 1; i < 2 * n; ++i) a[i] = '0';

		int eq = Eq, fq = Fq;

		if (!incremented) {
			if (index % 2 == 0)
			{
				if (eq == 0 || a[index] == '9') return {};
				a[index]++;
				eq--;
			}
			else {
				if (fq == 0 || a[index] == '9') return {};
				a[index]++;
				fq--;
			}
		}

		for (int i = 2 * n - 1; i >= index; --i) 
		{
			if (i % 2 == 0) {
				a[i] += std::min(eq, 9);
				eq -= std::min(eq, 9);
			}
			else {
				a[i] += std::min(fq, 9);
				fq -= std::min(fq, 9);
			}
		}
		
		if (a[index] > '9')
		{
			return {};
		}


		ss.second = a;
		if (inc(ss.second) && is_lucky(ss.first) && is_lucky(ss.second))
			return ss;
		
		int last_not_nine = 2 * n - 1;
		
		while (last_not_nine > 0 && a[last_not_nine] == '9')
			--last_not_nine;
		
		
		if (last_not_nine >= index)
		{
			int L9 = 2 * n - 1 - last_not_nine;
			if (L9 % 2 == 0)
			{
				//  zx9999
				//
				int i_inc = last_not_nine - 1;
				while (i_inc >= index && a[i_inc] == '9')
					i_inc -= 2;
				if (i_inc >= index && a[i_inc] < '9')
				{
					a[i_inc] ++;
					a[last_not_nine + 1] --;
				}
			}
			else if (L9 > 1){
				//  zx999
				a[last_not_nine]++;
				a[2 * n - 2]--;
			}

			ss.second = a;
			if (inc(ss.second) && is_lucky(ss.first) && is_lucky(ss.second))
				return ss;
		}
		
		return {};
	}
	
	std::pair<int,int> find_B( int index, bool incremented)
	{
		const int n = number.size() / 2;

		int C = 0, D = 0, E = 0, F = 0;
		for (int i = 0; i < n; ++i) {
			if (i % 2 == 0) C += number[i] - '0'; else D += number[i] - '0';
		}
		for (int i = n; i <= index; ++i) {
			if (i % 2 == 0) E += number[i] - '0'; else F += number[i] - '0';
		}
		// C - D ==  F - E
		// C + D == E + 1 - L*9 + F - 9 - L*9
		// 
		// 2*C = 2*F -8 - 2*L*9
		//
		// F = C + 4 + L*9
		// 2 * D = 2 * E - 8 - 2 * L * 9
		// E = D + 4 + L * 9
		int min_F = 9;
		if (index == n * 2 - 1)
			min_F = '9' - number[index];

		int Fq = C + 4 - F;
		int Eq = D + 4 - E;

		if (Fq < min_F || Eq < 0)
		{
			Fq += 9;
			Eq += 9;
			if (Fq < min_F || Eq < 0) return { -1, -1 };
			else return { Eq, Fq};
		}
		return {Eq, Fq};
		// [ 0.. n-1 ][ n .. index ] [index + 1 ... 2n - 1]
	}

	static bool is_lucky(str const & s) 
	{
		const int n = s.size() / 2;

		int sum_L[2] = { 0, 0 };
		int sum_R[2] = { 0, 0 };

		for (int i = 0; i < n; ++i)
		{
			sum_L[i & 1] += s[i] - '0';
			sum_R[(i + n) & 1] += s[i + n] - '0';
		}

		return sum_L[0] + sum_L[1] == sum_R[0] + sum_R[1] ||
			   sum_L[0] + sum_R[0] == sum_L[1] + sum_R[1];
	}

	static bool inc(str & s)
	{
		int n = s.size();
		int q = 1;
		int i = n - 1;
		while (i >= 0 && s[i] == '9') 
			s[i--] = '0';

		if (i >= 0)
		{
			++s[i];
			return true;
		}
		else {
			return false;
		}	
	}

	int size() const { return number.size(); }
private:
	str number;
};


#define USE_RANDOM 0

static int solve()
{
	str num;

#ifndef USE_RANDOM
	{
		std::cin >> num;
		Solver solver;
		solver.set_number(num);
		
		pair_str ab = solver.solve();
		if (ab.first.empty()) std::cout << "No solution\n"; else std::cout << ab.first << " " << ab.second << std::endl;

#ifndef ONLINE_JUDGE
		solver.set_number(num);
		pair_str cd = solver.solve_rec();
		std::cout << "recurrent solution:\n";
		std::cout << cd.first << " " << cd.second << std::endl;
#endif
		return 0;
	}
#else

	int const num_length = 1024;
	num.resize(num_length);
	std::random_device rd;
	std::mt19937 gen{ rd() };
	std::uniform_int_distribution<int> dist( static_cast<int>('0'), static_cast<int>('9') );

	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < num_length/2; ++j)num[j] = dist(gen);
		for (int j = num_length / 2; j < num_length; ++j)num[j] = '9';
		for (int j = num_length / 2; j >= num_length / 2 - 9; --j)num[j] = '9';

		Solver ss;

		ss.set_number(num);
		auto start_time = std::chrono::high_resolution_clock::now();
		pair_str ab = ss.solve();
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish_time - start_time);
		if (elapsed > std::chrono::milliseconds(500))
		{
			std::cout << "num = " << num << " elapsed time : " << elapsed.count() << " ms\n";
			std::cout << "a   = " << ab.first << " " << ab.second << "\n";
			return 0;
		}
		str a = ab.first;
		str b = ab.second;


#if 0
		ss.set_number(num);
		pair_str cd = ss.solve_rec();
		//std::cout << " recursive solution: " << cd.first << ' ' << cd.second << '\n';
		if (cd != ab) {
			std::cout << "num = " << num << " FAIL solve:\nab = " << ab.first << ", " << ab.second << "\n"
				<< "cd = " << cd.first << ", " << cd.second << "\n";
			return 0;
		}
#endif
	}
#endif // END USE_RANDOM

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
