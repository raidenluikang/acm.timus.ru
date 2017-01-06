

#include <algorithm>
#include <cstdio>
#include <cmath>

const int maxn = 55;
const double inf = 1e40;
const double eps = 1e-9;

bool eq(double x, double y){ return abs(x- y)< eps;}
bool lt(double x, double y){ return x < y - eps; }
bool le(double x, double y){ return x <= y + eps; }
template<typename T> 
T sqr(T x){ return x * x ; }

struct pt
{
	double x, y;
	pt(){}
	pt(double X, double Y): x(X), y(Y) {}
	
	pt operator+ (const pt& p) {return pt(x+p.x, y+p.y);}
	pt operator- (const pt& p) {return pt(x-p.x, y-p.y);}
	double operator* (const pt& p) {return x*p.y - y*p.x;}
	pt operator* (const double& k) {return pt(x*k, y*k);}
	double dist(const pt& p) {return sqrt(sqr(x-p.x) + sqr(y-p.y));}
};

double sq(pt a, pt b, pt c)
{
	return 0.5 * ((b-a) * (c-a));
}

int n;
pt p[maxn];
double needsq;

typedef unsigned char byte;
byte nxt[maxn];
byte prv[maxn];
void init()
{
    for(int i= 0; i != n; ++i)
    {
        nxt[i] = i + 1;
        prv[i] = i - 1;
    }
    nxt[n - 1] = 0;
    prv[0]   = n - 1;
    
}
//int nxt(int i) {return (i == n-1) ? 0 : (i + 1);}
//int prv(int i) {return (i == 0) ? n-1 : (i - 1);}

double f(int i, double k)
{
	double lft = needsq;
	pt t = p[i] * ( 1 - k ) + p[ nxt[ i ] ] * k;
	int j = nxt[ i ];
	while (sq(t, p[j], p[nxt[j]]) < lft)
	{
		lft -= sq(t, p[j], p[nxt[j]]);
		j = nxt[j];
	}
	
	double cf = lft / sq(t, p[j], p[nxt[j]]);
	pt opp = p[j] * (1-cf) + p[nxt[j]] * cf;
	return t.dist(opp);
}

double solve()
{
    needsq = 0;
    
    for(int i= 0; i < n-2; ++i)
            needsq += sq(p[0], p[i+1], p[i+2]);

    needsq /= 2;

    double mn = inf;
    
    for(int i= 0; i < n; ++i)
    {
            double l = 0, r = 1, m1, m2, v1, v2;
            for(int III = 0; III < 40; ++III) 
            {
                    m1 = (l + l + r) / 3. ;
                    m2 = (l + r + r) / 3. ;
                    v1 = f(i, m1);
                    v2 = f(i, m2);
                    if (v1 > v2)
                            l = m1;
                    else
                            r = m2;
            }
            mn = std::min(mn, f(i, l));
    }
    return mn;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    
    scanf("%d",&n);
    for(int i= 0; i < n;++i)
        scanf("%lf%lf",&(p[i].x), &(p[i].y));

    init(); // init nxt and prv arrays.
    
    printf("%.4f\n",solve());	
	return 0;
}
