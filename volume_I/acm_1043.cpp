

// 1075. Thread in a Space
// A , B, and C , R 
// find shortest path from A to B, no intersect with sphera with center C, radius R.
#include <cstdio>
#include <cmath>

static const double EPS = 1.0E-10;
static const double pi = acos(-1.0);

char in[1024];
char const* o;

int x1, y_1, x2, y2, x3, y3;
double maxx, minx, maxy, miny ;
double x, y, r, alpha, beta, gam_ma;
bool b;

void init_in()
{
    o = in;
    in[fread(in,1,sizeof(in)-4, stdin)] = 0;
}
int readInt()
{
    unsigned u = 0, s= 0;
    while(*o && *o <= 32)++o;
    if (*o == '-') s = ~0, ++o; else if (*o == '+')++o;
    while(*o >= 48 && *o <= 57) u = (u << 3) + (u << 1) + (*o++ - 48);
    return static_cast<int>((u ^ s) + !!s);
}


double max_(double a, double b){ return a > b ? a : b; }
double min_(double a, double b){ return a < b ? a : b; }

int upint(double a)
{
 
    return std::ceil(a - 1.0E-10);
}
int downint(double a)
{
 
    return std::floor(a + 1.0E-10);
}
 

int main()
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    init_in();
     
    x1 = readInt();
    y_1 = readInt();
    
    x2 = readInt();
    y2 = readInt();
    
    x3 = readInt();
    y3 = readInt();
    
    minx = min_(x1, x2);
    maxx = max_(x1, x2);
    
    miny = min_(y_1, y2);
    maxy = max_(y_1, y2);
    
    double cx = (x1 + x2)/2.0;
    double cy = (y_1 + y2)/2.0;
    double a = y2 - y_1;
    double b = x1 - x2;
    double c = x2 * y_1 - x1 * y2;
    double a0,b0,c0;
    if (fabs(a) > EPS)
    {
        a0 = b/a;
        b0 = -1.0;
        c0 = cy - a0 * cx;
    }
    else
    {
        a0 = 1.0;
        b0 = 0.0;
        c0 = -cx;
    }
    
    cx = (x1 + x3) / 2.0;
    cy = (y_1 + y3) / 2.0;
    a = y3 - y_1;
    b = x1 - x3;
    c = x3 * y_1 - x1 * y3;
    double a1,b1,c1;
    
    if (fabs(a) > EPS)
    {
        a1 = b / a;
        b1 = -1.0;
        c1 = cy - a1 * cx;
    }
    else
    {
        a1 = 1.0;
        b1 = 0.0;
        c1 = -cx;
    }
    
    cx = (b0 * c1 - b1 * c0) / (a0 * b1 - a1 * b0);
    cy = (a1 * c0 - a0 * c1) / (a0 * b1 - a1 * b0);
    double r = sqrt((x1 - cx) * (x1 - cx) + (y_1 - cy)*(y_1 - cy));
    a = y2 - y_1 ;
    b = x1 - x2 ;
    c = x2 * y_1 - x1 * y2 ;


    if ( ( a * x3 + b * y3 + c ) * ( a * ( cx - r ) + b * cy + c ) > -EPS ) minx = cx - r ;

    if ( ( a * x3 + b * y3 + c ) * ( a * ( cx + r ) + b * cy + c ) > -EPS ) maxx = cx + r ;
    if ( ( a * x3 + b * y3 + c ) * ( a * cx + b * ( cy - r ) + c ) > -EPS ) miny = cy - r ;

    if ( ( a * x3 + b * y3 + c ) * ( a * cx + b * ( cy + r ) + c ) > -EPS ) maxy = cy + r ;

#ifndef ONLINE_JUDGE
    printf("minx: %.16f\n", minx);
    printf("maxx: %.16f\n", maxx);
    printf("miny: %.16f\n", miny);
    printf("maxy: %.16f\n", maxy);
#endif
    int imin_x = downint   ( minx ) ;
    int imax_x = upint ( maxx ) ;
    int imin_y = downint   ( miny ) ;
    int imax_y = upint ( maxy ) ;


   // if ( imin_x < -1000 ) imin_x = -1000 ;
   // if ( imin_y < -1000 ) imin_y = -1000 ;
   //if ( imax_x >  1000 ) imax_x  = 1000 ;
    //if ( imax_y >  1000 ) imax_y  = 1000 ;

    int answer =   ( ( imax_x - imin_x ) * ( imax_y - imin_y ) ) ; 
    //write answer
    {
        unsigned u = answer;
        
        char *w = in + 1024;
        
        *--w = '\n';
       
        do *--w = u % 10 + '0'; while(u/=10);
        
        fwrite(w, 1, in + 1024 - w, stdout);
    }
    
    return 0;
}
