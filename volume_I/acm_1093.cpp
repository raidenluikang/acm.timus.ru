
#include <cstdio>
#include <cmath>

static const double g2        = 5.0;
static const double oo       = 1.0E+16;
static const double EPS      = 1.0E-9;
static const double TEN[ 8 ] = { 1.0, 0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001, 0.0000001 };

static inline bool zero(double n){
  return fabs(n) <= EPS;
}

struct scanner
{
    char buffer[512];
    char const* o ;
    void load()
    {
        o = buffer;
        buffer[fread(buffer, 1, sizeof(buffer) - 4, stdin)] = 0;
    }
    
    double readDouble()
    {
        unsigned u = 0, s = 0, t = 0;
        while(*o && *o <= 32)++o;// skip whitespaces
        
        if (*o == '-') s = ~0, ++o; else if (*o == '+')++o;
        while(*o >= 48 && *o <= 57) u = (u << 3) + (u << 1 ) + (*o ++ - 48);
        if (*o == '.')
        {
            ++o;
            while(*o >= 48 && *o <= 57)u = (u << 3) + (u << 1) + (*o ++ - 48),
             ++t;
        }
        
        return ((int)( ( u ^ s ) + !!s ) ) * TEN[ t ];
    }
};
struct point
{
  double x;
  double y;
  double z;
  point(): x(), y(),z(){}
  point (double x, double y, double z):x(x),y(y),z(z){}
};

point c, n, s,v;
double r;

static bool check(double t)
{
  if (t < 0)  return false;
  point m(s.x + v.x * t, s.y + v.y * t, s.z + v.z * t - g2 * t * t   );
  point d(m.x - c.x, m.y - c.y, m.z - c.z);
  double d_len = d.x * d.x + d.y * d.y + d.z * d.z;
  
  return d_len < r * r ;
}

// d.x = s.x - c.x + v.x * t
// d.y = s.y - c.y + v.y * t
// d.z = s.z - c.z + v.z * t - g * t * t / 2.0
// d_len = d.x * d.x + d.y * d.y + d.z * d.z  = 
// = (s.x - c.x)^2 + 2*v.x * (s.x - c.x)*t + v.x ^ 2 * t^2 +
// + (s.y - c.y)^2 + 2*v.y * (s.y - c.y)*t + v.y ^ 2 * t^2 + 

int main()
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    scanner sc;
    sc.load();
    c.x = sc.readDouble();
    c.y = sc.readDouble();
    c.z = sc.readDouble();
    
    n.x = sc.readDouble();
    n.y = sc.readDouble();
    n.z = sc.readDouble();
    
    r = sc.readDouble();
    
    s.x = sc.readDouble();
    s.y = sc.readDouble();
    s.z = sc.readDouble();
    
    v.x = sc.readDouble();
    v.y = sc.readDouble();
    v.z = sc.readDouble();
    
    // any coordinates by module less than 500 , at most 4 decimal digit after point.
    // integer conversation double 500 * 10^4 = 5 * 10^6
    
    bool have_answer=false;
    double a = - (g2 * n.z )  , // 10*5*10^6/2 = 25 * 10^6
           b = (v.x * n.x + v.y * n.y + v.z * n.z), // 5 * 10^6 * 5*10^6 * 3 = 75 * 10^12
           c = (s.x * n.x + s.y * n.y + s.z * n.z - ::c.x * n.x - ::c.y * n.y - ::c.z * n.z );
     
    if ( !zero( a ) )
    {
       double delta = b * b - 4.0 * a * c;
       if ( delta > -EPS )
       {
          if (delta < EPS) delta = 0;
          double d_s = sqrt( delta );
          double a_2 = 0.5 / a;
          
          double t1 = ( -b + d_s ) * a_2,
                 t2 = ( -b - d_s ) * a_2;
          
          if (t1 >= 0 )
            if ( check(  t1 ) )
               have_answer = true;
          
          if ( t2 >= 0 )
            if ( check(  t2 ) )
               have_answer = true;
       }
    }
    else
    {
        if ( !zero( b ) )
           if (check( -c / b ) )
              have_answer = true;
    }
    
    {
        char out[2][64] = {"MISSED\n", "HIT\n" };
        int  len[2] = {7, 4};
        fwrite(out[have_answer], 1, len[have_answer], stdout);
    }
    return 0;
}
