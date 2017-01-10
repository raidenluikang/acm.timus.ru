// 1189. Pairs of Integers
// AC  0.001s  296 KB

#include <cstdio>

void judge_assert(bool b)
{
    if (!b)
        printf("%d\n",1/b);
}
int digits(int n)
{
    int r = 0;
    do ++r; while(n/=10);
    return r;
}

char out[64444];
char * w;

void writeInt( int u, int d = 0 )
{
    if (d == 0)
        d = digits(u);
    for(int i = 0; i < d; ++i)
        w[d - i - 1] = u%10 + '0', u/=10;
    w += d;
}
void writeChar(char c){ *w++ = c;}

struct pt
{
    int x;
    int y;
};

pt p[1024];
int A, n;

int d[12];
int m;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    
    scanf("%d",&A);
    
    int ten[12] = {};
    
    {
        int t = A;
        m = 0;
        for(int i = 0; i != 12; ++i)
            d[i] = t % 10 , t /= 10;
        
        m = 12;
        while(m > 1 && d[m-1] == 0)
            --m;
        
        ten[0] = 1;
        for(int i= 1; i < 12; ++i)
            ten[i] = 10 * ten[i-1];
    }
    
    
    //we know m >= 2
    
    n = 0;
    for(int i = 0; i < m; ++i)
    {
        
        // X = x[j] ,  j = 0..m-1
        // Y = y[j] ,  j = 0..m-2
        
        // and x[j] = y[j], for j = 0..i-1
        // and x[j+1] = y[j], for j = i..m-2
        
        // for example: i = 2  (1-index base).
        // X = x1 x2 x3 x4
        // Y = x1 x3 x4
        
        // X + Y = 2*(x3x4) + (x2 + x1*11)*100 = A
        // A = a1 a2 a3 a4
        
        // x3x4 = (a3a4)/2
        // a1a2 = (x2 + x1*11)
        
        // x2 = 0..9  -->  x1 = (a1a2  -x2)/11
        
        
        //  i == 0:
        // 
        if (i == 0) // first digit will removed
        {
            //  X = x1x2x3..x[k-1]xk  = xh*10 + xl
            //  Y = x1x2...x[k-1]     = xh
            
            // X + Y = xh * 11 + xl = A --> xh * 11 = A - xl
          for(int xl = 0; xl < 10; ++xl)
          {
              // A >= 10 ,  so  A - xl > 0
              int xh_11 = A - xl;
              if (xh_11 % 11 == 0)
              {
                  int xh = xh_11 / 11;
                  
                  p[n].x = xh * 10 + xl;
                  p[n].y = xh;
                  ++n;
              }
          }
        }
        else  if (i == m - 1) // last digit will removed
        {
            // X = x1x2x3...xk = x1*10^(m-1) + xl
            // Y =   x2x3...xk =  xl
            
            // X+Y = x1*10^(m-1) + 2*xl
            
            //1. 2*xl < 10^(m-1)  --> 
             //    x1 = a1,  xl = al
            int a1 = A / ten[ m - 1 ];
            int al = A % ten[ m - 1 ];
             
            if (al % 2 == 0)
            {
                int xl = al / 2;
                int x1 = a1;
                
                int x = x1 * ten[m-1] + xl;
                int y = xl;
                
                p[n].x = x;
                p[n].y = y;
                ++n;
            }
            
            
            //2. 2*xl >= 10^(m-1) 
            //  xl = 10^(m-1)/2 + al/2
            //  x1 = a1 - 1
            if (al % 2 == 0 && a1 > 1)
            {
                int xl = ten[m-1]/2 + al/2;
                int x1 = a1 - 1;
                
                int x = x1 * ten[m-1] + xl;
                int y = xl;
                
                p[n].x = x;
                p[n].y = y;
                ++n;
            }
        }
        else // middle digit will removed
        {
            //  X = xh * 10^(i+1) + xr * 10^i + xl 
            //  Y = xh * 10^i + xl
            
            // xr -- removed digit
            
            // X + Y = 11*xh * 10^i + xr * 10^i + 2*xl
           
            //1. 2*xl < 10^i
            //2. 2*xl >= 10^i
            
            // 2)  A = ah*10^i + al
            //     2*xl = 10^i + al
            //   ah*10^i +al =  11*xh * 10^i + xr*10^i + 10^i + al
            // ah * 10^i = (11*xh + xr + 1)*10^i
            //   11*xh = ah - xr - 1
            
            for(int xr = 0; xr < 10; ++xr)
            {
                int al = A % ten[i];
                int ah = A / ten[i];
                if (al % 2 == 0)
                {
                    int xl = al / 2;
                    
                    int xh_11 = ah - xr ;
                    
                    if (xh_11 % 11 == 0)
                    {
                        int xh = xh_11 / 11;
                        
                        int x = xh * ten[i+1] + xr * ten[i] + xl;
                        int y = xh * ten[i] + xl;
                        
                        p[n].x = x;
                        p[n].y = y;
                        ++n;
                    }
                    else if (xh_11 % 11 == 1)
                    {
                        int xh = (xh_11-1) / 11;
                        xl += ten[i]/2;
                        
                        p[n].x = xh * ten[i+1] + xr * ten[i] + xl;
                        p[n].y = xh * ten[i] + xl;
                        ++n;
                    }
                    // 2. xl >= 10^i   
                    
                    
                }
            }
        }
    }
    
    
    for(int i = 0; i != n; ++i)
    {
        for(int j = i + 1; j != n; ++j)
        {
            if (p[i].x > p[j].x)
            {
                pt t = p[i];
                p[i] = p[j];
                p[j] = t;
            }
        }
    }
    
    // remove duplicates
    if (n > 0)
    {
        int nn = n;
        n = 1;
        for(int i= 1; i < nn; ++i)
        {
            if (p[i-1].x == p[i].x)
                ;
            else
                p[n++] = p[i];
        }
    }
    
    //printf("%d\n", n);
    //for(int i= 0; i != n; ++i)
   // {
   //     printf("%d + %*d = %d\n", p[i].x, m-1, p[i].y, A);
   // }
    
    w = out;
    writeInt(n);
    writeChar('\n');
    for(int i= 0; i<n;++i)
    {
        int x = p[i].x;
        int y = p[i].y;
        judge_assert(x + y == A);
        
        int nx = digits(x);
        int ny = digits(y);
        judge_assert(nx - 1 >= ny);
        
        writeInt(x, nx);
        writeChar(' ');
        writeChar('+');
        writeChar(' ');
        writeInt(y, nx - 1);
        writeChar(' ');
        writeChar('=');
        writeChar(' ');
        writeInt(A);
        writeChar('\n');
    }
    fwrite(out, 1, w - out, stdout);
}
