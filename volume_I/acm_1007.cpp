
//acm.timus.ru 1055. Combinations

#include <stdio.h>
#include <string.h>



struct alignas(64) solver
{
	char buffer[65536];
	char out[65536];
	char const* o;
	char const* e;
	char * w ;
	bool eof_;
	
	solver() : o( buffer ), e( 0 ), w( out ), eof_( false )
	{
	}
	
	void load()
	{
	   unsigned n;
	   n = fread(buffer, 1, 65536, stdin);
	   e = buffer + n;
	   o = buffer;
	   eof_ = n < 65536;
	}
	
	inline char peekChar()const{ return *o      ;   }
	inline char nextChar()     { return *o++    ;   }
	inline bool eof()const     { return  o == e ;   }
	
	bool nextLine()
	{
	    //1. read until eof
	    while( ! eof() && peekChar() <= 32) nextChar();
	    
	    if (eof() && eof_ )
	      return false;
	      
	    if (eof())
	    {
			load();
			while( ! eof() && peekChar() <= 32) nextChar();
		} 
		else if (e - o < 1024 && ! eof_) 
		{
			unsigned m = e - o ;
			memcpy( buffer, o, m ) ;
			unsigned n ;
			n = fread( buffer + m, 1, 65536 - m, stdin ) ;
			e = buffer + m + n ;
			o = buffer ;
			eof_ = n  + m < 65536 ;
		}
		
		
		if (out + 65536 - w < 1024) // flush it
		{
			if (w != out)
			{
				fwrite(out, 1, w - out, stdout);
				w = out;
			}
		}
		return true; 	
	}
	
	void toSolve()
	{
		unsigned n;
		load();
		n = 0;
		while(!eof() && peekChar() <= 32)nextChar();
		while(peekChar()>= 48) n =(n<<3) + (n<<1) + nextChar() - 48;
		
		for( ; ; )
		{
			if (!nextLine())
			  break;
			
			
			unsigned len = n - 1, sum = 0, j , i;
			
			if (o[ n - 1 ] >= 48) 
			{
				  if (o[ n ] >= 48) 
				    len = n + 1;
				  else
					len = n;
				 
			}
			
			for(i = 0; i != len; ++i)
			{
				sum += ( 1 + i ) & ( - ( unsigned )( o [ i ] - 48 ) );
			}
			
			//printf("len = %u\n", len);
		    
		    //memcpy(w, o, len);
		    
			j = sum % ( 1 + n);
			if (len == n)
			{
				memcpy(w, o, len);
				
				if ( j )
			       w[ j - 1 ] = '0';
			       
			    w += len;
			    *w++ = '\n';
			    
			    o += len;	
			    continue;  
			}
			
			if ( len < n ) // add
			{
				//0001  n = 5, len = 4
				// j = 4
				// n + 1 - j = 5 + 1 - 4 = 2
				
				// printf(" j = %u\n", j);
				//if sum %( n + 1) == 0 , add '0' at end.
				if (j == 0 || j == 1)
				{
					memcpy(w, o, len);
					w += len;
					*w++ = j + '0';
					*w++ = '\n';
					
					o += len;
					continue;
				}
				
				j = n + 1 - j; // 
				for( i = len; i > 0 ; --i)
				{
					j -= ( o[ i - 1 ] - 48 );
					if (j == 0 || j == i )
					  break;
				}
				
				//printf(" i = %u  j = %u\n",i,j);
				if ( i <= 1)
				{
					//add '0' or '1' at position i
					*w++ = ( j == 0 ) ? '0' : '1';
					memcpy(w, o, len);
					w += len;
					o += len;
					*w++ = '\n';
					continue;
				}
				
				//i > 1
				{
					memcpy(w,o,i-1);
					w += i - 1;
					o += i - 1;
					*w ++ = (j == 0) ? '0' : '1';
					memcpy(w, o, len-i+1);
					w += len - i + 1;
					o += len - i + 1;
					
					*w++ = '\n';
				}
				 
			}
			
			if (len > n) // remove
			{
				//printf(" j = %u\n",j);
				if (j == 0 )
				{
					memcpy(w, o, n);
					w += n;
					o += len;
					*w ++ = '\n';
					continue;
				}
				for( i = len; i > 0; i--)
				{
					unsigned u = o[i-1] - 48;
					//j -= (o[i-1] - 48);
					if (j == ( i & - u  ) )
					   break;
					j -= u;
				}
				//printf(" i = %u  j = %u\n",i,j);
				
				//remove i-th symbol
				if ( i == 0 )
				{
					memcpy(w, o + 1, len - 1);
					
					w += len - 1;
					o += len;
					*w++ = '\n';
					continue;
				}
				
				memcpy(w, o, i - 1);
				memcpy(w + i - 1, o + i, len - i);
				w += len - 1;
				o += len;
				*w++ = '\n';
				continue;
			}
		}//end for(;;)
		
		//flush.
		if (w != out)
	    {
		   fwrite(out, 1, w - out, stdout);
		   w = out;
	    }
	}
};

int main(int argc, char **argv)
{
#ifndef ONLINE_JUDGE
 	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif
	 solver sl;
	 
	 sl.toSolve();

	return 0;
}
