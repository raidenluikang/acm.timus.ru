
#include <stdio.h>
#include <math.h>
#include <algorithm>

static const double EPS = 1.0E-9;

static const double INFINIT= 1.0E+38 ;

static const int N = 100;

int u[N], v[N], w[N];
int n;

double au[N], av[N], aw[N];
double aamic[201],bbmic[201];
double a[201],b[201],c[201],aamare[201],bbmare[201];

char in[65536];
char const* o;
char *wo;
int readInt()
{
	int u = 0;
	while(*o && *o <= 32)++o;
	while(*o >= 48) u = (u<<3) + (u<<1) + (*o++ - 48);
	return u;
}
void writeYes()
{
	*wo++ = 'Y';
	*wo++ = 'e';
	*wo++ = 's';
	*wo++ = '\n';
}
void writeNo()
{
	*wo++ = 'N';
	*wo++ = 'o';
	*wo++ = '\n';
}

void readData()
{
	o = in;
	wo = in;
	in[fread(in,1,sizeof(in)-4,stdin)] = 0;
	n = readInt();
	//scanf("%d",&n);
	for(int i= 0; i != n; ++i) u[i] = readInt(), v[i] = readInt(), w[i] = readInt() ; //scanf("%d%d%d",u+i,v+i,w+i);
	
	for(int i = 0; i != n; ++i)
	{
		au[i] = 100000.0 / u[i];
		av[i] = 100000.0 / v[i];
		aw[i] = 100000.0 / w[i];
	}
}

bool canWin(int k)
{
   for(int i= 0; i != n; ++i)
   {
	   if (i == k ) continue;
	   
	   a[i] = av[i] - av[k];
	   b[i] = au[i] - au[k];
	   c[i] = aw[i] - aw[k];
	   
	   if (fabs(a[i]) < EPS &&
	       fabs(b[i]) < EPS &&
	       ( fabs(c[i]) < EPS || ( fabs(c[i]) > EPS && c[i] < 0) )
	      ) 
	       {
			   return false;
		   }
   }	 
  
    double min_y = 0, max_y = INFINIT;
 
    for(int i= 0; i != n; ++i)
    {
		if (!( i != k  && fabs(a[i]) < EPS && fabs(b[i]) > EPS)) continue;
		
		double r = - c[i] / b[i];
		
		if (b[i] > 0) 
		    min_y = std::max(min_y, r);
		else 
		    max_y = std::min(max_y, r);
	}   
    
    
    if (max_y < min_y + EPS) // max_y <= min_y
		return false;
		
    int nmare = 0;
    int nmic = 1; 
    aamic[0] = bbmic[0]=0;
	
	for(int i= 0; i != n; ++i)
	{
		if (!(i != k && fabs(a[i]) >EPS)) continue;
		
		double rx = -b[i]/a[i];
		
		double ry = -c[i]/a[i];
		
		if (a[i] > 0)
		{
			aamic[ nmic ] = rx;
			bbmic[ nmic ] = ry;
			++nmic;
		}
		else
		{
			aamare[ nmare ] = rx;
			bbmare[ nmare ] = ry;
			++nmare;
		}
	}
    
    for(int i= 0; i != nmare; ++i)
    {
		for(int j = 0; j != nmic; ++j)
		{
			double rx = aamare[i] - aamic[j];
			double ry = bbmare[i] - bbmic[j];
			if (fabs(rx) < EPS)
			{
				if ( ry  < EPS ) return false;
			}
			else
			{
				double r = -ry / rx;
				if (rx > 0) 
				   min_y = std::max(min_y, r);
				else 
				   max_y = std::min(max_y, r);
				
				if (max_y < min_y + EPS) return false;
			}
		}
	}
    
  
   
   if (max_y < min_y + EPS)
       return false;
   
   return true;

}

int main()
{

	#ifndef ONLINE_JUDGE
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	readData();
    
   for (int k  = 0; k != n; ++k)
   {
	  bool ok = canWin( k );
      if ( ok )
       writeYes();//printf( "Yes\n" );
     else
       writeNo();//printf( "No\n" );
   }
   
   if (wo != in)fwrite(in, 1, wo - in, stdout);

   return 0;
}
