#include <cstdio>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>

enum class SortedState
{
	already_sorted,
	can_sorted,
	can_not_sorted
};

struct TResult
{
	enum SortedState state;
	std::size_t first;
	std::size_t second;
};

void printSortedState(enum SortedState state)
{
		switch(state)
		{
			case SortedState::already_sorted : printf("Nothing to do here\n"); break;
			case SortedState::can_sorted : printf("Yes\n");break;
			case SortedState::can_not_sorted: printf("No hope\n");break;
		}
}

bool IsSorted(const std::vector<int>& numbers)
{
   return std::is_sorted(numbers.begin(), numbers.end()) ||
          std::is_sorted(numbers.rbegin(), numbers.rend());	
}

TResult solve_simple(const std::vector<int> & numbers )
{
	const std::size_t size = numbers.size();
	std::vector<int> copy(numbers);
	
	for(std::size_t i = 0; i < size; ++i){
		for(std::size_t j = i + 1; j <  size; ++j)
		{
			std::swap(copy[i], copy[j]);
			if (IsSorted(copy)){
				return TResult{ SortedState::can_sorted, i, j};
			}
			//back again i-th and j-th elements.
			std::swap(copy[i], copy[j]);
		}
	}
	
	return TResult{ SortedState::can_not_sorted, 0,0};
}

template< typename Comparator> 
TResult solve_comp(const std::vector<int> & numbers, Comparator comparator)
{
	const std::size_t size = numbers.size();
	std::size_t count_diff = 0;
	for(std::size_t i = 0; i + 1 < size; ++i)
	{
		if ( comparator(numbers[i+1], numbers[i]) )
		  ++count_diff;
	}

	if (count_diff > 4) return TResult{ SortedState::can_not_sorted, 0, 0};
	
	std::vector<int> copy(numbers);
	std::vector<std::size_t> candidates;
	
	candidates.push_back(0);
	candidates.push_back(size-1);
	
	for(std::size_t i = 0; i + 1 < size; ++i)
	{
		if (comparator(numbers[i+1], numbers[i]))
		{
			candidates.push_back(i);
			candidates.push_back(i+1);
			
			std::size_t i_e = i;
			
			while(i_e > 0 && numbers[i] == numbers[i_e-1])
			   --i_e;
			
			candidates.push_back(i_e);
			
			i_e = i + 1;
			while(i_e + 1 < size && numbers[i+1] == numbers[i_e + 1])
			   ++i_e;
			
			candidates.push_back(i_e);   
		}
	}
	
	std::sort(candidates.begin(), candidates.end());
	candidates.erase(std::unique(candidates.begin(), candidates.end()), candidates.end());
	//printf("candidates:{ ");
	for(std::size_t i : candidates)
	{
		//printf("%d, ", (int)i + 1);
		for(std::size_t j : candidates)
		{
			if (i < j ){
				std::swap(copy[i], copy[j]);
				bool is_sorted = std::is_sorted(copy.begin(), copy.end(), comparator);
				std::swap(copy[i], copy[j]);
				
				if (is_sorted) return TResult{ SortedState::can_sorted, i, j};
			}
		}
	}
	//printf("}\n");
	
	return TResult{ SortedState::can_not_sorted, 0, 0};
}
 
TResult solve_heavy(const std::vector<int> & numbers)
{
	// numbers.size() > 10
	// and  numbers is not a sorted.
	TResult lessSorted = solve_comp(numbers, std::less<int>{});
	
	if (lessSorted.state == SortedState::can_sorted)
		return lessSorted;
	
	TResult greaterSorted = solve_comp(numbers, std::greater<int>{});
	
	if (greaterSorted.state == SortedState::can_sorted)
		return greaterSorted;
		
	return TResult{ SortedState::can_not_sorted, 0, 0 };
}

TResult solve(const std::vector<int> & numbers)
{
	if (IsSorted(numbers))
		return TResult{ SortedState::already_sorted, 0,0};
		
	else if (numbers.size() <= 10)
		return solve_simple(numbers);
	else
		return solve_heavy(numbers);
}

void solve()
{
	int  n;
	scanf("%d",&n);
	
	std::vector< int > numbers(n);
	
	for(int  i = 0; i != n; ++i)
		scanf("%d", &(numbers[i]));
	
	const TResult result = solve(numbers);
	
	printSortedState(result.state);
	
	if (result.state == SortedState::can_sorted)
		printf("%d %d\n", (int)result.first + 1, (int)result.second+1);
}

int main(int, char**)
{
	
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif	
	solve();
}
