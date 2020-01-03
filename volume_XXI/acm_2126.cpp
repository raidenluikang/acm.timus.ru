#include <cstdio>
#include <cstdint>

using i64 = std::int64_t;

static constexpr
int power(int x, int n, int p)
{
     int r = 1;
     while(n>0){
		if (n%2 == 0){
			  x = (x*1ll*x)%p;
			  n/=2;
		}else{
		   r = (r*1ll*x)%p;
		   n --;
		}
	 }
	 return r;
}

static constexpr
int inverse(int x, int p){ return power(x, p-2,p);}
 
#define PMAX  (1<<20)
int fact[PMAX], fact_inv[PMAX];
static
void prepare(int p)
{
	fact[0] = 1;
	for(int i = 1; i < p ; ++i)
	{
		fact[i] = (fact[i-1] * 1ll*i) % p;
	}
	
	//fact_inv[i] = 1/i! = 1/(i+1)!  * (i+1) => fact_inv[i+1] * (i+1) % p
	// or i--> i-1 :  fact_inv[i-1] = fact_inv[i] * i % p
	// fact[p-1] = inverse(fact[p-1]);
	// but, we know that,  (p-1)! % p = -1 = 
	// (-1)^(p-2) = -1, because p - is odd, p-2 is odd.
	fact_inv[p-1] = p-1;
	for(int i = p-1; i > 0; --i)
	{
		fact_inv[i-1] = (fact_inv[i] * 1ll * i ) % p;
	}
}

static 
int F(int n, int k, int p)
{
     // n! / k! / k! / (n-2k)!
     //  fact[n] * fact_inv[k] * fact_inv[k] * fact_inv[n-2*k]
     int a = (fact[n] * 1ll * fact_inv[k]) % p;
     int b = (fact_inv[k] * 1ll * fact_inv[n - k - k]) % p;
     
     return (a * 1ll * b) % p;
}

static int solve(int n, int p)
{
	// n < p 
	int sum = 0;
	for(int k = 0; k + k <= n; ++k)
	{
		sum = (sum + F(n, k, p) ) % p;
	}
	return sum;	
}

void solve()
{
	int p;
	long long n;
	scanf("%lld %d",&n,&p);
	
	prepare(p);
		
	int result = 1;
	long long m = n;
	while(m>0){
		result = ( result * 1ll * solve( m % p, p ) ) % p ;
		m /= p;
	}
	
	//printf("result = %d\n", result);
	// 3^5 = 243 % 7 = 5           5-2=3 
	// 3^n = 3^((p-1)*a + q) = (3^(p-1))^a * 3^q = 1 * 3^q = 3^q, where q = n % p
	int p3 = power(3, n % (p-1), p);
	
	//printf("p3 = %d  n%(p-1) = %d  p = %d\n", p3, n%(p-1), p);
	result = (p3 - result + p) % p;
	
	result = (result + (result%2) * p ) / 2 ;
	
	printf("%d\n", result);
} 
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif	
	solve();  
}
