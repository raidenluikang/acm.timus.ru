//1404. Easy to Hack!


#include <cstdio>


int main()
{
#ifndef ONLINE_JUDGE
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    char s[128] = {};
    char o[128] = {};
    int  p[128] = {};
    int n;
    s[fread(s,1,127,stdin)] = 0;
    
    n = 0;
    
    while( n < 128 && s[n]>='a' && s[n]<='z')
        ++n;
    
    for(int i= 0; i < n; ++i)
        p[i] = s[i] - 'a';
    
    
    for(int i= 0, d = 5, t = 0; i < n; ++i)
    {
        t = p[ i ];
        p[i] -= d;
        while(p[i] < 0)
        {
            p[i] += 26;
            t += 26;
        }
        
        o[i] = 'a' + p[ i ];
        d = t;
    }
    puts(o);
    return 0;
}
