//1185. Wall


#include <cstdio>
#include <cmath>
#include <algorithm>

struct point
{
    int x;
    int y;
};
bool operator <  (point a, point b)
{
    return (a.y < b.y) || (a.y == b.y && a.x < b.x);
}

// returns -1 if a -> b -> c forms a counter-clockwise turn,
// +1 for a clockwise turn, 0 if they are collinear
int ccw(point a, point b, point c)
{
    point u = {b.x - a.x, b.y - a.y};
    point v = {c.x - a.x, c.y - a.y};
    int area = u.x * v.y - u.y * v.x;
    
    return - area;
}

int dist2(point a, point b)
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}

struct polar_order
{
    point pivot;
    explicit polar_order(point p): pivot(p){}
    bool operator()(point a, point b)const
    {
        int order = ccw(pivot, a, b);
        if (order == 0)
            return dist2(pivot, a) < dist2(pivot, b);
        return order < 0;
    }
};

int n, L;
char const* o;
char  in[65536];
point pivot;
point p[1024];
point hull[1024];

int readInt()
{
    unsigned u = 0, s = 0;
    while(*o && *o <= 32)++o;
    if (*o == '-')s = ~0, ++o; else if (*o=='+')++o;
    while(*o>='0' && *o<='9') u = (u << 3) + (u << 1) +(*o++ - '0');
    return (u ^ s) + !!s;
}

int solve()
{
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    n = readInt();
    L = readInt();
    for(int i = 0; i< n;++i)
    {    p[i].x = readInt();
                
        p[i].y = readInt();
    }
    
    // find the point having the least y coordinate (pivot),
    // ties are broken in favor of lower x coordinate
    int leastY = std::min_element(p, p + n) - p;
    
    // swap the pivot with the first point
    std::swap(p[0], p[leastY]);

    // sort the remaining point according to polar order about the pivot
    pivot = p[0];
    std::sort(p + 1, p + n, polar_order(pivot) ); 

    int h = 0;
    hull[h++] = p[0];
    hull[h++] = p[1];
    hull[h++] = p[2];
    
    for (int i = 3; i < n; i++) 
    {
        point top = hull[--h];
        
        while ( ccw( hull[h-1], top, p[ i ] ) >= 0)   {
            top = hull[--h];
        }
        hull[h++] = top;
        hull[h++] = p[i];
    }
    
    double pi = 3.141592653589793238462643383279502884;
    //M_PI
    
    double len = 0;
    hull[h] = hull[0];
    for(int i = 0; i < h; ++i)
    {
        len += sqrt( dist2(hull[i], hull[i+1]) + .0);
    }
    
    len += 2*pi*L;
    
    int len_i = (len + 0.5);
    printf("%d\n", len_i);
    
    return 0;
}




int main(int argc, char * argv[]) 
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
   
    solve();
    
    return 0;
}
