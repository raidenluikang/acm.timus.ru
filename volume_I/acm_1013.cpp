#include <stdio.h>

#ifndef ONLINE_JUDGE
#include <chrono>
struct auto_cpu_timer{
	typedef std::chrono::high_resolution_clock::time_point point;
	point s,e;
	auto_cpu_timer(){
		s = std::chrono::high_resolution_clock::now();
		
	}
	~auto_cpu_timer(){
		e = std::chrono::high_resolution_clock::now();
		long int n = std::chrono::duration_cast< std::chrono::microseconds>(e-s).count();
		fprintf(stderr, "elapsed: %ld microseconds\n",n);
	}
};
#endif


typedef unsigned long long u64;

u64 mul_mod( u64 a, u64 b, u64 m ) // returns (a*b)%m
{
	if (a == 0 ) return 0;// a= 16*a1 + a0   a * b = 16*a1*b + a0*b
	// a0 = a % 16 = a & 15;
	return ( b * ( a & 7 ) + ( mul_mod( a >> 3, b, m ) << 3 )) % m;   
}

struct matrix
{
	u64 a11, a12, a21, a22;
};


matrix mul_matrix(matrix const& ma, matrix const& mb, u64 m)
{
	matrix mc;
	mc.a11 = (mul_mod(ma.a11, mb.a11,m) + mul_mod(ma.a12, mb.a21,m)) % m;
	mc.a12 = (mul_mod(ma.a11, mb.a12,m) + mul_mod(ma.a12, mb.a22,m)) % m;
	
	mc.a21 = (mul_mod(ma.a21, mb.a11,m) + mul_mod(ma.a22, mb.a21,m)) % m;
	mc.a22 = (mul_mod(ma.a21, mb.a12,m) + mul_mod(ma.a22, mb.a22,m)) % m;
	return mc;
}

inline
u64 readInt()
{
	int c;
	u64 u = 0;
	while((c=getc(stdin)) <= 32) ;
	while(c>=48) u = (u<<3)+(u<<1) + c - 48, c = getc(stdin);
	return u;
}

inline
void writeInt(u64 u)
{
	char buf[64] = {};
	char* w = buf + 63;
	*--w = '\0';
	do *--w = u%10 + '0'; while(u/=10);
	puts(w);
}
int main(int argc, char **argv)
{
#ifndef ONLINE_JUDGE
	auto_cpu_timer tm;
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif
	 
     u64 n,k,m;
     n = readInt();
     k = readInt();
     m = readInt();
     //scanf("%lld%lld%lld",&n,&k,&m);
     
     matrix r = {1,0,0,1};
     matrix a = {0,1,k-1,k-1};
     while(n>0)
     {
		 if (n&1) r = mul_matrix(r, a, m), n--;
		 else a = mul_matrix(a, a, m), n/=2;
	 }
	 
	 // need a.a22
	// printf("%lld\n",r.a22 % m);
     writeInt(r.a22);
	
#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
#endif
	return 0;
}
