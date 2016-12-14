
#include <bits/stdc++.h>

template<typename T>
void read(T& t){std::cin >> t;}
template<typename T>
void write(T const& t){ std::cout << t;}
template<typename T>
void writeln(T const& t){write(t); std::cout << '\n';}
void solve()
{
	int n  = 0;
	int s[12][100] = {};
	read(n);
	s[0][0] = 1;
	for(int i= 1; i<=n/2; ++i)
	{
		for(int d = 0; d <= 9; ++d)
		{
			//m = m1m2m3..mkd
			//m1+m2+m3+..+mk = t
			//t + d --> a new number
			for(int t = 0; t < 100 - d; ++t)
			   s[ i ][ t + d ] += s[ i - 1 ][ t ];
		}
	}
	int r = 0;
	for(int t = 0; t < 100; t++)
	   r += s[ n / 2 ][ t ] * s[ n / 2 ][t];
	if(n&1) r *= 10;
	
	writeln(r);
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
