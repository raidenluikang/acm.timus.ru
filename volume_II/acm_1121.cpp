
// acm.timus.ru 1306 Median Sequence

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int H, W;
unsigned d[160][160];


char in[ 1 << 18 ];
char const* o;
char * w;

void write_1()
{
	*w++ = '-';
	*w++ = '1';
	*w++ = ' ';
}
void writeInt(unsigned u)
{
	unsigned v = u, n = 0;
	do ++n; while(v /= 10);
	v = n;
	while(v-->0)w[v] = u%10 + '0', u/=10;
	w += n;
	*w++ = ' ';
}

unsigned readInt()
{
	unsigned u = 0;
	while(*o && *o <= 32)++o;
	while( *o >= '0' && *o <= '9' ) u = (u << 3 ) + (u << 1) + (*o++ -'0');
	return u;
}

void load()
{
	size_t m;
	m = fread(in, 1, sizeof(in) - 4, stdin);
	o = in;
	in[ m ] = 0;
	in[ m + 1] = 0;

	w = in;
}


int solve()
{
	load();
	H = readInt();
	W = readInt();

	for(int i = 0; i != H; ++i)
	{
		for(int j = 0; j != W; ++j)
		{
			d[i][j] = readInt();
		}
	}
	
	int dx[ 6 ][ 140 ]; 
	int dy[ 6 ][ 140 ];
	int dn[ 6 ] = {};
	for(int x = -5; x <= 5; ++x)
	{
		for(int y = -5; y <= 5; ++y)
		{
			int i = abs(x) + abs(y);
			if (i < 6)
			{
				dx[ i ][ dn[ i ] ] = x;
				dy[ i ][ dn[ i ] ] = y;
				++dn[ i ];
			}
		}
	}
    
	for(int i = 0; i != H; ++i)
	{
		for(int j = 0; j != W; ++j)
		{
			if (!d[i][j])
			{
				unsigned h = 0;
				
				if (i - 5 < 0 || i + 5 >= H || j - 5 < 0 || j + 5 >= W )
				{
					for(int l = 1; l < 6 && h == 0; ++l)
					{
						int n = dn[l];
						for(int k = 0; k < n; ++k)
						{
							if (dx[l][k] + i >= 0 && dx[l][k] + i < H &&
								dy[l][k] + j >= 0 && dy[l][k] + j < W)
							
								h |= d[  dx[ l ][ k ] + i ] [ dy[ l ][ k ] + j ];

						}
					}
				}
				else
				{
					for(int l = 1; l < 6 && h == 0; ++l)
					{
						int n = dn[l];
						for(int k = 0; k < n; ++k)
						{
								h |= d[  dx[ l ][ k ] + i ] [ dy[ l ][ k ] + j ];
						}
					}
				}
				
				writeInt(h);
			}
			else
			{
				write_1();
				//e[i][j] = -1;
			}
		} // end j = 0..W-1

		w[-1] = '\n';
	}// end i = 0..H-1

	
	fwrite(in,1,w-in,stdout);
	
	return 0;
}

int main(int argc, char * argv[])
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif 
	
	//printf("total size( d[] + in [] ) = %u\n", sizeof(d) + sizeof(in) ) ;
	solve();
}
