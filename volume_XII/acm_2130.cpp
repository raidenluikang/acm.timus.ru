
#include <cstdio>
#include <cstdint>

using i64 = std::int64_t;

char in[1<<21], *o;
static int nextInt()
{
	int x = 0;
	while(!(*o>=48 && *o <=57))++o;
	while(*o>=48 && *o <= 57)
	  x = x * 10 + (*o++ - 48);
	 return x;
}

static i64 gcd(i64 x, i64 y)
{
	i64 m;
	while(y != 0 ){
		m = x % y;
		x = y;
		y = m;
	}
	return x;
}

static void print_others(int nerror, int nsuccess, i64 lcm)
{
	char* w = in;
	
	char buf[20];
	int f = 20;
	buf[--f] = '\n';
	do{
		buf[--f] = 48 + lcm % 10;
		lcm/=10;
	}while(lcm>0);
	
	for(int i = 0; i < nsuccess; ++i)
	{
		for(int j = f; j < 20; ++j)
		  *w ++ = buf[j];
		  
	}
	for(int i= 0; i < nerror; ++i)
	{
		*w++ = '-';
		*w++ = '1';
		*w++ = '\n';
	}
	
	fwrite(in, 1, w - in, stdout);
	
}

static bool used[1<<20];

static void solve()
{
	int n = nextInt();//scanf("%d",&n);
	i64 lcm = 1;
	constexpr i64 LCM_MAX = 1000000000000ll;
	
	for(int i = 0; i < n; ++i)
	{
		int d = nextInt();
		int t = nextInt();
		
		if (t == 0){
			if (lcm % d == 0)
			{
				return print_others( n - i, i, lcm);
			}
			int g = gcd(lcm, d);
			g = d/g;
			used[g] = true;
		} else {
			int g = gcd(lcm,d);
			g = d/g;
			
			lcm *=g;
			 
			if (lcm > LCM_MAX)
				return print_others(n - i, i, lcm/g);
				
			for(int k= 1; k * k <= g;++k)
			{
				if (g % k == 0 ){
					if (used[k] || used[g/k]) return print_others(n-i, i, lcm/g);
				}
			}
		}
		//printf("%lld\n", (long long)lcm);
	}
	return print_others(0, n, lcm);
}

int main(int, char**)
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	
	o = in;
	in[fread(in,1,sizeof(in)-4,stdin)]= 0;
	
	solve();
	
	return 0;
}
