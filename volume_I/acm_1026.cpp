
//1026. Questions and Answers

#include <cstdio>


  
char buffer[ (1 << 19) + ( 1 << 16 ) ];
char const * o ;
char * w ;
unsigned frequence[5005] = {};

void initRead()
{
	unsigned n;
	n = fread(buffer, 1, sizeof(buffer ) - 2, stdin);
	buffer[n] = '\0';
	o = buffer;
}
void initWriter()
{
	w = buffer;
}
unsigned readInt()
{
	unsigned u = 0;
	while(*o  && *o <= 32)++o;
	while(*o >='0' && *o <= '9') u = (u<<3) + (u<<1) + *o++ -'0';
	return u;
}
void writeInt(unsigned u, char c)
{
	unsigned v = u, vn = 0;
	do vn++; while(v/=10);
	v = vn;
	while(vn-->0)w[vn] = u%10 + '0', u/=10;
	w+=v;
	*w++ = c;
}
void flushBuffer(){
	if (w != buffer){
		fwrite(buffer, 1, w - buffer, stdout);
		w = buffer;
	}
}

unsigned query(unsigned i)
{
    unsigned l = 0, r = 5001;
    // [l,r)
    while( l < r - 1)
    {
		unsigned m = ( l + r ) >> 1;
		if (frequence[ m ] < i )
		   l = m + 1; //  frequence[m] < i --> i-th number great than m 
		else // frequence[m] >= i --> so need search in [l,m]  interval, or [l,m+1)
		  r = m ;
	}
	
	while(frequence[l] < i)
	   ++l;
	return l;	
}

int solve()
{
	unsigned n, q;
	initRead();
	n = readInt();
	for(unsigned i = 0; i != n; ++i)
	{
		unsigned u = readInt();
		frequence[u]++;
	}
	for(unsigned i = 1; i != 5001; ++i)
	{
		frequence[i] += frequence[i-1];
	}
	// skip '###'
	while(*o && ( *o <= 32 || *o == '#')) ++o;
	
	q = readInt();
	initWriter();
	for(unsigned i = 0; i != q; ++i)
	{
		unsigned u = readInt();
		unsigned v = query(u);
		writeInt(v,'\n');
	}
	
	flushBuffer();
	return 0;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif

    solve();
    
    return 0;
}  
