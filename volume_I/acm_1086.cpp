
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
	unsigned char mem[ 1 << 19 ] = {};
	int  primes[ 1 << 14] = {};
	int np = 0;
	mem[0] = mem[1] = true;
	for(int i = 2; i < 1024; ++i)
	{
		if ( ! mem[i])
		  for(int j =i *i; j < ( 1 << 19 ); j += i)
		    mem[j] = true;
	}
	
	for(int i = 0; np + 1 < 16384; ++i)
	{
		if (!mem[i])
		  primes[++np] = i;
	}
	
	int n = 0 ;
	read(n);
	for(int i = 0; i < n; ++i)
	{
		int pos = 0;
		read(pos);
		writeln(primes[pos]);
	}
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
