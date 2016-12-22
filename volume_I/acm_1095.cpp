
#pragma comment(linker,"/STACK:16777216")


#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifdef _MSC_VER  // visual studio c/C++
__declspec(align(128)) char in[ (1<<18) + (1<<16) ];

//__declspec(align(128)) char out[1 << 16];
#else

char in[ (1<<18) + (1<<16)] __attribute__((aligned(128)));


//char out[1 << 16] __attribute__((aligned(128)));
#endif

static const char a[7][6] = { "3241", "1324", "1234", "2341", "1243", "1342", "2134" };
//                                     0 * 3 %7 = 0, 1*3 % 7 = 3, 2*3%7 = 6, 3*3 % 7 = 2, 4*3%7=5, 5*3%7=1, 6*3%7=4
static const unsigned char  mod7[7] = { 0, 3, 6, 2, 5, 1, 4 };
static const unsigned char  pow7[7] =
{
	( 7 - (0*4) % 7) % 7,
	( 7 - (1*4) % 7) % 7,
	( 7 - (2*4) % 7) % 7,
	( 7 - (3*4) % 7) % 7,
	( 7 - (4*4) % 7) % 7,
	( 7 - (5*4) % 7) % 7,
	( 7 - (6*4) % 7) % 7
};

static const unsigned char add[7][10] = 
{
{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 0 , 1 , 2 },
{ 1 , 2 , 3 , 4 , 5 , 6 , 0 , 1 , 2 , 3 },
{ 2 , 3 , 4 , 5 , 6 , 0 , 1 , 2 , 3 , 4 },
{ 3 , 4 , 5 , 6 , 0 , 1 , 2 , 3 , 4 , 5 },
{ 4 , 5 , 6 , 0 , 1 , 2 , 3 , 4 , 5 , 6 },
{ 5 , 6 , 0 , 1 , 2 , 3 , 4 , 5 , 6 , 0 },
{ 6 , 0 , 1 , 2 , 3 , 4 , 5 , 6 , 0 , 1 }
};

int solve()
{
	unsigned m, n = 0;
	m = fread(in, 1, sizeof(in), stdin);
	in[m] = '\0';
	const char * o = in;
	const char * out;
	
	while ( *o && *o <= 32)++o;
	while ( *o >= 48 && *o <= 57) n = (n << 3) + (n << 1) + *o++ - 48;
	while ( *o && *o != '\n')++o;

	out = ++o;

	for (unsigned i = 0; i != n; ++i)
	{
		char * s = (char*)o;
		unsigned char m = 0; // module 7
		unsigned char z = 0; // number of zero.
		unsigned char l = 0; // number of digits.
		bool visit[ 10 ] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
		
		while (*o >= 48 && *o <= 57)
		{
			char d = *o++ - 48;

			z += !(d);

			if ( d > 0 && visit[ d ])
				s[l++] = d + 48, m = add[ mod7[ m ] ][ d];

			visit[ d ] = true;
		}
		if (l == 0 && z > 0)
		{
			s[0] = '3'; s[1] = '2';s[2] = '4';s[3] = '1';
			l = 4;
			while (z-- > 0)s[l++] = '0';
		}
		else
		{
			while (z-- > 0)s[l++] = '0', m = mod7[m];
			m = pow7[m];// m = (7 - (m*10^4) %7 )%7
			s[ l++ ] = a[ m ][ 0 ];
			s[ l++ ] = a[ m ][ 1 ];
			s[ l++ ] = a[ m ][ 2 ];
			s[ l++ ] = a[ m ][ 3 ];
		}
		++o;//skip'\n'
	}
	
	if (o > out)
		fwrite(out, 1, o - out, stdout);
}

#ifndef ONLINE_JUDGE
#include <chrono>
struct auto_cpu_timer
{
	typedef std::chrono::high_resolution_clock::time_point point;
	point s, e;
	auto_cpu_timer()
	{
		s = std::chrono::high_resolution_clock::now();
	}
	~auto_cpu_timer()
	{
		e = std::chrono::high_resolution_clock::now();

		long int n;
		n = std::chrono::duration_cast<std::chrono::microseconds>(e - s).count();
		fprintf(stdout, "\nelapsed: %6ld microseconds\n", n);
	}
};
#endif

int main()
{
#ifndef ONLINE_JUDGE
	auto_cpu_timer cpu_timer;

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	solve();
	
}
