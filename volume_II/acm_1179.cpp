//acm.timus.ru 1179. Numbers in Text


#include <stdio.h>

char in[ (1 << 20) | ( 1 << 16 ) ];


static const int max_n = 36;
int d[ 256 ];
int w[ 40 ];
int idx[ 40 ][ 40 ];
// i --> j

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 

    int n;
    int k, t;
    n = fread(in,1,sizeof(in)-4, stdin);
    in[n++] = '\n'; // for separate

    for(int c = 0; c < 256; ++c)d[c] = 0;
    for(int c = '0' ; c <= '9'; ++c)d[c] = c - '0' + 1;
    for(int c = 'A'; c <= 'Z'; ++c)d[c] = c - 'A' + 11;

    d['\n'] = max_n + 1;
    d[' '] = max_n + 1;
    
    
    int s = ' ';//s := #32;
    for(int i= 0; i != n; ++i)
    {
        int c = in[i];
        //if (d[c] > d[s])
        {
            // increment all from d[s] .. d[c]  (d[c] not included)
            idx[ d[ s ] ][ d[ c ] ]++;
           // for(int j = d[c] - 1; j >= d[s]; --j)
           //     w[ j ]++;
        }
        s = c;
    }
    
    for(int i = 0; i != 40; ++i)
    {
        for(int j = i+1; j != 40; ++j)
        {
            int x = idx[i][j]; // increment w[k] by x, where  i <= k < j
            for(int k = i; k < j; ++k)
                w[k] += x;
        }
    }
    t = 0;
    k = 0;
    for(int i= 2; i <= 36; ++i)
    {
       // printf("freq[%d] = %d\n",i, w[i]);
        if (w[i] > t)
        {
            t = w[i];
            k = i;
        }
    }
    printf("%d %d\n", k, t);
}
