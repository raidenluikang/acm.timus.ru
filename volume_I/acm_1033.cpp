
//acm.timus.ru 1033. Labyrinth

#include <stdio.h>
#include <string.h>
#include <math.h>
 

int main(int argc, char **argv)
{
#ifndef ONLINE_JUDGE
 	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif

     
     
	char buffer[4096];
	int n,m;
	m = fread(buffer, 1, sizeof(buffer)-4, stdin);
	
	buffer[m]  = 0;
	const char* o = buffer;
	while(*o && *o<=32)++o;
	n = 0;
	while(*o>=48) n =(n<<3) + (n<<1) + *o++ - 48;
	
	char table[40][40] = {};
	bool visit[40][40] = {};
	for(int i = 1; i <= n ; ++i)
	{
		while(*o && *o <= 32)++o;
		for(int j = 1; j<= n; ++j)
		{
			table[i][j] = *o++;
			if (table[i][j] != '.' && table[i][j] != '#')
			{
				fprintf(stderr, "ERROR table[%d][%d] = %c\n",i,j,table[i][j]);
			}
		}
	}
	
	for(int i= 0; i < 40; ++i)
	{
		visit[ 0 ][ i ] = true;
		table[ 0 ][ i ] = '#';
	}
	for(int i = 0; i < 40; ++i)
	{
		visit[ i ][ 0 ] = visit[ i ][ n + 1 ] = true;
		table[ i ][ 0 ] = table[ i ][ n + 1 ] = '#';
	}
	for(int i = 0; i < 40; ++i)
	{
		visit[ n + 1][ i ] = true;
		table[ n + 1][ i ] = '#';
	}
	
	int s = 0;
	
	int que[4096];
	int h = 0, t = 0;
	que[t++] = (1 << 8) | 1;
	visit[1][1] = true;
	que[t++] = (n << 8) | n;
	visit[n][n] = true;
	
	static const int dx[ 4 ]  = {1, 0, -1, 0};
	static const int dy[ 4 ]  = {0, 1, 0, -1};
	
	while( h < t)
	{
		int row = que[h] >> 8;
		int col = que[h] & 255;
		++h;
	   
	    for(int k = 0; k !=4; ++k)
	    {
			int r = row + dx[ k ];
			int c = col + dy[ k ];
			
			if (table[r][c] == '#')
			   ++s;
			else if (!visit[r][c])
			{
				visit[r][c] = true;
				que[t++] = (r << 8) | c;
			}
		}	
		
	}
	
	
	s -= 4;
	printf("%d\n", s*9);
	
	
 	return 0;
}
