


#include <cstdio>
#include <cmath>



int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 

    const double pi = 3.1415926535;
    double a,v,k;
    int ai,vi;
    scanf("%d%d%lf",&vi,&ai,&k);
    a = ai * pi / 180.0;
    v = vi;
    
    //k = sqrt( k );
    
    // E = v^2*m/2
    // E2 = v2 ^2
    
    // x = vx * t
    // vx = cos(a)*v
    // vy = sin(a)*v
    
    // vy(t)  = vy - 10*t
    // vy(t) = 0 -->  t = vy/10
    
    // x = vx * t = v*cos(a) * vy/10 * 2 = v^2 * cos(a) * sin(a)/5
    
    // x[2] = v^2 / k * cos(a) * sin(a)/5
    // ...........................
    
    // x[i] = v^2/k^i * cos(a) * sin(a) / 5
    
    // sum(x[i], i=0...infinity) = v^2 * cos(a) * sin(a)/5* ( 1/k^0 + 1/k + 1/k^2 + ... 1/k^i + ..) = 
    // = k/(k-1) * v^2 * cos(a) * sin(a)/5 = k/(k-1)v^2 * sin(2a)/10
    
    double ans = k / (k-1) * v * v* sin(a+a) / 10.0;
    
    printf("%.2f\n",ans);
    return 0;
}
