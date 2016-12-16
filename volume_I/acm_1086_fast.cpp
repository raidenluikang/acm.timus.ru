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
char buffer[1<<20];
char const* o;
char * w;
unsigned char mem[ 170000 ] = {};
unsigned  primes[ 15000 ] = {};

unsigned readInt();
void writeInt(unsigned u, char c);
void flushBuffer();

void solve()
{
	int np = 0;
	mem[0] = mem[1] = true;
	for(int i = 2; i < 512; ++i)
	{
		if ( ! mem[i])
		  for(int j = i * i; j < 170000; j += i)
		    mem[j] = true;
	}
	
	for(int i = 0; np  != 15000; ++i)
	{
		if (!mem[i])
		primes[ np++  ] = i;
	}
	
	int n =  readInt() ;
	
	for(int i = 0; i < n; ++i)
	{
		int pos = readInt();
		writeInt(primes[pos-1],'\n');
		//read(pos);
		//writeln(primes[pos]);
	}
	flushBuffer();
}

int main(int argc, char **argv)
{
#ifndef ONLINE_JUDGE
	auto_cpu_timer tm;
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
   
#endif
	 
	{
		unsigned n;
		w = buffer + 65536;
		n = fread(w, 1, sizeof(buffer) - 65538, stdin);
		w[n] = '\0';
		o = w;
		w = buffer;
	} 
	 
	solve();
	
#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
#endif
	return 0;
}


unsigned readInt()
{
	unsigned u = 0;
	while(*o && *o <= 32)++o;
	while(*o>=48)u = (u<<3) + (u<<1) + *o++ -'0';
	return u;
}
void writeInt(unsigned u, char c)
{
	unsigned v = u, n = 0;
	do ++n; while(v/=10);
	v = n;
	while(v-->0)w[v] = u%10 + '0', u/=10;
	w+=n;
	*w++ = c;
}
void flushBuffer()
{
	if (w != buffer)
	{
		fwrite(buffer, 1, w - buffer, stdout);
	}
}
