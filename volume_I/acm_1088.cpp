
#pragma comment(linker,"/STACK:16777216")


#include <stdio.h>
#include <string.h>
#include <stdint.h>

int min_(int a, int b) { return a < b ? a : b;  }
int max_(int a, int b) { return a > b ? a : b;  }

int readInt()
{
	int n = 0;
	int c;
	while ((c = getc(stdin)) != EOF && c <= 32);
	n = c - 48;
	while ((c = getc(stdin)) != EOF && c >= 48 && c <= 57)
		n = (n << 3) + (n << 1) + c - 48;

	return n;
}

int a[32], b[32];

int solve()
{
	int D, E, F, Dp, Ep, H;
	D = readInt();
	E = readInt();
	F = readInt();
	Dp = readInt();
	Ep = readInt();
	H = readInt();

	int i = (1 << F), j, ans = 100000;
	int Di = Dp + i - 1;
	int Ei = Ep + i - 1;
	int ld = 0, le = 0, t1 = 0, t2 = 0;
	while (Di)
	{
		if (t1 >= D)
			a[ld++] = Di;
		t1++;
		Di >>= 1;
	}
	while (Ei)
	{
		if (t2 >= E)
			b[le++] = Ei;
		t2++;
		Ei >>= 1;
	}
	if (le == 0 && ld == 0) {
		puts("YES");
		return 0;
	}
	else if (le == 0 && ld != 0) {
		ans = F - D;
	}
	else if (le != 0 && ld == 0) {
		ans = F - E;
	}
	else {
		for (i = 0; i < ld; i++) {
			for (j = 0; j < le; j++) {
				if (a[i] == b[j])
					ans = min_(i + j, ans);
			}
		}
	}
	if (ans <= H)
		puts("YES");
	else
		puts("NO");
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
