
#include <bits/stdc++.h>

template<typename T>
void read(T& t){std::cin >> t;}
template<typename T>
void write(T const& t){ std::cout << t;}
template<typename T>
void writeln(T const& t){write(t); std::cout << '\n';}

int a[1<<17];
void solve()
{
	a[ 0 ] = 0;
	a[ 1 ] = 1;
	
	for(int i = 2; i + 1 < (1<<17); i += 2)
	{
		a[i] = a[i>>1];
		a[i+1] = a[i>>1] + a[ (i >> 1 ) + 1 ] ;
	}
	for(int i = 1; i < (1<<17); ++i)
	   a[i] = std::max(a[i], a[i-1]);
	
	int n = 0;
	do
	{
		read(n);
		if (n > 0)
		  writeln(a[n]);
	}while(n > 0);
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
