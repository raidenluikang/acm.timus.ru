
// acm.timus.ru 1021.  Sacrament of the Sum O(2*n) algo.
 
#include <cstdio>
#include <cstring> 
char buffer[ 1 << 16 ];
unsigned nb;
bool eof_ ;
const char* o; 
unsigned a[4096] = {};
 
int readInt()
{
	unsigned n = 0, s = 0;
	unsigned const rem = buffer + nb - o; 
	
	if ( rem < 64 && ! eof_ ) // reload
	{
		
		memcpy(buffer, o, rem );
		nb = fread(buffer + rem, 1, sizeof(buffer) - rem - 2, stdin);
		nb += rem;
		eof_ = nb < sizeof(buffer) - 2 ;
		o = buffer;
		buffer[nb] = '\0';
	}
	
	while(*o && *o <= 32)++o;
	
	if (*o == '+')++o;
	else if(*o == '-')++o, s = ~0;
	
	while(*o>='0') n = (n<<3) + (n<<1) + *o++  -'0';
	
	return ( n ^ s ) + !!s ;
}

 

int main()
{
	
 #ifndef ONLINE_JUDGE
      freopen("input.txt","r",stdin);
      freopen("output.txt","w",stdout);
 #endif 

    int n1,n2;

    unsigned n;
    o = buffer;
    nb = fread(buffer, 1, sizeof(buffer)-2, stdin);

    buffer[nb] = '\0';
    eof_ = nb < sizeof(buffer) - 2;
    
    n1 = readInt();
    for(int i = 0; i != n1; ++i){
		int x = readInt();
		x = 10000 - x;
		// x =[-32768 .. 32767]
		// 10000 - x = [-22767 .. 42768]
		// 
		x += 32768;
		a[x>>5] |= (1u << (x&31));
	}
    
    
    n2 = readInt();
    
    //a1[] - ascending order, i.e. a[0] <= a[1] <= ... <= a[n-1]
    
    for(int i = 0; i != n2 ; ++i)
    {
		int x = readInt();
		x += 32768;
		if (a[x>>5] & (1u << (x&31)))
		{
			puts("YES");
			return 0;
		}
	}
	puts("NO");
   return 0;
}  
