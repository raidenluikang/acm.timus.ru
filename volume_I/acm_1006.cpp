
//acm.timus.ru 1006. Squares.

#include <stdio.h>
#include <string.h>

#define L_U  218   // left upper
#define L_D  192   // left down
#define R_U  191   // right upper
#define R_D  217   // right down
#define VER  179  // vertical
#define HOR  196  // horizontal 
#define EMT  200
#define DOT  46

struct alignas(64) solver
{
	unsigned char buffer[65536];
	unsigned char out[65536];
	unsigned char s[64][64];
	unsigned char const* o;
	unsigned char const* e;
	unsigned char * w ;
	bool eof_;
	
	unsigned n_sqr;
	unsigned xs[2048], ys[2048], as[2048];
	solver() : o( buffer ), e( 0 ), w( out ), eof_( false )
	{
		memset(s, 0, sizeof(s));
	}
	
	void load()
	{
	   unsigned n;
	   n = fread(buffer, 1, 65536, stdin);
	   e = buffer + n;
	   o = buffer;
	   eof_ = n < 65536;
	}
	
	inline unsigned char peekChar()const{ return *o      ;   }
	inline unsigned char nextChar()     { return *o++    ;   }
	inline bool eof()const     { return  o == e ;   }

    void readData()
    {
		load();
		for(int i = 0; i != 20; i++)
		{
			for(int j= 0;j != 50; ++j)
			{
				s[i][j] = nextChar();
			}
			
			while( !eof() && nextChar() != '\n')
			   {};
		}
	}
	
	void writeInt(unsigned u, char c)
	{
		unsigned v = u, m = 0;
		do m ++; while(v/=10);
		v = m;
		while(v-->0)w[v] = u % 10 + '0', u/=10;
		w += m;
		*w++ = c;
	}
	
	void writeData()
	{
		writeInt(n_sqr, '\n');
		for(unsigned i= n_sqr; i != 0; --i)
		{
			writeInt(xs[i-1], ' ');
			writeInt(ys[i-1], ' ');
			writeInt(as[i-1], '\n');
		}
		//flush
		if (w != out)
		{
			fwrite(out, 1, w - out, stdout);
			w = out;
		}
	}
	
	inline 
	bool expected(unsigned char c, unsigned char ex)const{ return c == ex;}
	
	inline
	bool expected(unsigned char c, unsigned char ex_1, unsigned char ex_2)const{ return expected(c,ex_1) || expected(c, ex_2); }
	
	bool check(unsigned row, unsigned col, unsigned len)const
	{
		
		 
		bool ok = true;
		bool e = false;
		
		ok = ok && expected(s[row][col], L_U, EMT);
		e  = e  || expected(s[row][col], L_U);
		for(unsigned i = 1; i < len - 1 && ok; ++i)
		{
			ok = ok && expected(s[row][col+i], HOR, EMT);
			e = e || expected(s[row][col+i], HOR);
		}
		ok = ok && expected(s[row][col+len-1], R_U, EMT);
		e = e || expected(s[row][col+len-1], R_U);
		
		for(unsigned i = 1; i < len - 1 && ok; ++i)
		{
			ok = ok && expected(s[row+i][col], VER, EMT) && expected(s[row+i][col + len-1], VER, EMT);
			e = e || expected(s[row+i][col], VER) || expected(s[row+i][col+len-1], VER);
		}
		
		ok = ok && expected(s[row+len-1][col], L_D, EMT);
		e = e || expected(s[row+len-1][col] , L_D);
		
		for(unsigned i = 1; i < len - 1 && ok; ++i)
		{
			ok = ok && expected(s[row+len-1][col+i], HOR, EMT);
			e = e || expected(s[row+len-1][col+i], HOR);
		}
		ok = ok && expected(s[row+len-1][col + len-1], R_D, EMT);
		e = e || expected(s[row+len-1][col + len -1], R_D);
		
		return ok && e;
	}
	
	void clear_sqr(unsigned row, unsigned col, unsigned len)
	{
		for(unsigned i = 0; i != len; ++i)
		{
			s[row][col+i] = EMT;
		}
		for(unsigned i = 1; i != len; ++i)
		{
			s[row+i][col] = EMT;
			s[row+i][col+len-1] = EMT;
		}
		for(unsigned i = 0; i != len; ++i)
		{
			s[row+len-1][col + i] = EMT;
		}
	}
	
    void toSolve()
    {
		n_sqr = 0;
		readData();
		while(true)
		{
			
			bool ok = false;
			
			for(unsigned row = 0; row != 20; ++row)
			{
				for(unsigned col = 0; col != 50; ++col)
				{
					unsigned a_max = ( ( 20 - row < 50 - col) ? (20 - row) : (50 - col) );
					for(unsigned a = a_max; a >= 2; --a)
					{
						if (check(  row, col, a))
						{
							xs[n_sqr] = col;
							ys[n_sqr] = row;
							as[n_sqr] = a;
							++n_sqr;
							
							clear_sqr(row, col, a);
							ok = true;
							break;
						}
					}
				}
				if (ok)break;
			}
			
			if (!ok)break;
		}
		
		writeData();
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
