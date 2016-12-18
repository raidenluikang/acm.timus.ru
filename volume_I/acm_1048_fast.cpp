
#pragma comment(linker,"/STACK:16777216")


#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifdef _MSC_VER  // visual studio c/C++
__declspec(align(128))
char in[1<<22];

__declspec(align(128))
char out[1 << 20];
#else

char in[1 << 22] __attribute__((aligned(128)));


char out[1 << 20] __attribute__((aligned(128)));


#endif
struct solver
{
	
	solver()
	{}

	int solve()
	{
		//read n
		unsigned n = 0;
		{
			int c = getc(stdin);
			while (c <= 32)c = getc(stdin);
			while (c >= 48) n = (n << 3) + (n << 1) + c - 48, c = getc(stdin);
			while (c != '\n')c = getc(stdin);
		}

		fread(in, 1, sizeof(in), stdin);
		 
		unsigned w = 0, v = 0;

		uint32_t const* o = (uint32_t const * ) in; // in 128 bit aligned
		uint32_t * p = (uint32_t  *)out;  // out 128 bit aligned

		for (unsigned i = 0, n4 = n >> 2; i != n4; ++i)
		{

#define O_TO_P(x,sh)  ( ((x & 0xFF) + ((x>>16) & 0xFF) - 48) << sh )

			p[i] = O_TO_P(o[0], 0) | O_TO_P(o[1], 8) | O_TO_P(o[2], 16) | O_TO_P(o[3], 24);

			o += 4;
			
			//if all 4 digits are 9 skip this
			if (   p[ i ]  == 0x39393939 )
			{
				continue;
			}
			
			// if p[i] last digit  > 57 ('9')  , 57 = 0x39
			if ( ( p[i] & 0xFF000000) > 0x39000000)
			{
				//p[i] -= 0x0A000000;
				//p[i] += 0x00010000;
				//   0x 0A 00 00 00 
				// -
				//   0x 00 01 00 00
				// -------------------
				//   0x 09 FF 00 00
			
				p[i] -= 0x09FF0000;
			}

			// if p[i] -3-rd digit > 57 ('9')
			if ((p[i] & 0x00FF0000) > 0x00390000)
			{
				// p[i] -= 0x 00 0A 00 00
				// p[i] += 0x 00 00 01 00
				// ----------------------
				// p[i] -= (0x 00 0A 00 00 - 0x 00 00 01 00)
				//   0x 00 0A 00 00
				// - 
				//   0x 00 00 01 00
				// -----------------
				//   0x 00 09 FF 00
				p[i] -= 0x0009FF00;
			}

			// if p[i] - 2-nd digit > 57 ('9')
			if ((p[i] & 0x0000FF00) > 0x00003900)
			{
				p[i] -= 0x000009FF;

			}


			//if p[i] -1-st digit > 57 ('9')
			if ((p[i] & 0xFF) > 0x39)
			{
				p[i] -= 0x0A;

				
				while ( v > 0 && out[v] == 0x39)--v;
				
				out[ v ]++;
				if (++v != (i << 2))
					memset(out + v, '0', (i << 2) - v);
			}
			v = ( i << 2 ) | 3;
		}

		while (v > 0 && out[v] == 0x39)--v;

		for (unsigned i = n & ~3; i != n; ++i)
		{
			out[i] = ((o[0] & 0xFF) + ((o[0] >> 16) & 0xFF)) - 48;
			++o;
			if (out[i] > 0x39)
			{
				out[i] -= 0x0A;
			
				out[v]++;
				if (++v != i)
					memset(out + v, '0', i - v);
				v = i;
			}
			else if (out[i] < 0x39)
			{
				v = i;
			}
		}

		out[n] = '\n';
		fwrite(out, 1, n+1, stdout);
		return 0;
	}
};


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
	
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	auto_cpu_timer cpu_timer;
#endif
	solver slv;
	slv.solve();
#if 0
	unsigned n = 1000 * 1000;
	printf("%d\n", n);
	for (unsigned i = 0; i != n; ++i)
	{
		printf("%c %c\n", '7', '1');
	}
#endif
}
