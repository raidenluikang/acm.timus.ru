
// acm.timus.ru 1002 Phone number. AC 0.001s on Clang 3.5 C++14 compiler.
 
#include <cstdio>
#include <cstring>

#ifdef _MSC_VER

#define JUDGE_ALIGN64_OFFSET  __declspec(align(64))
#define JUDGE_ALIGN64_SUFFIX     

#else

#define JUDGE_ALIGN64_OFFSET   
#define JUDGE_ALIGN64_SUFFIX  __attribute__((aligned(8)))

#endif 
 
static const char table[26] = 
{
	// 'a'  'b'  'c'  'd'  'e'  'f'  'g' 'h' 'i' 'j' 'k' 'l' 'm' 'n' 'o' 'p' 'q' 'r' 's' 't' 'u' 'v' 'w' 'x' 'y' 'z'
	 2,   2, 2, 3, 3, 3, 4, 4, 1 , 1, 5, 5 , 6 , 6 , 0 , 7 , 0 , 7 , 7 , 8 , 8 , 8 , 9 , 9 , 9 , 0  
};

JUDGE_ALIGN64_OFFSET
char buffer[ 1 << 19] JUDGE_ALIGN64_SUFFIX;
char const*o;
char * w;

JUDGE_ALIGN64_OFFSET 
unsigned  g[ 128 ][ 128 ] JUDGE_ALIGN64_SUFFIX= {} ;

JUDGE_ALIGN64_OFFSET 
unsigned  ps[ 65536 ]    JUDGE_ALIGN64_SUFFIX = {} ;

JUDGE_ALIGN64_OFFSET
unsigned  ls[ 65536 ] JUDGE_ALIGN64_SUFFIX = {};
 
JUDGE_ALIGN64_OFFSET 
char text[ 128 ]    JUDGE_ALIGN64_SUFFIX = {} ;

JUDGE_ALIGN64_OFFSET
char  word[128] JUDGE_ALIGN64_SUFFIX = {};

JUDGE_ALIGN64_OFFSET
bool visit[128] JUDGE_ALIGN64_SUFFIX;

JUDGE_ALIGN64_OFFSET
unsigned que[128] JUDGE_ALIGN64_SUFFIX;

JUDGE_ALIGN64_OFFSET
unsigned widx[128]JUDGE_ALIGN64_SUFFIX;

JUDGE_ALIGN64_OFFSET
unsigned wprev[128]JUDGE_ALIGN64_SUFFIX;

unsigned ntext, tq, hq; 
int solve()
{
	unsigned n;
	//w = buffer;
	w = buffer + 65536;
   //1. read	
	n = fread(w, 1, sizeof(buffer) - 65536,stdin);
	w[n] = '\0';

   //2. remove -1.
	while(n > 0 && w[ n ] != '-') -- n;
	w[ n ] = '\0';
	
	//3. let o and w  start position of buffer.
	o = w;
	w = buffer;
	
	
	while(true)
	{
		//1. read text[100]
		while(*o && *o <= 32)++o;
		if (!o[0])break;
		
		 
		ntext  = 0 ;
		while(*o >='0') 
		   text[ntext++] = *o++  - '0';
		
		 
		//2. read n
		n = 0;
		while(*o <= 32)++o;
		while( *o >= '0' ) 
		  n = ( n << 3 ) + ( n << 1 ) + *o ++  -'0';
		
		memset(g, 0, sizeof(g));
		
		//read n words.
		for(unsigned i = 1; i != n + 1; ++i)
		{
			
			unsigned l  = 0;
			while(*o && *o <= 32)++o;
			ps[ i]  = o - buffer;
		

			while(*o >= 'a')
			  word[l++] = table[  *o++ -'a' ];
			
			//*o++ = '\0';//set terminator symbol.
			
			ls[ i ] = l;
			
			if( l > ntext)continue;
			
			for(unsigned h = 0; h < ntext - l + 1; ++h)
			{
				if(memcmp( word, text + h, l ) == 0)
				{
					g[ h ][ l ] = i ;
				}   
			}
		}
		
		//
		memset(visit,0,sizeof(visit));
		visit[ntext] = true;
		tq = hq = 0;
		que[tq++] = ntext;
		
		while(hq < tq && !visit[ 0 ] )
		{
			unsigned pos = que[hq++];
			
			for(unsigned i = 0 ; i < pos; ++i)
			{
				if( ! visit[ i ] )
				{
					if (unsigned idx = g[ i ][ pos - i ]  )
					{
						que[ tq++ ] = i;
						visit[ i ]  = true;
						widx [ i ]  = idx;
					 	wprev[ i ]  = pos;
					}
				}
			}
		}
		
		if (!visit[0])
		{
			//No solution.
			*w++ = 'N';
			*w++ = 'o';
			*w++ = ' ';
			*w++ = 's';
			*w++ = 'o';
			*w++ = 'l';
			*w++ = 'u';
			*w++ = 't';
			*w++ = 'i';
			*w++ = 'o';
			*w++ = 'n';
			*w++ = '.';
			*w++ = '\n';
		}
		else
		{
			unsigned pos = 0;
			while(pos < ntext)
			{
				unsigned idx = widx[pos];
				for(unsigned i = 0; i != ls[idx]; ++i)
				{
					*w++ = buffer[ps[idx] + i];
				}
				*w++ = ' ';
				pos = wprev[pos];
			}
			w[-1] = '\n';
			
		}
		
		
	}
	
	if(w != buffer)
	{
		fwrite(buffer, 1, w - buffer, stdout);
	}
	return 0;
}

int main()
{
	
 #ifndef ONLINE_JUDGE
      freopen("input.txt","r",stdin);
      freopen("output.txt","w",stdout);
 #endif 
 
   solve();
   return 0;
}  
