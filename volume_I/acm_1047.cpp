

#include <cstdio>
#include <cstring>

char buffer[65536];
char const* o;
int readInt()
{
	int n = 0;
	while(*o && *o <= 32)++o;
	
	while(*o >='0' && *o <='9') n = n * 10 + *o++ -'0';
	return n;
}
int readFloatInt()
{
	 int n = 0, sign = 1;
	 while( *o && *o <= 32) ++o;
	 if(*o == '-' || *o == '+')
	 {
		 sign = (*o=='-') ? -1 : +1;
		 ++o;
		while( *o && *o <= 32) ++o;
	 }

	 while(*o >='0' && *o <='9')
	 {
		 n = n * 10 + *o ++ -'0';
	 }
	 if (*o == '.')
	 {
		 ++o;//skip '.'
		 n = n * 10 + (*o++)  - '0';
		 n = n * 10 + (*o++)  - '0';
		 //while(*o>='0')
	 }
	 else
	 {
		 n = n * 10 + 0;
		 n = n * 10 + 0;
	 }
	 return n*sign;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif
 
    //int a[4096] = {};
    int a_0, a_n_1;
   
    int n = 0;
    n = fread(buffer, 1, sizeof(buffer) - 4, stdin);
    buffer[n] = '\0';
    o = buffer;
    
    n = readInt();
    a_0 = readFloatInt();
    a_n_1 = readFloatInt();
    
    //for(int i= 1; i <= n; ++i)
      
      //scanf("%lf", c + i);
    
    // a[i] = (a[i-1] + a[i+1])/2 - c[i]
    // a[i]*2 = a[i-1] + a[i+1] - 2*c[i]
    
    // a[1] * 2 = a[0] + a[2] - 2c[1]
    // a[2] * 2 = a[1] + a[3] - 2c[2]
    // a[3] * 2 = a[2] + a[4] - 2c[3]
    // a[4] * 2 = a[3] + a[5] - 2c[4]
    // a[5] * 2 = a[4] + a[6] - 2c[5]
    //...............................
    // a[n] * 2 = a[n-1] + a[n+1] - 2c[n]
    //------------------------------------- 
	// sum(a[i]*2,i=1..n) = sum(a[i-1] + a[i+1],i=1..n) - sum(2c[i],i=1..n)
	// a[1] * 2 + 2*a[n] = a[0] + a[1] + a[n] + a[n+1] - 2*sum(c[i])
	// a[1] + a[n] = a[0] + a[n+1] - 2*sum(c[i])
	
	// a[1] = x
	// a[2] = a[1]*2 - a[0] + 2*c[1] = 2x + (2c[1] - a[0])
    // a[3] = a[2]*2 + 2*c[2] - a[1] = (2x + (2c[1] - a[0])) * 2 + 2*c[2] - x = 3x + 4c[1] + 2c[2] - 2*a[0]
    // a[4] = a[3]*2 + 2*c[3] - a[2] = 6x + 8c[1] + 4c[2] - 4a[0] + 2c[3] - 2x - 2c[1] + a[0] = 
    //      = 4x + 6c[1] + 4c[2] + 2c[3] - 3a[0]
    int y_1 = 0, y_0 = a_0; // a[0] = y_1 * x + y_0
    int x_1 = 1, x_0 = 0;
    // a[1] = x_1 * x + x_0
    // a[i] = x_1(i) * x + x_0(i)
    // a[i+1] = 2*a[i] - a[i-1] + 2*c[i-1]	--> x_1(i+1) = 2*x_1(i) - x_1(i-1) 
    //  and  x_0(i+1) = 2*x_0(i) - x_0(i-1)  + 2*c[i-1]
    for(int i= 2; i <= n + 1; i++)
    {
		int c_i = readFloatInt();
		int z_1 = x_1 + x_1 - y_1;
		int z_0 = x_0 + x_0 - y_0 + c_i + c_i;//c[ i - 1 ] + c[ i - 1 ];
		y_0 = x_0;
		y_1 = x_1;
		
		x_0 = z_0;
		x_1 = z_1;
	}
	
	// a[n+1] = x_1 * x + x_0 --> x = (a[n+1] - x_0)/x_1
	double x = (a_n_1 - x_0)/(double)x_1 / 100.0;
	printf("%.2f\n",x);
	return 0;   
}  
