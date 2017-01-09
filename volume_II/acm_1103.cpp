/* acm.timus.ru 1103. Pencils and Circles 
 *
 * Strategy:
 * Pick two points on the convex hull of the point set. If we form a circle with some other point,
 * the largest such circle will encompass all points, the second largest will encompass all points
 * except for one, etc. The angle formed by the two static points and the third that we pick will
 * be inversely proportional to the radius of the circle that they form (the specific location of
 * the third point on the circle does not affect the angle), so we find the median biggest angle
 * out of all angles that we can form accordingly, and use the points constituting that circle as
 * the answer.
 *
 * Performance:
 * O(n), runs the test suite in 0.031s using 548KB memory.
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

struct point
{
    int x;
    int y;
};

typedef point vector;

vector operator - (point a, point b)
{
    vector result = {a.x - b.x, a.y - b.y };
    return result;
}
point operator + (point a, vector v)
{
    point result = {a.x + v.x, a.y + v.y };
    return result;
}
point operator * (point a, int k)
{
    point result = {a.x * k, a.y * k };
    return result;
}
long long operator * (vector a, vector b)
{
    return a.x * 1ll * b.x + a.y * 1ll * b.y; 
}

long long operator ^ (vector a, vector b)
{
    return a.x * 1ll * b.y - a.y * 1ll * b.x;
}

struct cmp_point
{
    bool operator()(point a, point b)const
    {
        return ( a.x < b.x ) || ( a.x == b.x && a.y < b.y ) ;
    }
};

double dist(vector v)
{
    return sqrt( v * v + 0.0);
}



struct scanner
{
    char const* o;
    char in[131072];
    
    void init()
    {
        o = in;
        in[fread(in,1,sizeof(in),stdin)] = 0;
    }
    
    int readInt()
    {
        unsigned u = 0, s = 0;
        while(*o && *o <= 32)++o;
        if (*o == '-') s= ~0u, ++o; else if (*o == '+')++o;
        while(*o>='0') u = (u << 3) + (u << 1) + (*o++ - '0');
        return (u ^ s) + !!s;
    }
} sc ;

int n;
point p[ 5000 + 8 ];

struct angle
{
    double cos_;
    int i;
}angles[5000 + 8];

struct cmp_angle
{
    // angle > 0   angle < 180
    // cos(angle) = -1 .. +1
    // 
    bool operator ()(angle a, angle b)const{ return a.cos_ > b.cos_ ; }
};


int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    //I. readData.
    // ---------------------------------------------------------------
    
    sc.init();
    
    n = sc.readInt();
    for(int i= 0; i != n; ++i)
    {
        p[i].x = sc.readInt();
        p[i].y = sc.readInt();
    }
    // -----------------------------------------------------------------
    
    
    // II. find first point: minimum element.
    // swap minimum with first point
    {
        point * pm = std::min_element(p, p + n, cmp_point());
        
        std::swap( *pm,  p[ 0 ]  ) ;
    }
    
    point pa = p[ 0 ];
    
    for(int i = 0; i < n ;++i)
        p[ i ] = p[ i ] - pa;
    
    
    // III. find second point: most right point than pa.
    for(int i = 2; i < n; ++i)
    {
        if ( ( p[ i ] ^ p[ 1 ] ) >= 0 )
            std::swap( p[ i ], p[ 1 ] );
    }
    
    point pb = p[ 1 ] ;
    
    
    for(int i = 0; i < n - 2; ++i)
    {
        angles[i].i = 2 + i;
        
        vector v = p[ i + 2 ];
        vector u = p[ i + 2 ] - pb;
        
        angles[i].cos_ = ( v * u ) / dist( u ) / dist( v );
    }
    
    std::nth_element(angles, angles + ( n - 2 ) / 2, angles + (n-2), cmp_angle() );
   
    
    point pc = p[ angles[( n - 2 ) / 2 ].i ] ;
    
    {
        point ra = pa;
        point rb = pb + pa;
        point rc = pc + pa;
        
        printf("%d %d\n", ra.x, ra.y ) ;
        printf("%d %d\n", rb.x, rb.y ) ;
        printf("%d %d\n", rc.x, rc.y ) ;
    }
}
