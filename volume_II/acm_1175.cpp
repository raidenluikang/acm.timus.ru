#include <cstdio>
#include <cstddef>
#include <map>
#include <utility>

static const size_t N = 10000;

typedef long long ll;

int a1, a2, a3, a4, b1, b2, c;

int F(int x, int y)
{
	int h = a1 * x * y + a2 * x + a3 * y + a4;
	if (h > b1) // h - c*k <= b2  -->  c*k >= h - b2
	{
		if (h > b2)
		{
			h -= ( ( h - b2 ) / c) * c ;
			while( h > b2) 
				h -= c;
		}
	}
	return h;
}


typedef std::pair<int,int> ii;
typedef std::map<ii, int> mii;

int main(int argc, char * argv[])
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int x1, x2;
    
    scanf("%d%d%d%d%d%d%d",&a1, &a2, &a3, &a4, &b1, &b2, &c);
    
    scanf("%d%d",&x1,&x2);

    mii m;

    m[std::make_pair(x1,x2)] = 1;
    for(int i = 3; true; ++i)
    {
    	int x3;
    	x3 = F(x1, x2);

    	x1 = x2; x2 = x3;
    	std::pair<int,int> p = std::make_pair(x1,x2);
    	if (m.count(p))
    	{
    		int pos = m[p];
    		int len = i - pos - 1;
    		printf("%d %d\n", pos, len);
    		return 0;
    	}

    	if (i < N )
    		m[ p ] = i - 1;

    	//if (i > 1000000)break;
    }
    
	return 0;
}

