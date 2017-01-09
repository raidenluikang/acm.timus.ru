#include <cstdio>
#include <cstring>


int L, memo[ 100 ][ 100 ];
char S[1024];
char R[1024];
int n;

int min(int x, int y){ return x < y ? x : y ;}


void putchar_(char c){ R[n++] = c;}

int solve_memo()
{
    //memo[i][j] == i..j
    for(int i = 1; i < L; ++i)
    {
        memo[ i ][ i - 1 ] = 0;
    }
    
    for(int i = 0; i < L; ++i)
    {
        memo[ i ][ i ] = 1;
    }
    
    for(int i = 0; i + 1 < L; ++i)
    {
        memo[i][i+1] = ( ( S[ i ] == '(' && S[ i + 1 ] == ')' ) || 
                         ( S[ i ] == '[' && S[ i + 1 ] == ']' ) ) 
                       ? 0 : 2;
    }
    
    for(int len = 2; len < L; ++len)
    {
        for(int i = 0; i + len < L; ++i)
        {
            memo[ i ][ i + len ] = 1 + memo[ i + 1 ][ i + len ];
            
            if (S[ i ] == '(')
            {
                for(int j = i + 1; j <= i + len; ++j)
                {
                    if (S[ j ] == ')')
                    {
                        //ret = min(ret,solve(s+1,i-1)+solve(i+1,e));
                        memo[ i ][ i + len ] = min( memo[ i ][ i + len], memo[ i + 1 ][ j - 1 ] + memo[ j + 1 ][ i + len ] );
                    }
                }
            }
            else if (S[i] == '[')
            {
                for(int j = i + 1; j <= i + len; ++j)
                {
                    if (S[j] == ']')
                    {
                        memo[i][i+len] = min(memo[i][i+len], memo[i+1][j-1] + memo[j+1][i+len]);
                    }
                }
            }
        }
    }
}
#if 0
int solve(int s, int e){
    if(s>e) return 0;
    
    int &ret = memo[s][e];
    
    if( ret == -1 )
    {
        ret = 1+solve(s+1,e);
        
        if(S[ s ] == '(' || S[ s ] == '[')
        {
            for(int i = s + 1; i <= e; ++i)
                if(( S[  s ] == '(' && S[ i ] == ')' ) || 
                   ( S[ s  ] == '[' && S[ i ] == ']' )
                  )
                  ret = min(ret,solve(s+1,i-1)+solve(i+1,e));
        }
    }
    
    return ret;
}
#endif 
void print(int s, int e)
{
    if( s > e ) 
        return;
    
    int best =  memo[s][e];//solve(s, e);
    
    if( 1 + memo[s+1][e] == best)
    {
        if(S[s]=='(' || S[s]==')'){
            putchar_('(');
            putchar_(')');
        }else{
            putchar_('[');
            putchar_(']');
        }
        
        print(s+1,e);
        return;
    }
    
    for(int i = s + 1; i <= e; ++i)
    {
        if( ( ( S[ s ] == '(' && S[i] == ')') || 
              ( S[ s ] == '[' && S[i] == ']')
            ) && 
            best == memo[s+1][i-1] + memo[i+1][e] )//solve( s + 1 , i - 1 ) + solve( i + 1 , e ) )
        {
            if(S[s] == '(')
            {
                putchar_('(');
                print( s + 1, i - 1 );
                putchar_( ')' );
                print( i + 1, e);
            }else{
                putchar_('[');
                print( s + 1 , i - 1 );
                putchar_( ']' );
                print( i + 1, e );
            }
            
            return;
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 

     scanf("%s",S);
    
     L = strlen(S);
    solve_memo();
    
    n = 0; 
    print(0, L - 1 );
    
    putchar_('\0');
    
    puts(R);
    
    return 0;
}
