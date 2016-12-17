
//acm.timus.ru 1084. Goat in the Garden

#include <stdio.h>
#include <string.h>
#include <math.h>
 
const double pi = 3.1415926535897932384626433832795;

int main(int argc, char **argv)
{
#ifndef ONLINE_JUDGE
 	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif

    int a,r;
    scanf("%d%d",&a,&r);
    
    if (r + r <= a ) // circle
    {
		
		double area = pi * r * r;
		printf("%.3f\n", area);
		return 0;
	}
	
	// r >= d/2   d = a*sqrt(2)
	// r*r >= d^2 / 4 = a^2 * 2 / 4 = a^2 / 2
	if (r * r * 2 >= a * a )
	{
		//square
		printf("%d.000\n", a * a);
		return 0;
	}
	
	{
		double h = sqrt(r * r - a * a / 4.0 );
		double area_triangle = h * a / 4.0 ;
		double area_circle = pi * r * r;
		double area_cord =  acos(a/2.0/(double)r) * r * r / 2.0;
		
		double area = area_circle - 8*(area_cord - area_triangle);
		printf("%.3f\n", area); 
	}
	
	
 	return 0;
}
