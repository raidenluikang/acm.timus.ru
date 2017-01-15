#include <cstdio>


const int maxn = 32767;

unsigned query [ 1 << 17 ];
unsigned ans [ 1 << 17 ];
unsigned head[maxn+1];
unsigned next[1<<17];
unsigned r[maxn+1];

char in[1 << 21];
char const* o;
char * w;

int powm(int x, int n, int p)
{
    int r = 1;
    while(n)
    {
        if (n&1)r = (r * x )% p;
        x = (x*x)%p;
        n/=2;
    }
    return r;
}

void writeNoRoot()
{
    *w++ = 'N';
    *w++ = 'o';
    *w++ = ' ';
    *w++ = 'r'; *w++ = 'o';*w++ = 'o';*w++ = 't';*w++ = '\n';
}

void writeInt(int u, char c)
{
    int v = u, n = 0;
    do ++n;while(v/=10);
    v = n;
    while(v-->0)w[v] = u%10 + '0',u/=10;
    w += n;
    *w++ = c;
}

int readInt()
{
    int u = 0;
    while(*o && *o <= 32)++o;
    while(*o >='0'&&*o<='9') u = (u << 3) + (u << 1) + (*o++ - '0');
    return u;
}

int main(int argc, char * argv[])
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    int K, a, n;
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    //scanf("%d",&K);
    K = readInt();
    
    //for(int i = 0; i <= maxn; ++i)head[i] = 0;
    
    for(int i = 1; i <= K; i++)
    {
      //  scanf("%d%d",&a,&n);
        a = readInt();
        n = readInt();
        a %= n;
        next[ i ] = head[ n ];
        head[ n ] = i;
        query[ i ] = a ;
    }
    
    for(int n = 1; n <= maxn; ++n)
    {
        
        if (head[ n ] == 0)continue;
        
        if ( n % 4 == 3)
        {
            for(int i = head[n]; i != 0; i = next[i])
            {
                int a = query[i];
                int x = powm( a, ( n + 1 ) / 4, n );
                
                if (( x * x) % n == a)
                    ans[ i ] = x | (n << 16);
                else
                    ans[ i ] = 0;
            }
            continue;
        }
        
        if (n % 8 == 5 )
        {
            int k = n / 8;
            for(int i = head[n]; i != 0; i = next[i])
            {
                int a = query[i];
                int r = powm(a, (n-1)/4, n);
                int x;
                if (r == 1)
                {
                    x = powm(a, k+1, n);
                }
                else
                {
                    x = powm(2, 2*k+1, n);
                    x = (x * powm(a, k + 1, n)) % n;
                }
                
                if ((x*x)%n == a)
                    ans[i] = x | (n << 16);
                else
                    ans[i] = 0;
            }
            continue;
        }
        for(int x = 0, x2 = 0; x < n; ++x)
        {
            r[ x2 ] = x | (n << 16);
            x2 += x + x + 1;
            while(x2 >= n)
                x2 -= n;
        }
        
        for(int i = head[n]; i != 0; i = next[i])
        {
            int a = query[i];
            int m = r[a] >> 16;
            int x = r[a] & 65535;
            
            //int y = n - x;
            
            if (m == n)
                ans[ i ] = x | (n << 16);
            else
                ans[ i ] = 0;
            
        }
        
        
    }
   
    w = in;
    for(int i = 1; i <= K; i++)
    {
        if (!ans[i]){
            writeNoRoot();
            continue;
        }
        int n = ans[i] >> 16;
        int x = ans[i] & 65535;
        int y = n - x ;
        if (x > y){ int t = x; x = y; y = t;}
        if( x == y)
            writeInt(x, '\n');//printf("%d\n", output[i].first);
        else 
        {
            writeInt(x, ' ');
            writeInt(y,'\n');
        }
    }
    
    fwrite(in,1,w-in,stdout);
}
