

// 	ACM.TIMUS.RU 1001 Reverse Root AC 0.001s !!!!!!!!.
#include <cstdio>
#include <cmath> 
#include <cstring>

static const unsigned long long sqrt_table[] = 
{
  0xa30303030302e30, 0xa30303030302e31, 0xa30323431342e31, 0xa30313233372e31, 0xa30303030302e32, 0xa30313633322e32, 0xa30353934342e32, 0xa30383534362e32, 0xa30343832382e32, 0xa30303030302e33, 0xa30333236312e33, 0xa30363631332e33, 0xa30313436342e33, 0xa30363530362e33, 0xa30373134372e33, 0xa30303337382e33, 0xa30303030302e34, 0xa30313332312e34, 0xa30363234322e34, 0xa30393835332e34, 0xa30313237342e34, 0xa30363238352e34, 0xa30343039362e34, 0xa30383539372e34, 0xa30303939382e34, 0xa30303030302e35, 0xa30303939302e35, 0xa30323639312e35, 0xa30353139322e35, 0xa30323538332e35, 0xa30323737342e35, 0xa30383736352e35, 0xa30393635362e35, 0xa30363434372e35, 0xa30303133382e35, 0xa30313631392e35, 0xa30303030302e36, 0xa30383238302e36, 0xa30343436312e36, 0xa30303534322e36, 0xa30363432332e36, 0xa30313330342e36, 0xa30373038342e36, 0xa30343735352e36, 0xa30323333362e36, 0xa30323830372e36, 0xa30333238372e36, 0xa30373535382e36, 0xa30323832392e36, 0xa30303030302e37, 0xa30313137302e37, 0xa30343134312e37, 0xa30313131322e37, 0xa30313038322e37, 0xa30353834332e37, 0xa30323631342e37, 0xa30333338342e37, 0xa30383934352e37, 0xa30383531362e37, 0xa30313138362e37, 0xa30303634372e37, 0xa30323031382e37, 0xa30303437382e37, 0xa30333733392e37, 0xa30303030302e38, 0xa30333236302e38, 0xa30303432312e38, 0xa30343538312e38, 0xa30323634322e38, 0xa30363630332e38, 0xa30363636332e38, 0xa30313632342e38, 0xa30333538342e38, 0xa30303434352e38, 0xa30333230362e38, 0xa30333036362e38, 0xa30383731372e38, 0xa30303537372e38, 0xa30383133382e38, 0xa30323838382e38, 0xa30333434392e38, 0xa30303030302e39, 0xa30343535302e39, 0xa30343031312e39, 0xa30323536312e39, 0xa30353931322e39, 0xa30363337322e39, 0xa30343732332e39, 0xa30383038332e39, 0xa30303433342e39, 0xa30383638342e39, 0xa30343933352e39, 0xa30373139352e39, 0xa30373334362e39, 0xa30343539362e39, 0xa30383634372e39, 0xa30303839372e39, 0xa30393834382e39, 0xa30353939382e39, 0xa30393934392e39
};

char out[(1<<20) ] __attribute__ ((aligned(8)));
char in [(1<<19) ] __attribute__((aligned(8)));

unsigned long long * w;

//write double inverse order
void writeDouble(double d)
{
	char * s = ( char* )( w );
	unsigned u,v;
	
	d +=  0.5E-4;
	
	u = d;
	d -= u;
	v = ( d ) * 10000;

	*--s = '\n';
	*--s = '0' + v%10, v/=10;
	*--s = '0' + v%10, v/=10;
	*--s = '0' + v%10, v/=10;
	*--s = '0' + v;
	*--s = '.';
	if (u < 100)
    {
	  *--s  = u%10 + '0';
	  *--s  = u/10 + '0';
	  --w;
    }
    else
    {
		*--s  = u%10 + '0'; u/=10;
		*--s  = u%10 + '0'; u/=10;
		*--s  = u%10 + '0'; u/=10;
		*--s  = u%10 + '0'; u/=10;
		*--s  = u%10 + '0'; u/=10;
		*--s  = u%10 + '0'; u/=10;
		*--s  = u%10 + '0'; u/=10;
		*--s  = u%10 + '0'; u/=10;
		*--s  = u%10 + '0'; u/=10;
		*--s  = u%10 + '0'; u/=10;
		
		--w;
		--w;
	}
	  
}


int solve()
{ 
   unsigned long long u = 0;
   unsigned tu = 0;
   
   w = (unsigned long long*)( out + sizeof(out) );
   const char* o;
   tu = fread(in, 1, sizeof(in)-2, stdin);
   in[tu] = '\0';
   o = in;
   while(*o)
   {
	   while(o[0] >='0' && o[1] < '0')
	   {
		   *--w = sqrt_table[*o++ -'0'];
		   ++o;
	   }
	   
	   while(*o && *o <= 32)++o;
	   
	   if (!o[0])break;
	   
	   u = 0;
	   
	   while(*o >='0')
	      u = ( u  << 3) + ( u << 1 ) + *o ++ - '0';
	   
	   if (u < 100)
		*--w = sqrt_table[ u];
	   else
		 writeDouble(sqrt( u + .0));
	    
   }
   
   
   fwrite(w, 1, out + sizeof(out) - (char*)w, stdout);
   
   return 0;
}

#ifndef ONLINE_JUDGE
#include <cstdlib>
#include <time.h>

#include <chrono>

struct auto_timer
{
	typedef std::chrono::high_resolution_clock::time_point rep;
	rep s,e;
	auto_timer()
	{
		s = std::chrono::high_resolution_clock::now();
		
	}
	~auto_timer()
	{
		e = std::chrono::high_resolution_clock::now();
		long int n = std::chrono::duration_cast< std::chrono::microseconds > ( e - s).count();
		printf("elapsed microseconds: %ld\n",n);
	}
};

#else

struct auto_timer{};
#endif

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","rb", stdin);
    freopen("output.txt","wb",stdout);
#endif
	
	
	{
		auto_timer tm;
		solve();
		//fflush(stdout);	
	}
   

    return 0;
}  
