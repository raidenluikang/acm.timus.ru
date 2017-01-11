
// acm.timus.ru 1306 Median Sequence


//#pragma comment(linker, "/STACK:1048576")
#include <stdio.h>
#include <stddef.h>

#define N  250000
#define M  187512

//static const unsigned N = 250000;
//static const unsigned M = 187512 ;//( 250000 / 4 + 4 ) * 3;


unsigned d[ M ];
unsigned n;
char in[ 1 << 16 ];
char const* o;

unsigned readIntImpl()
{
	unsigned u = *o++ - '0';
	while( *o >= '0' && *o <= '9' ) u = (u << 3 ) + (u << 1) + (*o++ -'0');
	return ++o, u;
}

void load()
{
	size_t m;
	m = fread(in, 1, sizeof(in) - 4, stdin);
	o = in;
	in[ m ] = 0;
	in[ m + 1] = 0;
}

unsigned readInt()
{
	unsigned u;

	u = readIntImpl();
	
	if (*o == '\0') // reach end,  pre-load
	{
		int const b = o[ -1 ] == '\0' ;

		load();

		if ( b ) // continue read u
		{
			while(*o >= '0' && *o <='9') u = (u << 3 ) + (u << 1) + (*o++ - '0');
			++o;//skip space
		}
	}
	
	return u;
}

static void insertion_sort(unsigned * l, unsigned * r )
{
	unsigned * i;
	for( i = l ; i < r; ++i)
	{
		unsigned x = *i;
		
		unsigned * j = i - 1;

		// while (j >= 0 && A[j] > x ) 
		while ( j >= l &&  j[ 0 ] > x )
		{
			j[ 1 ] = j[ 0 ]; // A[j+1] = A[j]
			--j;             // j = j - 1
		}
		j[ 1 ] = x;  //A[j+1] = x
	}
}

static void order_statistics(unsigned * l,  unsigned* k, unsigned * r) // k-th element from [l..r)
{
	enum {THRESHOLD = 16};
	for( ;; )
	{
		unsigned * i = l;
		unsigned * j = r;
		unsigned * m = l + ( ( r - l ) >> 1 );
        unsigned curr = * m;
		unsigned t;
		
		if ( r - l < THRESHOLD ) // sort insertion
		{
			insertion_sort(l, r );
			return ;
		}
		
		do
		{
			while( i[ 0 ] < curr)++i;
			while( j[ -1 ] > curr)--j;
            if ( i < j )
			{
                t = i[0]; i[0] = j[-1]; j[-1] = t;
				--j; 
				++i;
			}
		}while( i < j );
        
		//   i >= j
		// 1. i == j  :   [L .. i) <= cur <=  [i..R)
		//if ( i == j)
		//{
	//		if (k >= i )l = i; // find in [i..R]
	//		else r = i; // find in [ L.. i)
	//	}
	//	else
	//	{
			// 2. i > j:  i == j + 1
			//  [L .. j)  <= A[j] = curr <= [i..R)

			// we can change this as: [L .. i ) <= curr <= [i .. R)

	//	}
		if (k >= i) l = i; else r = i;
	}
}


int solve()
{
	unsigned n, n2, i;
	load();

	n = readInt();
    n2 = n / 2;
	if ( n <= M )
	{
         // read all use order_statistics
		for( i = 0; i != n; ++i)
			d[ i ] = readInt();

		order_statistics(d, d + n2, d + n);
		if (n & 1 ) // odd
		{
			printf("%u\n", d[n2]);
			
		}
		else
		{
			unsigned x = d[ n2 ];
            unsigned y = d[0]; // max element d[ 0 ..  n2 - 1]
			for( i = 1; i < n2; ++i)
				y = (y < d[i]) ? d[i] : y;
			
			x += y;
			if (x & 1)
				printf("%u.5\n",x/2);
			else
				printf("%u\n", x/2);
		}
		return 0;
	}

	// n > M
	//so load first M numbers
	for( i = 0; i != M; ++i)
		d[i] = readInt();

	//use order_statistics(d, d + (n - M), d + M)
	order_statistics(d, d + (n - M), d + M);

	// d[0...(n-M-1)] -- numbers can't be median element nor near median element
	// so  read remain  n-M  elements to d[0..(n-M-1)]
	for( i = 0; i < n - M; ++i)
		d[i] = readInt();

	// we need n/2  median, but n-M  min elements already removed, so need n/2 - (n - M) -th statistics
	order_statistics(d, d + (n2 - (n- M)), d + M);
	if(n & 1) 
	{
		printf("%u\n", d[ n2 - (n- M)] );
	}
	else
	{
		unsigned x,y;
		x = d [ n2 - (n - M) ] ;
		y = d[ 0];
		for( i = 1; i < n2 - (n - M); ++i)
			y= (y < d[i]) ? d[i] : y; // maximum

		x += y;
		if (x & 1 )
			printf("%u.5\n",x/2);
		else
			printf("%u\n",x/2);
	}
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
