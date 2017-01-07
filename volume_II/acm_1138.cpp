

//1138. Integer Percentage


#include <cstdio>
 
unsigned char d[10008];

int q[40008];
int h,t;
int solve()
{
    int n,s;
    scanf("%d%d",&n,&s);
    for(int i = 0; i != 10008; ++i)
        d[i] = 0;
    
    d[s] = 1;
    h = t = 0;
    q[t++]= s;
    while( h < t )
    {
        int u = q[h++];
        
        // i -percentage
        // v = u * (1+i/100) = u + (u * i /100)
        
        for(int i= 1; i <= 100; ++i)
        {
            int v = u * i;
            if (v % 100 == 0)
            {
                v /= 100;
                v += u;
                if ( v <= n && d[ v ] < d[ u ] + 1)
                {
                    d[ v ] = d[ u ] + 1;
                    q[ t++ ] = v;
                }
            }
        }
    }
    
    int ans = 0;
    for(int i= 0; i != 10008; ++i)
        ans = d[i] > ans ? d[i] : ans;
    
    printf("%d\n", ans);
    return 0;
}

int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    
    solve();
    
    return 0;
}
