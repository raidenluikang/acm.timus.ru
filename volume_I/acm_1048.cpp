
// if compiler is visual studio
#ifdef _MSC_VER
#pragma comment(linker,"/STACK:16777216")
#endif

#include <cstdio>
#include <cstring>

static const unsigned char div10[20] = {0,0,0,0,0,0,0,0,0,0,  1,1,1,1,1,1,1,1,1,1};
static const unsigned char mod10[20] = {0,1,2,3,4,5,6,7,8,9,  0,1,2,3,4,5,6,7,8,9};

char buffer[1<<22] = {};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif
	char* w = buffer;
	char const* o = buffer;
	unsigned int n = 0;
	
	n = fread(buffer, 1, sizeof(buffer)-1, stdin);
	buffer[n] = '\0';
	
	n = 0;
	while(*o && *o <= 32)++o;
	while(*o >='0' && *o <='9') n = n * 10 + (*o++) - '0';
	
	while(*o && !(*o >='0' && *o <='9')) 
	     ++o;
	for(unsigned i = 0, j = 0; i != n; ++i)
	{
		//unsigned char c =  o[ i << 2 ] + o[ ( i << 2 ) | 2 ] - 96;
		w[i] = o[i<<2] + o[(i<<2) | 2] - 48;//mod10[ c ]  + 48;
		if (w[i] > '9')
		{
			w[i] -= 10;
			// j+1 .. i - 1
			w[j]++;
			if(j + 1 <  i)
			  memset(w + j + 1, '0', i - j - 1);
			j = i;
		}
		else if(w[i] < '9')
		{
			j = i;
		}
	}
	
	
	fwrite(w, 1, n, stdout);
}
