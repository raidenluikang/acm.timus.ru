// acm.timus.ru 1074. Very Short Problem


#include <cstdio>

static const int N = 200;


static const int G[10][5]
{
    // '-'  9    .    e    %
    //  0   1    2    3    4
     {  1,  2,   3,   9,  9 }, // 0 - start
     {  9,  2,   3,   9,  9 }, // 1 - int sign
     {  9,  2,   4,   6,  9 }, // 2 - int digits
     {  9,  5,   9,   9,  9 }, // 3 - dot without int digits
     {  9,  5,   9,   9,  9 }, // 4 - dot with int digits
     {  9,  5,   9,   6,  9 }, // 5 - float digits
     {  7,  8,   9,   9,  9 }, // 6 - e|E symbol
     {  9,  8,   9,   9,  9 }, // 7 - exp sign
     {  9,  8,   9,   9,  9 }, // 8 - exp digits
     {  9,  9,   9,   9,  9 } //  9 - error
};
static const int F[10]=
{
    // 0   1   2   3   4   5   6   7    8    9
       0,  0,  1,  0,  0,  1,  0,  0,   1,   0
};
// states:  0 -> start 
//          1 -> int sign
//          2 -> int digits
//          3 -> dot without int digits
//          4 -> dot with int digits
//          5 -> float digits
//          6 -> E|e  symbol
//          7 -> exp sign
//          8 -> exp digits
//          9 - error

// aphabet  :   +|-  --> 0
//              0..9  --> 1
//               '.'  ---> 2
//               e|E  --> 3
//               other symbols 4
int getID(char c)
{
    switch(c)
    {
        case '-': case '+': return 0;
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': return 1;
        case '.': return 2;
        case 'e' : case 'E': return 3;
        default : return 4;
    }
}

//<digit> ::= 0|1|2|3|4|5|6|7|8|9
//<unsigned integer number> ::= <digit>|<digit><unsigned integer number>
//<sign> ::= +|-
//<integer number> ::= <unsigned integer number>|<sign><unsigned integer number>
//<exponent symbol> ::= e|E
//<exponent> ::= <exponent symbol><integer number>
//<simple unsigned real number> ::= <unsigned integer number>|.<unsigned integer number>|<unsigned integer number>.<unsigned integer number>
//<simple real number> ::= <simple unsigned real number>|<sign><simple unsigned real number>
//<real number> ::= <simple real number>|<simple real number><exponent>
        

bool isReal(const char s[], const int n)
{
    int st = 0;
    for(int i = 0; i != n; ++i)
        st = G[ st ][ getID( s [ i ] ) ] ;
    
    return F[ st ];
}

// return number of written symbols.
int writeFailure(char w[])
{
    //Not a floating point number
    static const char U[] = "Not a floating point number";
    int i = 0;
    for(; U[i] != '\0'; ++i)
        w[ i ] = U[ i ];
    return i;
}

//        1      2      3     4    5  6    7
// w[]:  [+|-] [0..9] ['.'] [0..9][e][+|-][0..9] 
// returns number of symbols written to w[] array - normalized array.
int normalize(const char s[], const int n, char w[])
{
    int j = 0, i = 0;
    
    // 1. integer sign
    if (s[ i ] == '-' || s[ i ] == '+')
    {
        w[ j++ ] = s[ i++ ];
    }
    else
    {
        w[ j++ ] = '+';
    }
    
    
    //2. integer digits
    if ( s[ i ] >= '0' && s[ i ] <='9')
    {
        do w[ j++ ] = s[ i++ ]; while( s[ i ] >= '0' && s[ i ] <= '9' );
    }
    else
    {
        w[ j++ ] = '0';
    }
    
    
    //3. dot
    if (s[ i ] == '.')
    {
        w[ j++ ] = s[ i++ ];
        
        //4. fractional digits
        if (s[i] >='0' && s[i] <= '9')
        {
            do w[j++] = s[i++]; while(s[i]>='0' && s[i] <= '9');
        }
        else
        {
            w[j++] = '0';
        }
    }
    else
    {
        //3 and 4 dot and fractional digit
        w[j++] = '.';
        w[j++] = '0';
    }
    
    
    //5. 'e' symbol
    if ( s[ i ] == 'e' || s[ i ] == 'E')
    {
        w[ j++ ] = 'e'; ++i;
        
        //6. exponenta sign
        if (s[ i ] == '-' || s[ i ] == '+')
        {
            w[ j++ ] = s[ i++ ];
        }
        else
        {
            w[ j++ ] = '+';
        }
        
        //7. exponenta digits
        while(s[ i ] >='0' && s[ i ] <= '9')
            w[ j++ ] = s[ i++ ];
    }
    else
    {
        // 5, 6, and 7 :  'e' sign and digits
        w[ j++ ] = 'e';
        w[ j++ ] = '+';
        w[ j++ ] = '0';
    }
    
    return j;
}


