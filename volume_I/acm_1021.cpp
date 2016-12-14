

#include <cstdio>
#include <cstring>

static const unsigned char mask[ 8 ] = {1, 2, 4, 8, 16, 32, 64, 128};

char buffer[ 1 << 20 ] = {};
unsigned char bits[ 16384 ] = {};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif
 
	char const* o = buffer;
	unsigned int n = 0;
	
	n = fread(buffer, 1, sizeof(buffer)-1, stdin);
	buffer[n] = '\0';
	
    n = 0;
    while(*o && *o <= 32)++o;
    while(*o >='0' && *o <='9')n = n * 10  + *o++  - '0';
    for(unsigned i = 0; i != n; ++i)
    {
		unsigned const c = 32768; // middle   min(u + c) = -32768 + 32768 =  0 , max(u+c) = 32767 + 32768 = 65535
		unsigned u = 0;
		while(*o && *o <= 32)++o;
		
		bool sign = ( *o == '-' ) ? (++o, true) : (*o == '+' ? (++o, false) : false);
		while(*o >='0' && *o <='9') u = u * 10 + *o++ -'0';
		
		u = ( sign ) ? ( c - u ) : ( c + u );
		
		bits[ u >> 3 ] |= mask[u & 7 ];
	}
	
	n = 0;
	while(*o && *o <= 32)++o;
	while(*o>='0' && *o<='9') n = n * 10 + *o++ -'0';
	
	for(unsigned i = 0; i != n; ++i)
	{
		// u + x = 10000  --> x = 10000 - u 
		// y = x + 32768 = 10000 - u + 32768 = 42768 - u
		
		unsigned const c = 32768 + 10000;
		unsigned u = 0;
		while(*o && *o <= 32)++o;
		bool sign = ( *o == '-' ) ? (++o, true) : (*o == '+' ? (++o, false) : false);
		while(*o >='0' && *o <='9') u = u * 10 + *o++ -'0';
		
		u = (sign) ? (c + u ) : (c - u);
		
		if(bits[ u >> 3 ] & mask[ u & 7 ] )
		{
			puts("YES");
			return 0;
		}
	}
	
	puts("NO");
	
}
