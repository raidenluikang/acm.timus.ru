
//Code Prufer  O(N) solution.

#include <cstdio>

#define N  128

static const unsigned mask[32] = {
	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 
	0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000,
	0x10000, 0x20000, 0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000,
	0x1000000, 0x2000000, 0x4000000, 0x8000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000
	
} ;  

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif
    
  
    char buffer[65536] = {};
    char const*o = buffer;
    char * w = buffer;
    unsigned g[ N ][ 4 ] = {};
    unsigned char degree[ N ] = {};
    
    unsigned int n = 0;
    
    n = fread(buffer, 1, sizeof(buffer)-2,stdin);
    buffer[n]  = '\0';
    
    n = 0;
    while(*o &&  *o <= 32)++o;
    
    while( *o>='0' && *o<='9')
      n = (n<<3) + (n<<1) + *o ++  - '0';
      
    for(unsigned int i = 1; i != n+1; ++i)
    {
		int u ;
		do
		{
			u = 0;
			while(*o && *o<=32)++o;
    
			while( *o >= '0' && *o <= '9')
				u = ( u << 3) + ( u << 1 ) + *o ++  - '0';
			
			g[i][u >> 5 ] |= mask[u & 31];
			//g[ 1 ][ u ] = true;
			degree[ i ] += !!u; // u = 0 --> !!0 = !1=0, u != 0 --> !!u= !0 = 1
		}while( u > 0 );
	}
	
	unsigned char  q[ N ];
	unsigned int t = 0, h = 0;
	for(unsigned int i = 1; i != n + 1; ++i)
	{
		if (!degree[i])
		  q[t++] = i;
	}
	while( h < t)
	{
		unsigned int u = q[h++];
		for(unsigned int i = 1; i != n + 1; ++i)
		{
			if ( g[ i ] [ u >> 5] & mask[u & 31] )
			{
				--degree[ i ];
				if (! degree[i])
				{
					q[ t++ ] = i;
				}
			}
		}
	}
	
	for( ; h > 0; --h)
	{
		unsigned int u = q[h-1];
		unsigned int v = u, vn = 0;
		do vn++; while( v /= 10 );
		v = vn;
		while(vn-->0)w[ vn ] = u % 10 + '0', u/=10;
		w += v;
		*w++ = ' ';
	}
	--w;
	*w = '\0';
	puts(buffer);
    return 0;
}  