//convert [+|-][0..9]  representation s[] to integer
// return 10^8 if integer is a very large number.
int expInt(const char s[], const int n)
{
    unsigned  e = 0, h = 0;
    int i= 0;
    if (s[0] == '-')h = ~0, ++i; else if (s[i] == '+')++i;
    for(; i != n; ++i)
    {
        e = ( e << 3 ) + ( e << 1 )  + s[i] - 48;
        if (e > 100000000)
            return (100000000 ^ h) + !!h;
    }
    return ( e ^ h )  + !!h;
}

// write 0.00000   to w[]  with precision.
// return number of written symbols.
int writeZero(const int precision, char w[])
{
    int i = 0;
    w[ i++ ] = '0';
    if ( precision > 0 )
    {
        w[ i++ ] = '.';
        for(int p = 0; p != precision; ++p)
            w[ i++ ] = '0';
    }
    return i;
}
 
// writes with precision and returns number of symbols
int writePrecision(const char s[], const int n, const int precision, char w[ ])
{
    
    // i_dot - position of dot
    // i_e   - position of 'e' symbol
    // z_i   - position of first non-zero digit of integer part, if all integer digits is zero, z_i == i_dot
    // z_f   - position of first non-zero digit of fractional part, if all fractional digits is zero , z_f == i_e
    // l_i   - number of integer digits
    // l_f   - number of fractional digits.
    int i_dot = 0, i_e = 0, e;
    int z_i = 0, z_f = 0;
    int l_i = 0, l_f = 0;
    for(int i= 0; i != n; ++i)
    {
        if (s[i] == '.') i_dot = i ;
        
        if (s[i] == 'e') i_e   = i ;
        
        if (s[i] >= '1' && s[i] <= '9')
        {
             if(z_i == 0 && i_dot == 0 && i_e == 0)
                 z_i = i;
             
             if (z_f == 0 && i_dot != 0 && i_e == 0) 
                 z_f = i;
        }
    }
    if ( z_i == 0 ) z_i = i_dot;
    if ( z_f == 0 ) z_f = i_e;
    
    l_i = i_dot - 1;// -1 because, s[0] is sign symbol.
    l_f = i_e - i_dot - 1;// 
    
    // s[i_e] == 'e'
    // s[i_e+1] == '-' or '+'
    // s[i_e + 2] .. s[n-1]  == digits
    e = expInt(s + i_e + 1, n - i_e - 1);
    
    
    
    // if integer digits and fractional digits both of zero - so result also will be zero.
    if ( z_i == i_dot && z_f == i_e )
    {
        return writeZero(precision, w);
    }
    
    // if e is very large or very small fill with zero.
    if ( e > 1000000  || e < -1000000 )
    {
        while (e > 1000000) ;
        //writeZero
        return writeZero(precision, w);
    }
    
    
    
    // now e is zero
    if ( e == 0 )
    {
        // if no precision required
        if ( precision == 0 )
        {
            // if integer part is zero write zero
            if (z_i == i_dot)
                return writeZero(precision, w);
            
            
            int i = z_i, j = 0;
            
            if ( s[ 0 ] == '-')
                w[ j++ ] = '-';
            
            for( ; i != i_dot; ++i)
            {
                w[j++] = s[ i ];
            }
            
            return j;
        }
        
        // precision > 0
        
        // if number of fractional digits less than precision, so write all s[] and add to leading zero to end.
        if ( l_f <= precision)
        {
            int i = z_i, j = 0;
            int lead_zero = precision - l_f;
            
            if (s[0] == '-')
                w[j++] = '-';
            
            if (z_i == i_dot)
            {
                w[j++] = '0' ;
            }
            else
            {
                while(i != i_dot) w[j++] = s[i++];
            }
            
            ++i;//skip dot.
            
            w[j++] = '.';
            
            while( i != i_e)
                w[j++] = s[i++];
            
            for( ; lead_zero > 0; --lead_zero)
                w[j++] = '0';
            
            return j;
        }
        
        // l_f > precision
        // if integer digits are zero, and first precision digits also is zero, so result is zero.
        if (z_i == i_dot && z_f - i_dot > precision)
            return writeZero(precision, w);
        
        {
            int i= z_i, j = 0;
            
            if ( s[ 0 ] == '-' )
                w[j++] = '-';
            
            if (z_i == i_dot)
            {
                w[j++] = '0';
            }
            else
            {
                while(i != i_dot)w[j++] = s[i++];
            }
            
            ++i; // skip dot
            
            w[j++] = '.';
            
            for(int p = 0; p != precision; ++p)
                w[j++] = s[i++];
            
            return j;
        }
        
    } // end e == 0
    
    
    if (e > 0)
    {
         
        // need shift left
        if ( l_f >= e) // at most e digits 
        {
            int d = l_f - e; // fractional digits after shifting
            if (precision == 0)
            {
                if ( z_i == i_dot && z_f - i_dot > e)
                    return writeZero(precision, w);
                
                int i = z_i, j = 0;
                
                if (s[0] == '-')w[j++] = '-';
                
                if (z_i == i_dot)
                {
                    i = z_f;
                    for( ; i !=  i_dot + e + 1; ++i)
                        w[j++] = s[i];
                    return j;
                }
                
                while(i != i_dot)w[j++] = s[i++];
                ++i;//skip dot
                for( ; i != i_dot + e + 1; ++i)
                    w[j++] = s[i];
                //--------------
                return j;
            } // end precision == 0
            
            
            if ( precision <= d )
            {
                if (  z_i == i_dot && z_f - i_dot > e + precision)
                    return writeZero(precision, w);
                
                
            }
            
            {
                int i = z_i, j = 0;
                if (s[0] == '-')
                    w[ j++ ] = '-';
                
                if (z_i == i_dot)
                {
                    if (z_f - i_dot > e)
                    {
                        w[j++] = '0';
                        w[j++] = '.';
                        i = i_dot + e + 1;
                        int p = 0;
                        for( ; p != precision && i != i_e; ++p)
                            w[j++] = s[i++];
                        for( ; p != precision; ++p)
                            w[j++] = '0';
                        return j;
                    }
                    i = z_f;
                    while(i != i_dot + e + 1)
                    {
                        w[j++] = s[i++];
                    }
                    
                    w[j++] = '.';
                    
                    int p = 0;
                    
                    for( ; p != precision && i != i_e; ++p)
                        w[j++] = s[i++];
                    
                    for( ; p != precision; ++p)
                        w[j++] = '0';
                    
                    return j;
                } // end z_i == i_dot
              
                while( i != i_dot)w[j++] = s[i++];
                
                ++i;//skip dot
                
                while( i != i_dot + e + 1)w[j++] = s[i++];
                
                w[j++] = '.';
                int p = 0;
                for( ; p != precision && i != i_e; ++p)
                    w[j++] = s[i++];
                
                for( ; p != precision ; ++p)
                    w[j++] = '0';
                return j;
            } // end scope
        } // end l_f >= e
        
        // there l_f < e
        
        // there can't be s is zero
        {
            int i= z_i, j = 0;
            int d = e - l_f;
            if (s[0] == '-')w[j++] = '-';
          
            if (z_i == i_dot)
            {
                i = z_f;
                
                while ( i != i_e )
                    w[j++] = s[i++];
            }
            else
            {
                while(i !=i_dot)w[j++] = s[i++];
                ++i;//skip '.';
                while(i != i_e)w[j++] = s[i++];
            }
            
            for ( ; d > 0; --d)
                w[j++] = '0';
            
            if (precision > 0)
            {
                w[j++] = '.';
                
                for(int p = 0; p != precision; ++p)
                    w[j++] = '0';
            }
            
            return j;
        }// end l_f < e
    } // end if e > 0
    
    // there e < 0
    
    {
        //    0123456789
        // s: +343242.342342
        
        //get absolute value
        e = -e;
        
        if ( precision == 0 )
        {
            if ( e >= l_i ||  z_i > l_i - e)
                return writeZero(precision, w);
            
            //e < l_i 
            int const d = l_i  - e;
            int i = z_i, j = 0;
            
            if ( s[ 0 ] == '-' )
                w[j++] = '-';
            
            while( i <= d )
                w[j++] = s[i++];
            
            return j;
        } // end precision == 0
        
        
        // there precision > 0
        
        if ( e >= l_i )
        {
            int const d = e - l_i; // number of zero
            
            if ( d >= precision)
                return writeZero(precision, w);
            
            if (d + precision <= z_i)
                return writeZero(precision, w);
                
            int t = precision - d;
            
            int j = 0, i = 0;
            
            if (s[0] == '-')
                w[j++] = '-';
            
            w[j++] = '0';
            w[j++] = '.';
            
            for(  ; i != d; ++i)
                w[j++] = '0';
           
            i = 1;
            for( ; t > 0 && i != i_dot; -- t)
                w[j++] = s[i++];
            
            if (t > 0)
            {
                i = i_dot + 1;
                for( ; t > 0 && i != i_e;  --t)
                {
                    w[j++] = s[i++];
                    
                }
                
                for( ; t > 0 ; --t )w[j++] = '0';
            }
            
            return j;
        } // end e >= l_i
        
        
        // there e < l_i
        
        {
            // d - is number of integer part
            int const d = l_i - e;
            if (z_i == i_dot)
            {
                if (e + (z_f - i_dot) > precision)
                {
                    return writeZero(precision, w);
                }
                
                int j = 0, i = d + 1, t = 0;
                if (s[0] == '-')w[j++] = '-';
                
                w[j++] = '0';
                w[j++] = '.';
                
                while ( i != i_dot && t > 0)
                    w[j++] = s[i++], --t;
                
                if (t  > 0 )
                {
                    ++i;//skip dot
                    while ( i != i_e && t > 0)
                        w[j++] = s[i++], --t;
                    for( ; t > 0; --t)
                        w[j++] = '0';
                }
                return j;
            }
            
            //s[0] = sign
            // s[1] ... s[d] - integer part
            // s[d+1]...s[i_dot-1] = fractional part
            
            if ( z_i > d )
            {
                if (z_i - d > precision)
                    return writeZero(precision, w);
                
                int j = 0, i = d+1, t = precision;
                if (s[0] == '-')w[j++] = '-';
                
                while (i != i_dot && t > 0)w[j++] = s[i++], --t;
                
                if (t > 0)
                {
                    ++i;//skip dot
                    while ( i != i_e && t > 0)w[j++] = s[i++], --t;
                    for( ; t > 0 ; --t)
                        w[j++] = '0';
                }
                
                return j;
            }
            
            // z_i <= d
            {
                int i = z_i, j = 0, t = precision;
                
                if (s[0] == '-')
                    w[j++] = '-';
                
                while ( i != d + 1 )
                    w[j++] = s[i++];
                
                w[j++] = '.';
                
                while (i != i_dot && t > 0)
                    w[j++] = s[i++], --t;
                
                if (t >0)
                {
                    ++i;
                    for( ; i != i_e && t > 0; --t)
                        w[j++] = s[i++];
                    for( ; t > 0; --t)
                        w[j++] = '0';
                }
                return j;
            } // end z_i <= d
        } // end e < l_i
    }// end e < 0
    
    
    return 0;
}



