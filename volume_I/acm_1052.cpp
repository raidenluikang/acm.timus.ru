

#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>

char buff[8192];
const char* o;
void load()
{
	 unsigned n;
	o = buff;
	 n = fread(buff, 1, sizeof(buff) - 1, stdin);
	 //200   -2000 2000
	 buff[n] = '\0';
}
unsigned readuint()
{
	unsigned u = 0;
	while(*o && *o<=32)++o;
	while(*o >='0' && *o <='9')
	 u = u * 10 + *o ++  -'0';
	 return u;
}
int readint()
{
	unsigned u    = 0;
	unsigned mask  = 0, a = 0;//0xFFFFFFFF, a = 0; // -u = ~u + 1   ~u == u ^ 0xFFFFFFF
	// u ^ mask + a
	while(*o && *o<=32)++o;
	//if (*o == '-' || *o == '+')
	{
		if (*o == '-' )
		  mask = 0xFFFFFFFF, a = 1, ++o;
		else if (*o == '+') 
		  ++o;
		
	}
	while(*o>='0' && *o <='9')u = u * 10 + *o++ -'0';
	
	return (int)(( u ^ mask ) + a); 
}

struct point
{
	int x;
	int y;
	point(): x(0),y(0){};
	point(int x_, int y_): x(x_), y(y_){};
}; 

bool operator == (point const& lhs, point const& rhs){ return lhs.x == rhs.x && lhs.y == rhs.y;}
bool operator < (point const& lhs, point const& rhs){ return lhs.x < rhs.x || (lhs.x==rhs.x && lhs.y < rhs.y);}
int gcd(int x, int y){return y == 0 ? x : gcd(y, x % y); }

int maxPointOnSameLine(const point p[], int n)
{
	if (n < 2)
	  return n;
	int maxPoints = 0;
	int curMax, overlapPoints, verticalPoints;
	std::map< point, int > slope;
	for(int i= 0; i != n; ++i)
	{
		curMax = overlapPoints = verticalPoints = 0;
		for(int j = i + 1; j != n; ++j)
		{
			if (p[i] == p[j])
			  ++overlapPoints;
			else if (p[i].x == p[j].x)
			   ++verticalPoints;
		    else
		    {
				int xd = p[j].x  - p[i].x;
				int yd = p[j].y  - p[i].y;
				int g  = gcd(xd,yd);
				
				xd /= g;
				yd /= g;
				
				int& e =  (slope[point(xd,yd)]);
				++e;
				curMax = std::max(curMax, e);
			}
			
			curMax = std::max(curMax, verticalPoints);
		}
		
		maxPoints = std::max(maxPoints , curMax + overlapPoints + 1);
		
		slope.clear();
	}
	
	return maxPoints;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif
    int n;
    point p[200];
    load();
    n = readuint();
    for(int i = 0; i != n; ++i){
       p[i].x = readint();
       p[i].y = readint();
   }
     int rm = maxPointOnSameLine(p, n);
     
	 printf("%d\n",rm);
	return 0;   
}  
