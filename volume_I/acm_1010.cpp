

// acm.timus.ru 1010. Discrete Function.

#include <cstdio>


  
char buffer[ (1 << 21) ];
char const * o ;


void initRead()
{
	unsigned n;
	n = fread(buffer, 1, sizeof(buffer ) - 2, stdin);
	buffer[n] = '\0';
	o = buffer;
}
unsigned readInt()
{
	unsigned u = 0;
	while(*o  && *o <= 32)++o;
	while(*o >='0' && *o <= '9') u = (u<<3) + (u<<1) + *o++ -'0';
	return u;
}
int readInt_s()
{
	unsigned u = 0, s = 0;
	while(*o && *o <= 32) ++o;
	if (*o == '+')
	   ++o;
	else if (*o == '-')
	   ++o, s = ~0;
	while(*o>='0' && *o <='9')
	  u = (u<<3) + (u<<1) + *o++  -'0';
	
	return (u ^ s ) + !!s;   
}

int solve()
{
	unsigned n;
	long long a, b, c, d = -1000000000000000000LL;
	unsigned j = 0;
	
	initRead();
	
	n = readInt();
	
	a = readInt_s();
	
	for(unsigned i = 1; i != n; ++i, a = b)
	{
		b = readInt_s();
		c = (b-a);
		if ( c > d  )
		{
			j = i;
			d = c;
		}
		else if (-c > d)
		{
			j = i;
			d = -c;
		}
	}
	
	printf("%u %u\n",j,j+1);
	return 0;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif

    solve();
    
    return 0;
}  
