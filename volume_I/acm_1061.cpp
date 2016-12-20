

// acm.timus.ru 1061. Buffer Manager.

#include <cstdio>
#include <cstring>
#include <algorithm>

#ifdef _MSC_VER
__declspec(align(128))
char in[1<<17];

__declspec(align(128))
char const* o;
#else
char in[1<<17] __attribute__((aligned(128)));

char const* o __attribute__((aligned(128)));
#endif

int solve()
{
    unsigned m, n, k, l = 0, s = 0, star = 0, p ;
    m = fread(in, 1, sizeof(in) - 4, stdin);
    in[m] = '\0';
    o = in;

    n = 0;
    while(*o && *o<=32)++o;
    while(*o>=48)n = (n<<3) + (n<<1) + *o++ - 48;

    k = 0;
    while(*o && *o <= 32)++o;
    while(*o>=48) k = (k<<3) + (k<<1) + *o++ - 48;
    while(*o && *o != '\n')++o;
    
    if (*o == '\n')++o; // skip first line .
    
    if (k > n)
    {
        puts("0");
        return 0;
    }
    
    char* oo = (char*)o;
    m =  std::remove(oo, in + m, '\n') - oo;
    oo[m] = '\0';

    oo = (char*)(--o); // use 1..n indexes :)
    
    unsigned max_s = 1000000000, max_pos = 0;
    for(unsigned i = 1, j = 0; i <= n; ++i)
    {
        if (o[i] == '*' )
        {
            s = 0; 
            j = 0;
            oo[i] = '0' - 1; // for -1 :)
        }
        else if (j < k)
        {
            j++;
            s += o[i] - '0';
            if (j == k){
                if (max_s > s)
                {
                    max_s = s;
                    
                    max_pos = i - k + 1;
                }
            }
        }
        else 
        {
            s += o[i]  - o[i-k];
            if (max_s > s)
            {
                max_s = s;
                
                max_pos = i - k + 1;
            }
        }
    }

    printf("%u\n",max_pos);
    return 0;
}

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    solve();
    return 0;
}
