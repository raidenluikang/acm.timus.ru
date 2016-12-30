
#include <cstdio>
 
char in  [ 16384 ];
char out [ 84    ];

int main()
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    for(int i = 0; i != 80; ++i)out[i] = ' '; //space
    out[80] = '\0';
    
    int n;
    n = fread(in,1,sizeof(in)-4,stdin);
    if (n > 0 && in[n-1] == '\n')--n;
    for(int i= 0, p = 0; i !=n ; ++i)
    {
        switch(in[i])
        {
            case '>': // go right
                if ( (++p) == 80)
                    p = 0;
                break;
            case '<': // go left 
                if (p == 0)
                    p = 0;
                else
                    --p;
                break;
            default:
                out[p++] = in[i];
                if (p == 80)p = 0;
                break;
        }
    }
      
    fwrite(out, 1, 80, stdout);
    
    return 0;
}
