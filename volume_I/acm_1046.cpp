

// acm.timus.ru 1046. Geometrical Dreams


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

static const int N = 56;
static const double PI = acos(-1.0);


struct point 
{
    double x,y ;
    
};
point operator + (point pa, point pb)
{
    point r = {pa.x + pb.x, pa.y + pb.y};
    return r;
}
point operator - (point pa, point pb)
{
    point r = {pa.x - pb.x, pa.y - pb.y};
    return r;
}

bool operator == (point pa, point pb)
{
    return fabs(pa.x - pb.x) < 1.0E-12 && fabs(pa.y - pb.y) < 1.0E-12;
}

point pm [ N ];
point res[ N ];
double ang[ N ];
double cos_a [ N ];
double sin_a [ N ];

int n;



point rotate(point p, double cos_, double sin_ )
{
    point r;
    r.x = p.x * cos_  - p.y * sin_ ;
    r.y = p.x * sin_  + p.y * cos_ ;
    return r;
}
int solve()
{

    scanf("%d",&n);
    for(int i= 1; i <=n; ++i)
    {
        scanf("%lf %lf",&(pm[i].x), &(pm[i].y));
    }
    for(int i= 1; i<=n;++i)
    {
        scanf("%lf",&(ang[i]));
        ang[i] = ang[i] * PI / 180.0;
        cos_a[i] = cos(ang[i]);
        sin_a[i] = sin(ang[i]);
    }
    point pa = {1.0 , 0.0};
    point pb = {0.0 , 0.0};

    for(int i=1; i<=n; i++)
    {
        pa = rotate(pa, cos_a[i], sin_a[i]);
        pb = rotate(pb, cos_a[i], sin_a[i]);
        pb = pb + pm[i] - rotate(pm[i], cos_a[i], sin_a[i]);
    }

    pa.x -= 1;
    pb.x = -pb.x;
    pb.y = -pb.y;

    point ans; 
    res[1].x = (pa.x*pb.x+pa.y*pb.y)/(pa.x*pa.x+pa.y*pa.y);
    res[1].y = (-pa.y*pb.x+pa.x*pb.y)/(pa.x*pa.x+pa.y*pa.y);
    ans  = res[1];
    for(int i = 1; i <= n; i++)
    {
        res[ i ] = ans;
        ans = pm[ i ] + rotate(ans - pm[i], cos_a[i], sin_a[i] );
    }
    for(int i = 1; i <=n; ++i)
    {
        printf("%.2f %.2f\n",res[i].x, res[i].y);
    }
    return 0;
}

int main(int argc, char * argv[])
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    
     solve();
    
    return 0;
}
