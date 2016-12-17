
//acm.timus.ru 1032. Find a Multiple

#include <stdio.h>
#include <string.h>
#include <math.h>
 

char buffer[1 << 16] = {};
unsigned o ;



unsigned p[10001] = {};
 
void solve()
{
	unsigned m, n;
	m = fread(buffer, 1, sizeof(buffer)-4, stdin);
	n = 0;
	o = 0;
	
	//1. read n
	while(o != m && buffer[o] <= 32)++o;
	while(buffer[o] >= 48) n = (n<<3) + (n<<1) + buffer[o++]  - 48;
	
	unsigned x = 0, s = 0;
	
	while(o != m && buffer[o] <= 32)++o;
	
	p[ 0 ] = o | ( 0 << 16 );
	
	for(unsigned i = 1; i <=n ;++i)
	{
		//read a[i]
		x = 0;
		while(buffer[o] >= 48 ) x = (x << 3) + (x << 1) + buffer[ o++ ] - 48;
		
		while(x>=n)x-=n;
		
		//x = a[i]
		s = (s + x) ;
		while(s>=n)s-=n;
		if ( p[ s ] )
		{
			unsigned o_start = p[s] & 0xFFFF;
			unsigned j = p[ s ] >> 16;
			unsigned ans = i - j;
			buffer[--o_start] = '\n';
			do  buffer[--o_start] = ans % 10 + '0'; while(ans/=10);
			fwrite(buffer + o_start, 1, o - o_start, stdout);
			return ;
		}
		while(o != m  && buffer[o] <= 32)++o;
		p[ s ] = o | ( i << 16);
	}
	
	puts("0");
}

int main(int argc, char **argv)
{
#ifndef ONLINE_JUDGE
 	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif
	
    solve();
	return 0;
}
