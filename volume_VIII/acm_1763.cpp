#include <cstdio>
#include <array>
#include <algorithm>
#include <cstring>
#include <cstdlib>

static constexpr int results[] = 
{ // 0  1  2  3  4  5
     0, 0, 0, 0, 0, 0,
/*Answer for n = 6 is*/  12,
/*Answer for n = 7 is*/  46,
/*Answer for n = 8 is*/  144,
/*Answer for n = 9 is*/  110,
/*Answer for n = 10 is*/ 312,
/*Answer for n = 11 is*/ 290,
/*Answer for n = 12 is*/ 670,
/*Answer for n = 13 is*/ 706,
/*Answer for n = 14 is*/ 1538,
/*Answer for n = 15 is*/ 1732,
/*Answer for n = 16 is*/ 3504,
/*Answer for n = 17 is*/ 4288,
/*Answer for n = 18 is*/ 8098,
/*Answer for n = 19 is*/ 10568,
/*Answer for n = 20 is*/ 19044,
/*Answer for n = 21 is*/ 26042,
/*Answer for n = 22 is*/ 45222,
/*Answer for n = 23 is*/ 64220,
/*Answer for n = 24 is*/ 108382,
/*Answer for n = 25 is*/ 158324,
/*Answer for n = 26 is*/ 261754,
/*Answer for n = 27 is*/ 390314,
/*Answer for n = 28 is*/ 635666,
/*Answer for n = 29 is*/ 962282,
/*Answer for n = 30 is*/ 1550244, 
/*Answer for n = 31 is*/ 2372372,
/*Answer for n = 32 is*/ 3792560,
/*Answer for n = 33 is*/ 5848746,
/*Answer for n = 34 is*/ 9299148,
/*Answer for n = 35 is*/ 14419296,
/*Answer for n = 36 is*/ 22838014,
/*Answer for n = 37 is*/ 35548790,
/*Answer for n = 38 is*/ 56153296,
/*Answer for n = 39 is*/ 87640646,
/*Answer for n = 40 is*/ 138180196,
/*Answer for n = 41 is*/ 216065986,
/*Answer for n = 42 is*/ 340223834,
/*Answer for n = 43 is*/ 532680994,
/*Answer for n = 44 is*/ 838025410,
/*Answer for n = 45 is*/ 1313251780,
/*Answer for n = 46 is*/
};
constexpr int K = 19;
constexpr int A[K] = {1, 2, -1, 1, -2, -1, -2, -3, 3, -1, 5, 2, 2, 1, -2, 0, -3, 0 ,-1};
constexpr int Prime = 1000'000'000 + 9;

using matrix = std::array< std::array<int, K>, K > ; 

void init_matrix(matrix& a)
{
	memset(&a, 0, sizeof(a));
	for(int i = 0; i < K; ++i) a[0][i] = (A[i]+Prime)%Prime;
	for(int i = 1; i < K; ++i) a[i][i-1] = 1;
} 

void mul_matrix(matrix const& a, matrix const& b, matrix & c)
{
	memset(&c, 0, sizeof(c));
	for(int i = 0; i < K; ++i)
	{
		for(int j = 0; j < K; ++j)
		{
			for(int x = 0; x < K; ++x)
			  c[i][j] = (c[i][j] + a[ i ][ x ] * 1ll * b[ x ][ j ] ) % Prime;
		}
	} 
}

void power_matrix(const matrix& a, int n, matrix& c)
{
	// c = a ^ n
	memset(&c, 0, sizeof(c));
	for(int i = 0; i < K; ++i)
	    c[i][i] = 1;
	    
	matrix d;
	matrix e = a;
	while(n > 0)
	{
		if (n % 2 == 0)
		{
			mul_matrix(e, e, d);
			e = d;
			n = n / 2;
		} else {
			// e=  a^x, c = a^m
			mul_matrix(c, e, d);
			c = d;
			n = n - 1;
		}
	}
}	
int solve(int n)
{
	if (n < 26 ) 
		return results[n];
	
	matrix a,b;
	
	init_matrix(a);
	
	power_matrix(a, n - 25, b);
	
	// b = a^(n-25)
	int r = 0 ;
	for(int i = 0; i < K; ++i)
	{
		r = (r + results[25 - i] *1ll* b[ 0 ][ i ])%Prime;
	}
	return r;
}

int main()
{
  int n; 
  scanf("%d",&n);
	printf("%d\n", solve(n));
	//if (n < 46)printf("results = %d\n", results[n] % Prime);
}
