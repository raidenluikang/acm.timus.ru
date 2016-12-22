
#pragma comment(linker,"/STACK:16777216")


#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifdef _MSC_VER  // visual studio c/C++
__declspec(align(128))
char in[1<<16];

__declspec(align(128))
char out[1 << 16];
#else

char in[1 << 16] __attribute__((aligned(128)));


char out[1 << 16] __attribute__((aligned(128)));
#endif

unsigned char mask[ 128 ];
unsigned char domino[128][2];
unsigned n;

struct status
{
	unsigned char ngroup;
	unsigned char group[ 7 ];
	unsigned char freq [ 7 ];
};

struct ans_type
{
	unsigned char d[ 12 ][ 2 ];
	unsigned char n;
	unsigned char s;
};

ans_type rec(status const& st)
{
	ans_type res;
	if (st.ngroup == 1) // one single group
	{
		unsigned nodd = 0;
		unsigned char odds[ 6 ] = {};
		res.n = 0;
		res.s = 0;
		for (unsigned char i = 6; i > 0; --i)
		{
			if (st.freq[ i ] & 1) {
				odds[nodd++] = i;
			}
		}
		while ( nodd > 2 )
		{
			unsigned i = odds[ nodd - 1 ], j = odds[ nodd - 2 ];
		
			res.s += i + j;
			res.d[ res.n ][ 0 ] = i;
			res.d[ res.n ][ 1 ] = j;
			res.n++;

			nodd -= 2;
		}

		return res;
	}

	// find minimum sum, so...
	res.n = 0;
	res.s = 255;//max unsigned char
	for (unsigned char i = 1; i <= 6; ++i)
	{
		for (unsigned char j = i + 1; j <= 6; ++j)
		{
			if (st.group[i] != st.group[j] && st.group[i] > 0 && st.group[j] > 0)
			{
				// add (i,j) domino
				ans_type r2;
				status s2 = st;
				s2.freq[ i ]++ ;
				s2.freq[ j ]++ ;
				
				for (unsigned char d = 1; d <= 6; ++d)
					if (s2.group[d] == st.group[i])
						s2.group[d] = st.group[j];
				//s2.group[i] = st.group[j]; // now i and j digits in same group.
				s2.ngroup   = st.ngroup - 1;

				r2 = rec( s2 );

				r2.s += i + j;//i and j also added
				r2.d[ r2.n ][ 0 ] = i;
				r2.d[ r2.n ][ 1 ] = j;
				r2.n++;

				if ( r2.s < res.s )
				{
					res = r2;
				}
			}
		}
	}
	return res;
}
int solve()
{
	unsigned m;
	m = fread(in, 1, sizeof(in), stdin);
	in[m] = '\0';
	const char* o = in;
	status st = {};
	ans_type res;
	
	n = 0;
	while (*o  && *o <= 32)++o;
	while (*o >= 48) n = (n << 3) + (n << 1) + *o++ - 48;


	for (unsigned i = 0; i != n; ++i)
	{
		while (*o && *o <= 32)++o;
		domino[i][0] = *o++ - '0';
		++o;
		domino[i][1] = *o++ - '0';
		
		// 2^6 + 2^5 = 64 + 32 = 96 < 256. - so unsigned char enough for mask.
		mask[i] = (1u << domino[i][0]) | (1u << domino[i][1]);

		st.freq[ domino[ i ][ 0 ] ] ++ ;
		st.freq[ domino[ i ][ 1 ] ] ++ ;
	}

	st.ngroup = 0;
	
	bool visit[128] = {};
	unsigned char queue[128] = {};
	unsigned h = 0, t = 0;

	for (unsigned i = 0; i != n; ++i)
	{
		if (visit[i])continue;
		visit[i] = true;
		h = t = 0;
		queue[t++] = i;
		
		unsigned g = ++st.ngroup;

		while (h < t)
		{
			unsigned u = queue[h++];
			
			st.group[ domino[ u ][ 0 ] ] = g ;
			st.group[ domino[ u ][ 1 ] ] = g ;

			for (unsigned v = 0; v != n; ++v)
			{
				if (!visit[ v ] && (mask[ u ] & mask[ v ]) != 0)
				{
					visit[ v ]   = true;
					queue[ t++ ] = v;
				}
			}
		}
	}


	//solve it.
	res = rec(st);

	//write result.
	//1. res.s
	char *w = out;
	if (res.s >= 10)
	{
		*w++ = res.s / 10 + '0';
		*w++ = res.s % 10 + '0';
		*w++ = '\n';
	}
	else
	{
		*w++ = res.s + '0';
		*w++ = '\n';
	}

	//2. res.n - number of added domino
	if (res.n >= 10)
	{
		*w++ = res.n / 10 + '0';
		*w++ = res.n % 10 + '0';
		*w++ = '\n';
	}
	else
	{
		*w++ = res.n + '0';
		*w++ = '\n';
	}

	//3. res.d[] - added dominos.
	for (unsigned char i = 0; i != res.n; ++i)
	{
		*w++ = res.d[i][0] + '0';
		*w++ = ' ';
		*w++ = res.d[i][1] + '0';
		*w++ = '\n';
	}

	//4. flush
	fwrite(out, 1, w - out, stdout);
	
	return 0;
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
