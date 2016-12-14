
//Code Prufer  O(N) solution.

#include <cstdio>

#define N  128
  


int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif
    
  
    char buffer[65536] = {};
    char const*o = buffer;
    char * w = buffer;
    bool g[N][N] = {};
    int n = 0;
    
    n = fread(buffer, 1, sizeof(buffer)-2,stdin);
    buffer[n]  = '\0';
    
    n = 0;
    while(*o && *o<=32)++o;
    
    while(*o>='0' && *o<='9')
      n = (n<<3) + (n<<1) + *o ++  - '0';
      
    //printf("n = %d\n",n);
    //return 0;
    for(int i = 0; i != n; ++i)
    {
		int u ;
		do
		{
			u = 0;
			while(*o && *o<=32)++o;
    
			while(*o>='0' && *o<='9')
				u = (u<<3) + (u<<1) + *o ++  - '0';
			g[1+i][u] = true;
			g[u][1+i] = true;	
		}while( u > 0 );
	}
	
	for(int i = 1; i != N; ++i)
	   w[i] = '\0';
	
	int q[N];
	int h = 0, t = 0;
	q[t++] = 1;//first 
	w[1] = '0';
	
	while(h < t)
	{
		int i = q[h++];
		int color = w[i];
		
		for ( int j = 1; j != n + 1; ++j )
		{
			if ( g[ i ][ j ] )
			{
				if ( w[ j ] == '\0' )
				{
					w[ j ] = color ^ 1 ;
					q[ t++ ] = j;
				}
				else if ( w[ j ] == color )
				{
					puts("-1");
					return 0;
				}
			}
		}
	}
	
	puts(w+1);
	
    return 0;
}  
