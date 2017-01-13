
#include <cstdio>

int solve()
{
    char s[64];//std::string s;
    unsigned n = 0;
     s[fread(s,1,64,stdin)] = 0;
   
    for(unsigned i = 0; s[i] >='0' && s[i] <='9'; ++i)
    {
            unsigned digit  = s[ i ] - '0';
            n = n * 3 + digit;
            n = n % 7;
    }
    
     printf("%u\n", n);
    //std::cout << n << '\n';

    return 0;
}

int main() 
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    solve();

    return 0;
}

