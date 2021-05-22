// https://www.cnblogs.com/psimonw/p/11801023.html
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector <int> poly;
const int N = 1 << 21, mod = 998244353, G = 3;
const ll infty = 1ll * mod * mod;
int power (int x, int y) {
	int ret = 1;
	y < 0 ? y += mod - 1 : 0;
	for ( ; y; y >>= 1, x = 1ll * x * x % mod) {
		if (y & 1) {
			ret = 1ll * ret * x % mod;
		}
	}
	return ret;
}
namespace {
	int adjust (int n) {
		int ret = 1;
		for ( ; ret < n; ret <<= 1);
		return ret;
	}
	poly trans (int n, int *a) {
		int m = adjust(n);
		poly ret; ret.resize(m, 0);
		for (int i = 0; i < n; ++i) {
			ret[i] = a[i];
		}
		return ret;
	}
	void dnt (int n, poly &_a, int sgn) {
		static int rev[N], a[N], wi[N];
		for (int i = 0; i < n; ++i) {
			rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
			a[i] = _a[rev[i]];
		}
		for (int l = 2, _w; l <= n; l <<= 1) {
			_w = power(G, (mod - 1) / l * sgn), wi[l >> 1] = 1;
			for (int i = (l >> 1) + 1; i < l; ++i) {
				wi[i] = 1ll * wi[i - 1] * _w % mod;
			}
		}
		for (int l = 2, m = 1; l <= n; m = l, l <<= 1) {
			for (int i = 0; i < n; i += l) {
				int *u = a + i, *v = a + i + m, *w = wi + m;
				for (int j = 0, x, y; j < m; ++u, ++v, ++w, ++j) {
					x = *u, y = 1ll * (*v) * (*w) % mod;
					*u = (x + y) % mod, *v = (x - y + mod) % mod;
				}
			}
		}
		int coe = power(n, sgn > 0 ? 0 : -1);
		for (int i = 0; i < n; ++i) {
			_a[i] = 1ll * a[i] * coe % mod;
		}
	}
	poly conv (int n, poly a, poly b) {
		n <<= 1, a.resize(n, 0), b.resize(n, 0);
		dnt(n, a, 1), dnt(n, b, 1);
		for (int i = 0; i < n; ++i) {
			a[i] = 1ll * a[i] * b[i] % mod;
		}
		dnt(n, a, -1);
		return a;
	}
}
poly A, B, C;
int n, m, ans;
int a[N], b[N], fac[N], ivf[N], _fac[N], _ivf[N];
void prework () {
	fac[0] = 1;
	for (int i = 1; i <= n + m + 1; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % mod;
	}
	ivf[n + m + 1] = power(fac[n + m + 1], mod - 2);
	for (int i = n + m; ~i; --i) {
		ivf[i] = 1ll * ivf[i + 1] * (i + 1) % mod;
	}
}
int main () {
	scanf("%d%d", &n, &m), --n, prework();
	for (int i = 0; i <= n; ++i) {
		scanf("%d", &a[i]);
		a[i] = 1ll * a[i] * ivf[i] % mod * ivf[n - i] % mod;
		a[i] = ((n - i) & 1 ? mod - a[i] : a[i]);
	}
	for (int i = 0; i <= n + m; ++i) {
		b[i] = power(i, mod - 2);
	}
	A = trans(n + m + 1, a), B = trans(n + m + 1, b);
	C = conv(A.size(), A, B);
	for (int i = n + 1; i <= n + m; ++i) {
		ans = 1ll * fac[i] * ivf[i - n - 1] % mod * C[i] % mod;
		printf("%d ", ans);
	}
	return 0;
}
