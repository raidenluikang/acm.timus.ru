
// acm.timus.ru 1024. Permutations. 

#include <cstdio>
char buffer[65536];
struct scanner
{
	const char* o;
	scanner(const char * o_): o(o_){}
	unsigned readInt()
	{
		unsigned u = 0;
		while(*o && *o <= 32)++o;
		while(*o>=48)u=(u<<3) + (u<<1) + *o++ - 48;
		return u;
	}
};
unsigned gcd(unsigned a, unsigned b)
{
	unsigned m; 
	while(b)
	{
		m = a % b;
		a = b;
		b = m;
	}
	
	return a;
}

int solve()
{
     unsigned p[1024] = {};
     unsigned n = 0;
     n = fread(buffer, 1, sizeof(buffer)-2,stdin);
     buffer[n] = '\0';
     
     scanner sc(buffer);
          
     //std::cin >> n;
     n = sc.readInt();
     for(unsigned i = 1; i <= n ; ++i)
        p[i]= sc.readInt();
     
     unsigned res = 1;
     for(unsigned i = 1; i<=n; ++i)
     {
		 if (p[i] == 0)continue;
		 unsigned rn = 0;
		 unsigned j = i;
		 while(p[j] != 0)
		 {
			 unsigned p_j = p[j];
			 ++rn;
			 p[j] = 0;
			 j = p_j;
		 }
		 unsigned d = gcd(res, rn);
		 rn /= d;
		 res *= rn;
	 }
	 printf("%u\n",res);
	 //std::cout << res << '\n';
     return 0;
}
int main() 
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
     solve();
    return 0;
}
