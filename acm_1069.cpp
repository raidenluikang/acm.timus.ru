
//Code Prufer  O(N) solution.

#include <cstdio>

#define N  7506
 
char buffer[ 262144 ]; 
char const* o;
char * w;
void initRead()
{
	unsigned n_read;
	n_read = fread(buffer, 1, sizeof(buffer)- 2, stdin);
	buffer[n_read] = '\0';
	o = buffer;
}
unsigned   readInt(){
	//const unsigned short ten  = 10; // u*10 = u*8 + u*2 = (u<<3) + (u<<1)
	unsigned   u = 0;
	while(*o && *o<=32)++o;
	while(*o>='0'&&*o<='9')u = u * 10 + *o++ -'0'; //((u<<3)+(u<<1)) + *o++ -'0';
	return u;
}
void initWrite()
{
	w = buffer;
}

void writeChar(char c){*w++ = c;}

void writeInt(unsigned   u){
	unsigned   v  = u, vn = 0;
	
	//1. number of digits of v
	do vn++; while(v/=10);
	
	//2. presave vn.
	v = vn;
	
	//3. fill from end.
	while(vn --> 0) 
	   w[ vn ] = u % 10 + '0',
	   u /= 10;
	
	//4. increase position.
	w += v;
}
void flushWrite(){
	if (w != buffer){
		*w = '\0';
		fwrite(buffer,1,w-buffer,stdout);
		w = buffer;
	}
}

unsigned   prufer_code[N];
unsigned   degree[N];
unsigned   pos[ N ];
unsigned   result[ N ];
unsigned   parent[ N ];
unsigned int   n;

void readPruferCode()
{
	unsigned   u = 0;
	initRead();
	n = 0;
	while((u = readInt()) > 0)
	   prufer_code[n++] = u-1;
	
	++n;   
	 
}

void solvePruferCode()
{
	//1. degree
	for(unsigned i = 0; i != n; ++i)
	    degree[i] = 1;
	    
	//2. increase degree
	for(unsigned i = 0; i != n - 1; ++i)
	    degree[prufer_code[i]]++;
	
	//degree[i] == 1 + number of children of i-th node.
	
	//3. pos
	pos[0] = 0;
	for(unsigned i = 1; i != n; ++i)
	{
		pos[ i ] = pos[ i - 1 ] + degree[ i - 1 ] - 1;
	}
	
	//4.  algo O(N)
	unsigned int ptr = 0, leaf, v;
	while(ptr != n && degree[ptr] != 1)
	     ++ptr;
	
	leaf = ptr;
	for(unsigned i = 0; i != n - 1; ++i)
	{
		v = prufer_code[ i ];
		
		parent[ leaf ] = v;
		
		--degree[leaf];
		
		if ( --degree[v] == 1 && v < ptr){
			   leaf = v;
		} else {
			++ptr;
			while (ptr < n && degree[ptr] != 1)
				++ptr;
			leaf = ptr;
		}
	}
	
    for(unsigned i = 0; i != n - 1; ++i)
    {
		//printf("parent[%d] = %d\n",1+i, 1 + parent[i]);
		unsigned p = parent[ i ];
		result[ pos[ p ]++ ] = i;
	}
	 
}

void writePruferCode()
{
	unsigned j = 0;
	
	//1. init writer
	initWrite();
	
	for(unsigned i = 0; i != n - 1 ; ++i)
	{
		//1. i:
		writeInt( i + 1 );
		writeChar( ':' );
		 
		for ( ; j  != pos[ i ] && result[j] < parent[i] ; ++j )
		{
			writeChar(' ');
			writeInt( 1 + result[ j ]);
		}
		
		writeChar(' ');
		
		writeInt(parent[i] + 1);
		
		for( ; j != pos[i]; ++j)
		{
			writeChar(' ');
			writeInt(1 + result[j]);
		}
		//now Line break
		writeChar('\n');
	}
	writeInt(n);
	writeChar(':');
	for( ; j != pos[n-1]; ++j)
	{
		writeChar(' ');
		writeInt(1 + result[j]);
	}
	writeChar('\n');
	flushWrite();
}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif
    
    //1. read prufer code
    readPruferCode();
    
    //2. solve 
    solvePruferCode();
    
    //3. write
    writePruferCode();
    
    //4.end
    return 0;
}  
