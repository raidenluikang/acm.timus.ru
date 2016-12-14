
// acm.timus.ru  1028 Stars. Used Segment Tree.

#include <cstdio>


  
char buffer[ (1 << 19) ];
char const * o ;
char * w;

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
void initWrite()
{
	w = buffer;
}
void writeInt(unsigned u, char c)
{
	 
	unsigned v = u, vn = 0;
	do ++vn; while(v/=10);
	
	 
	v = vn;
	while(vn-->0)w[vn] = u%10 + '0', u/=10;

	w += v;
	*w++ = c;
}
void flushBuffer()
{
	if (w !=buffer)
	{
		fwrite(buffer, 1, w - buffer, stdout);
		w = buffer;
	}
}
unsigned frequence[15001] = {};
 
unsigned level[ 65536 ] = {};

int solve()
{
	unsigned n,x,y,u,l;
    initRead();
    initWrite();
    
    n = readInt();
    for(unsigned i = 0; i != n; ++i)
	{   
		x = 1 + readInt();
		y = 1 + readInt();
		(void)y;
		//1. add it and 
		
		//u = 1;
		l = x + 32768;
		u = level[ l ]++;
		while( l > 1)
		{
			if (l & 1 ) u += level[ --l ];
			++level[ l >>= 1 ];
		} 
		//if (u>=15001)
		 
		// u - level of i-th star
		frequence[u]++;
	}    
     
    //write data
    for(unsigned i = 0; i != n; ++i)
    {
		writeInt(frequence[i],'\n');
		
	}
	flushBuffer();
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
