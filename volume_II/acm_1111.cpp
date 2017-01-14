// 1111. Squares


#include <cstdio>
#include <cmath>
#include <algorithm>

static const int N = 50;
static const double EPS = 1.0E-8;

struct pt
{
    double x,y;
    pt():x(),y(){}
    pt(double x_, double y_):x(x_),y(y_){}
};

typedef pt vec;

vec operator - (pt a, pt b){ return vec(a.x-b.x,a.y-b.y);}
pt  operator + (pt a, pt b){ return pt(a.x + b.x, a.y + b.y);}
pt operator  * (pt a, double t){ return pt(a.x * t, a.y * t);}
pt operator  * (double t, pt a){ return a * t ; }
pt operator  / (pt a, double t){ return a * ( 1.0 / t ); }
double operator *(vec a, vec b){ return a.x * b.x + a.y * b.y;}
double operator ^(vec a, vec b){ return a.x * b.y - a.y * b.x; }

double length(vec v)
{
    return sqrt(v*v);
}

double distance(pt a, pt b)
{
    return length(a - b );
}

//segment [v..w]  to point p.
double distance(pt v, pt w, pt p)
{
    // Return minimum distance between line segment vw and point p
    double l2 = distance(v,w);
  //  const float l2 = length_squared(v, w);  // i.e. |w-v|^2 -  avoid a sqrt
    if (fabs( l2 ) < EPS) return distance(p, v);
//    if (l2 == 0.0) return distance(p, v);   // v == w case
  // Consider the line extending the segment, parameterized as v + t (w - v).
  // We find projection of point p onto the line. 
  // It falls where t = [(p-v) . (w-v)] / |w-v|^2
  // We clamp t from [0,1] to handle points outside the segment vw.

    double t = std::max(0.0, std::min(1.0 , ( (p-v)*(w-v) ) / l2 ) );
    vec proj = v + ( t * (w - v) );
    return distance(p, proj);
    //const float t = max(0, min(1, dot(p - v, w - v) / l2));
  //const vec2 projection = v + t * (w - v);  // Projection falls on the segment
  //return distance(p, projection);
}

struct square_t
{
    pt a;
    pt b;
    
    pt c;
    pt d;
};

bool inner(square_t const& s, pt p)
{
   
    pt o = (s.a + s.b)/2.0;//((s.a.x + s.b.x)/2.0, (s.a.y + s.b.y)/2.0); // center
    double d_op = distance(o, p);
    double radius = distance(o, s.a);
    
    if (d_op > radius + EPS)
        return false;
    
    vec oa = o - s.a;
    vec pa = p - s.a;
    
    if ((oa * pa) < -EPS)
        return false;
    
    vec ob = o - s.b;
    vec pb = p - s.b;
    
    if ((ob * pb) < -EPS)
        return false;
    return true;
}
double distance(square_t const& s, pt p)
{
    if (inner(s,p))
        return 0.0;
    
    // a c b d
    double l_1 = distance(s.a, s.c, p);
    double l_2 = distance(s.c, s.b, p);
    double l_3 = distance(s.b, s.d, p);
    double l_4 = distance(s.d, s.a, p);
    
    return std::min( std::min(l_1, l_2), std::min(l_3, l_4)) ;
}


int n;
pt p;
square_t q[ N ];
double   d[ N ];
int      h[ N ];

int solve()
{
    scanf("%d",&n);
    for(int i= 0; i !=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        q[i].a.x = x;
        q[i].a.y = y;
        
        scanf("%d%d",&x,&y);
        q[i].b.x = x;
        q[i].b.y = y;
        
        pt o = (q[i].a + q[i].b)/2.0;
        vec oa = o - q[i].a;
        vec oa_rot = vec(-oa.y, oa.x);
        
        q[i].c = o + oa_rot;
        q[i].d = o - oa_rot;
    }
    
    {
        int x,y;
        scanf("%d%d",&x,&y);
        p.x = x;
        p.y = y;
    }
    
    for(int i = 0; i != n; ++i)
    {
        d[i] = distance(q[i], p);
        
        h[i] = i;
    }
    
    for(int i = 0; i < n; ++i)
    {
        for(int j = i + 1; j < n; ++j)
        {
            double d_i = d[h[i]];
            double d_j = d[h[j]];
            
            if ( (d_i > d_j + EPS) || ( ( d_i > d_j - EPS) && h[i] > h[j] ) )
            {
                int t = h[i];
                h[i] = h[j];
                h[j] = t;
            }
        }
    }
    
    for(int i = 0; i != n; ++i)
    {
        printf("%d ", h[i]+1);
    }
    //printf("\n")
    return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt","w",stdout);
#endif 
    
    solve();
    
    return 0;
}
