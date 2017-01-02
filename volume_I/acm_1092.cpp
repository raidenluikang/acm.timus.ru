// acm.timus.ru 1092. Transversal
// source based on  https://github.com/BoleynSu/acmicpc/blob/master/archives/problemset/acm.timus.ru/1092.cpp .

#include <cstdio>

static const int N = 44;

char s[ N ][ N ];
int n;

char in[ 65536 ];
char const * o;

char out[65536*4];
char * w;

int init()
{
    o = in;
    w = out;
    
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    return 0;
}

// u : 1..41
int writeInt(int u)
{
    if (u < 10)
        *w++ = u + '0';
    else 
    {
        *w++ = u / 10 + '0';
        *w++ = u % 10 + '0';
    }
    return 0;
}

int writeStr(const char* p)
{
    while(*p)*w++ = *p++;
    return 0;
}
int readData()
{
    init();
    
    n = 0;
    
    while( *o && *o <= 32 )
        ++o;
    
    while( *o >= '0' && *o <= '9' )
        n = ( n << 3 ) + ( n << 1 ) + ( *o++ -'0' );
    
    //go to next Line
    while (*o && *o != '\n')
        ++o;
    
    if (*o == '\n')
        ++o;
    
    n += n + 1; // n = 2*n + 1
    for(int i = 0; i != n ; ++i)
    {
       for(int j = 0; j != n; ++j)
           s[ i ][j] = *o++;

       //go to next Line
        while (*o && *o != '\n')++o;
        if (*o == '\n')++o;
    }
    return 0;
}

char invert(char c)
{
    switch(c)
    {
        case '+': return '-';
        case '-': return '+';
        default: return 0;
    }
}

void transveral(int a, int b, int c, int d)
{
    s[ a ][ d ] = invert( s[ a ][ d ] );
    s[ a ][ b ] = invert( s[ a ][ b ] );
    s[ c ][ b ] = invert( s[ c ][ b ] );
    s[ c ][ d ] = invert( s[ c ][ d ] );
    
    for(int i = 0; i != n; ++i)
    {
        if (a == i) writeInt(b+1);
        else if (c == i)writeInt(d+1);
        else if (b == i)writeInt(a+1);
        else if (d == i)writeInt(c+1);
        else writeInt(i+1);
    
        *w++ = ' ';
    }
    w[-1] = '\n';//change last to '\n' :)
    
    //second change
    for(int i = 0 ;i != n; ++i)
    {
        if (a == i)writeInt(d + 1);
        else if (c == i)writeInt(b+1);
        else if (b == i)writeInt(a+1);
        else if (d == i)writeInt(c+1);
        else writeInt(i+1);
        *w++ = ' ';
    }
    w[-1] = '\n';
}
 

int solve()
{
    readData();
    
    writeStr("There is solution:");
    *w++ = '\n';
    
    bool n_plus_odd = false;
    
    for(int i = 0; i != n; ++i)
    {
        for(int j= 0; j != n; ++j)
        {
            n_plus_odd ^=  (s[i][j] == '+');
        }
    }
 
    if (n_plus_odd  )
    {
        //change main diagonal
        for(int i  = 0 ;i != n; ++i)
        {
            s[ i ][ i ] = invert(s[ i ][ i ]);
            writeInt( i + 1 );
            *w++ = ' ';
        }
        w[-1] = '\n';
    }
    
    for (int i = 0; i != n; i++)
    {
        int j = n - 1, _j, k = n - 1, _k;
        
        while ( j > i )
        {
            // find two '+' in the i-th row upper side of main diagonal.
              while ( ( j > i ) && ( s[ i ][ j ] != '+' ) )
                  --j;
              
              _j = j;
              --j;
              while ( ( j > i) && ( s[ i ][ j ] != '+' ) ) 
                  --j;
              
              if (j <= i)
                  break;
                  
              transveral( i, j, n - 1, _j );
              _j = -1;
        }
        
        if ( _j > i ) transveral( i, i, n - 1, _j );
        
        while ( k > i )
        {
              while ( ( k > i ) && ( s[ k ][ i ] != '+' ) ) 
                  --k;
              _k = k;
              --k;
              while ( ( k > i ) && ( s[ k ] [ i ] != '+' ) ) 
                  --k;
              if (k <= i)
                  break;
              
              transveral(k,i,_k, n - 1);
              _k = -1;
        }
        
        if ( _k > i && s[ i ][ i ] == '+') 
            transveral( i, i, _k, n -1 );
    }
    
    // flush
    if (w != out)
        fwrite(out, 1, w - out, stdout);
    return 0;
}

int main(int argc, char * argv[])
{

#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    
    solve();
    
    return 0;
}
