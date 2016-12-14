
#include <bits/stdc++.h>

template<typename T>
void read(T& t){std::cin >> t;}
template<typename T>
void write(T const& t){ std::cout << t;}
template<typename T>
void writeln(T const& t){write(t); std::cout << '\n';}

int sum(int n)
{
	int s = 0;
	//
	if ( n > 0 )
	{
		//1 + 2 + 3 + .. + n = (n+1)*n/2
		s = (n * (n+1) ) / 2;
	}
	else
	{
		// +1 + 0 -1 - 2 - 3 - ... - n = 1 - (1 + 2 + 3 + .. + |n|) = 1 - n*(n+1)/2
		n = -n;
		s = 1 - (n * (n+1))/2; 
	}
	return s;
}
void solve()
{
	int n = 0;
	read(n);
	writeln(sum(n));
}

int main(int argc, char **argv)
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	::std::ios::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0);
	solve();
	return 0;
}
