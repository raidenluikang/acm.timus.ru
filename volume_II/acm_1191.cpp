// acm.timus.ru  1191. Catch the thief!

#include <cstdio>

char in[65536];
char const* o;

int L;
int N;
int K[100];

int readInt()
{
    int u = 0;
    
    while(*o && *o <= 32)++o;
    while(*o >='0' && *o <= '9') u = (u << 3) + (u << 1) + (*o++ - '0');
    
    return u;
}

int solve()
{
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    L = readInt();
    N = readInt();
    
    for(int i =0 ; i != N; ++i)
        K[i] = readInt();
    
    
    int R = 0;
    for(int i = 0; i != N && L > 0 ; ++i)
    {
        R += K[i];
        if ( R > L)
        {
            puts("YES");
            return 0;
        }
    
        L += (K[i] - (L-R) % K[i]);
    }
    
    puts("NO");
    
    return 0;
    
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt","w", stdout);
#endif 
    
    solve();
}
