
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
int solve()
{
	unsigned n, m;
	m = fread(in, 1, sizeof(in), stdin);
	int state = 0;
	int nerr = 0;
	for (int i = 0; i != m; ++i)
	{
		char c = in[i];
		switch (state)
		{
		case 0:
			// start of sentience
			if (c >= 'a' && c <= 'z')
			{
				++nerr;
				//printf("i pos = %d\n", i + 1);
				state = 1;
			}
			else if (c >= 'A' && c <= 'Z')
			{
				state = 1;
			}
			break;
		case 1:
			// within sentience
			if (c >= 'a' && c <= 'z')
			{
				// nothing, no error
			}
			else if (c >= 'A' && c <= 'Z')
			{
				//printf("i pos = %d\n", i + 1);
				++nerr;
			}
			else if (c == '.' || c == '?' || c == '!')
			{
				state = 0;
			}
			else
			{
				state = 2;
			}
			break;
		case 2: // wait next word
			if (c >= 'a' && c <= 'z')
			{
				state = 1;
			}
			else if (c >= 'A' && c <= 'Z')
			{
				state = 1;
			}
			else if (c == '.' || c == '?' || c == '!')
			{
				state = 0;
			}
			break;
		} // end switch
	} // end for loop.

	printf("%d\n", nerr);
	//fwrite(out, 1, n, stdout);
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
