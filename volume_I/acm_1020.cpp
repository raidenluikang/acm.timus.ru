
#include <bits/stdc++.h>


void solve()
{
	int n  = 0;
	double r = 0.0;
	double x0, y0;
	double p = 0;
	double x1, y1;
	std::cin >> n >> r;
	std::cin >> x0 >> y0;
	x1 = x0;
	y1 = y0;
	for(int i = 1; i<n;++i)
	{
		double x2, y2;
		std::cin >> x2 >> y2;
		p += std::sqrt( ( x2 - x1 ) * ( x2 - x1 ) + ( y2 - y1 ) * ( y2 - y1 ) ) ;
		
		x1 = x2;
		y1 = y2;
		
	}
	
	p += std::sqrt( (x1 - x0) * ( x1 - x0) + (y1 - y0)*(y1-y0));
	
	p += 2*r * acos(-1.0);
	
	std::cout << std::fixed << std::setprecision(2) << p << '\n';
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
