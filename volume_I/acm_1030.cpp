// acm.timus.ru 1030. Titanic.

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib> // atof 
static const double Diameter = 6875.0;
static const double Radius   = 3437.5;
static const double C_PI     = 3.14159265358979323846;


double strToDouble( char s[], int p)
{
    char t = s[ p ] ;

    double result ;

    s[p] = '\0';

    result  = ::std::atof(s);

    s[p] = t;

    return result;
}

char in[65536];

char s[1024];
const char* o;

double phi1, phi2, teta1, teta2 ;
double degrees, minutes, seconds, sign;
double x_1, x_2, y_1, y_2, z_1, z_2;
double dist, k, way;

void init_in()
{
    unsigned n;
    n = fread(in, 1, sizeof(in) - 4, stdin);
    in[n] = '\0';
    o = in;
}

int readLine(char s[])
{
    int n = 0;
    while(*o && *o != '\n')
    {
        s[n++] = *o++;
    }
    if (*o == '\n')
      ++o;
    s[n] = '\0';
    return n;
}

int solve()
{
     init_in();
     // first 3 lines do not used.
     readLine(s);

     readLine(s); 

     readLine(s);
    
     // main 
     readLine(s);
     char* p = strchr(s, '^');
     char* p2 = strchr(p, '\'' );
     char* p3 = strchr(p2, '\"');

     degrees  = strToDouble(s, p - s);
     ++p; // skip '^'
     minutes  = strToDouble(p, p2 - p);
     ++p2; // skip '\''
     seconds  = strToDouble(p2, p3 - p2) ;
     ++p3; // skip '\"' 

     sign = 0.0;
     while(*p3 && *p3 <= 32)++p3;
     if (*p3 == 'S') sign = -1.0;
     else if (*p3 == 'N') sign = 1.0;

     phi1 = sign * (degrees + minutes/60.0 + seconds/3600.0);

     readLine(s);
     
     char * t = strchr(s, ' ');
     ++t;
     p = strchr(t, '^');
     p2 = strchr(p, '\'');
     p3 = strchr(p2, '\"');
     degrees = strToDouble(t, p - t);
     ++p;// skip ^ 
     minutes  = strToDouble(p, p2 - p);
     ++p2; // skip '\''
     seconds =  strToDouble(p2, p3 - p2);
     ++p3; // skip '\"'
     sign =0.0;
     while(*p3 && *p3 <= 32)++p3;
     if (*p3 == 'W') sign = -1.0;
     else if (*p3 == 'E') sign = 1.0;
    
     teta1 = sign*(degrees + minutes/60.0 + seconds/3600.0);

     readLine( s );

     readLine( s );

     p = strchr(s, '^');
     p2 = strchr(p, '\'');
     p3 = strchr(p2, '\"');
     degrees  = strToDouble(s, p - s);
     ++p;
     minutes  = strToDouble(p, p2 - p); 
     ++p2;
     seconds  = strToDouble(p2, p3 - p2);
     ++p3;
     sign  = 0.0;
     while(*p3 && *p3 <= 32) 
        ++p3 ;
     if (*p3 == 'S') sign = -1.0;
     else if (*p3 == 'N') sign = 1.0;

     phi2  = sign*(degrees + minutes/60.0 + seconds/3600.0);

     readLine(s);
     t = strchr(s, ' ');
     ++t;
     p = strchr(t, '^');
     p2 = strchr(p, '\'');
     p3 = strchr(p2, '\"');

     degrees  = strToDouble(t, p - t);
     ++p;
     minutes  = strToDouble(p, p2 - p);
     ++p2;
     seconds  = strToDouble(p2,p3 - p2);
     ++p3;
     sign  =0.0;
     while(*p3 && *p3 <= 32)++p3;
     if (*p3 == 'W') sign = -1.0;
     else if (*p3 == 'E') sign = 1.0;
     teta2  = sign*(degrees + minutes/60.0 + seconds/3600.0);

        phi1  = phi1  * C_PI / 180.0;
        phi2  = phi2  * C_PI / 180.0;
        teta1 = teta1 * C_PI / 180.0;
        teta2 = teta2 * C_PI / 180.0;

        x_1  = Radius*cos(phi1)*cos(teta1);
        y_1  = Radius*cos(phi1)*sin(teta1);
        z_1  = Radius*sin(phi1);

        x_2  = Radius*cos(phi2)*cos(teta2);
        y_2  = Radius*cos(phi2)*sin(teta2);
        z_2  = Radius*sin(phi2);
        dist = sqrt((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2)+(z_1-z_2)*(z_1-z_2));
        k = dist / Diameter;
        if (k > 1.0) k  = 1.0;
        else if ( k < -1.0) k  = -1.0;
        way = Diameter * asin(k);
        
        printf ("The distance to the iceberg: %.2f miles.\n", way);
        if (way < 99.995)
        {
            printf("DANGER!\n");
        }

        return 0;
} // end solve

int main(int argc, char* argv[])
{

#ifndef ONLINE_JUDGE
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
#endif

    solve();
    return 0;
}
