
#include <bits/stdc++.h>

template<typename T>
void read(T& t){std::cin >> t;}
template<typename T>
void write(T const& t){ std::cout << t;}
template<typename T, typename U>
void write(T const& t , U const& u){ std::cout << t << u; }

void writeln(){ std::cout << '\n';}
template<typename T>
void writeln(T const& t){write(t); writeln();}

void solve()
{
	int n = 0;
	read(n);
	for(int i = 1; i<=n; ++i)write(i, ' ');
	writeln();
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