char in [ 1 << 20 ];
char out[ 1 << 20 ];
char tmp[ 4096 ]; // input string length <= 100

char const* o;
char* w;

int solve()
{
    o = in;
    w = out;
    
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    while(*o)
    {
        if ( o[ 0 ] == '#' && ( o[1] == '\0' || o[1] == '\n') )
            break;
        
        const char* s = o;
        
        int n, precision = 0;
        
        while(*o && *o != '\n')
            ++o;
        n = o - s;
        
        if (*o == '\n')
            ++o;
        
        while(*o && *o <= 32)++o;
        
        while(*o >= '0' && *o<='9') precision = (precision << 3) + (precision << 1) + (*o++ - '0');
        
        while (*o && *o != '\n')++o;
        
        if (*o == '\n')
            ++o;
        
        if (isReal(s,n))
        {
            int tn , wn;
            tn = normalize(s, n, tmp);
            tmp[tn] = 0;
            wn = writePrecision(tmp, tn, precision, w);
            
            w += wn;
            *w++ = '\n';
        }
        else
        {
           int wn;
           wn = writeFailure(w);
           w += wn;
           *w++ = '\n';
        }
    }
    
    
    if (w != out)
        fwrite(out, 1, w - out, stdout);
    
    return 0;
}

int main(int argc, char * argv[])
{
#ifndef ONLINE_JUDGE
    freopen( "input.txt", "r", stdin ) ;
    freopen( "output.txt", "w", stdout ) ;
#endif
    
    solve();
}


