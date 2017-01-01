

// 1066. Garland

#include <cstdio>
#include <cmath>


// h[1]  =  a
// h[i] = (h[i-1] + h[i+1])/2 - 1, where 1 < i < n 
// h[n] = b
// h[i] >= 0 , 1 <= i <= n

// given n and a, find smallest possible value of b.

// solution:
// h[1] = a  
// h[2] = x
// and h[i+1] = 2 + 2h[i] - h[i-1]                (1)
// let h[i] = v[i] * x + u[i] * a + w[i]          (2)
// v[1] = 0,  u[1] = 1, w[1] = 0
// v[2] = 1,  u[1] = 0, w[2] = 0

// set (2) to (1) :
// v[i+1] * x + u[i+1] * a + w[i+1] = 2 + 2*(v[i] *x + u[i]*a + w[i]) - (v[i-1]*x + u[i-1]*a + w[i-1)
// so 
// v[i+1] = 2*v[i] - v[i-1]   (3a)
// u[i+1] = 2*u[i] - u[i-1]   (3b)
// w[i+1] = 2 + 2*w[i] - w[i-1] (3c)

// solve (3a)
// v[1] = 0, v[2] = 1, v[3] = 2*v[2] - v[1] = 2 *1 - 0 = 2, v[4] = 2*v[3] - v[2] = 2*2 - 1 = 4 - 1 = 3
// and we got:
// v[i] = i - 1 

// solve (3b)
// u[1] = 1
// u[2] = 0
// u[3] = 2*u[2] - u[1] = 2*0 - 1 = -1
// u[4] = 2*u[3] - u[2] = 2(-1) - 0 = -2
// u[5] = 2*u[4] - u[3] = 2(-2) - (-1) = -4 + 1 = -3
// u[6] = 2*u[5] - u[4] = 2(-3) - (-2) = -6 + 2 = -4
// and we got intuitive
// u[i] = 2 - i

// solve(3c)
// w[1] = 0
// w[2] = 0
// w[3] = 2 + 2w[2] - w[1] = 2
// w[4] = 2 + 2w[3] - w[2] = 2 + 2*2 = 6
// w[5] = 2 + 2w[4] - w[3] = 2 + 2*6 - 2 = 12
// w[6] = 2 + 2w[5] - w[4] = 2 + 2*12 - 6 = 20
// and we got intuitive
// w[i] = (i-2)*(i-1) 
// 
// h[i] = v[i]*x + u[i]*a + w[i] >= 0
// h[i] = (i-1)*x + (2-i)*a + (i-2)*(i-1) >= 0
// or  (i-1)*x >= a *(i-2) - (i-2)*(i-1)
//  x >= a (i-2)/(i-1) - (i-2) = a (1 - 1/(i-1)) - (i-2), where i > 2
//  f(i) = a - a/(i-1) - (i-2)  , so x =  max( f( i ), i = 2..n )
// and h[n] = b = (i-1)*x - (i-2)*a + (i-1)*(i-2) - is result

// analyze function f(i) = a - a/(i-1) - i + 2,   i > 1
// f(2) = a - a/1 - 2 + 2 = a - a  = 0
// f(3) = a - a/2 - (3-2) = a - a/2 - 1
// 
// dif(f(i), by i) = a - a/(i-1)^2 - 1 = 0 ==>  a ( 1- 1/(i-1)^2) = 1
// 1 - 1/(i-1)^2 = 1/a
// 1/(i-1)^2 = 1 - 1/a,  if a = 1 --> 1/(i-1)^2 = 0   
// (i-1)^2 = 1/(1 - 1/a) = a/(a-1)
// i - 1  = sqrt(a/(a-1)) ==> i = 1 + sqrt(a/(a-1))

 
int main()
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
   
    int n;
    
    double a, xmax = 0;
    double u1, v1, u2, v2, ui, vi;
    scanf("%d%lf",&n,&a);
    
    // h = u1 * x + v1
    u1 = 0; 
    v1 = a;
    
    u2 = 1;
    v2 = 0;
    
    for(int i= 3; i <= n; ++i)
    {
        ui = 2*u2 - u1;
        vi = 2 + 2*v2 - v1;
        
        // h[i] = ui * x + vi >= 0 --> x >= -vi/ui
        a = -vi/ui;
        xmax = (a > xmax ? a : xmax);
        u1 = u2; u2 = ui;
        v1 = v2; v2 = vi;
    }
    
    double b = xmax * ui + vi;
    
    printf("%.2f\n",b);
    
    
    return 0;
}

