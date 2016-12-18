
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
		
		for (unsigned i = 0; i != n; ++i)
		{
			out[i] = (o[0] & 0xFF) + ((o[0] >> 16) & 0xFF) - 48;
			++o;
			if (out[i] < 57) { v = i; }
			else if (out[i] > 57){
				out[i] -= 10; 
				out[v++]++; 
				memset(out + v, '0', i - v);
				v = i;
			}
		}
	
		fwrite(out, 1, n, stdout);
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
