


#include <cstdio>
#include <cmath>

char s[2048];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
   
    std::fgets(s, 2048, stdin);
    
    int n = 0;
    while( s[ n ] >='0' && s[ n ] <= '9')
        ++n;
    s[n] = '\0';
    
    //1. check palindrom
    {
        int i = 0, j = n - 1;
        while( i < j && s[i] == s[j])
            ++i, --j;
        if (i >=j)
        {
            fputs(s, stdout);
            return 0;
        }
    }
    
    
    int i = n / 2, j = n / 2;
    
    if (n&1)
        ;
    else
        i--;
    
    // 0 1 2 3 : n = 4,  i = 2  j = 2
    while(i >= 0 && s[i] == s[j])
        --i, ++j;
    
    if(i < 0) // s - is palindrom
    {
        fputs(s, stdout);
        return 0;
    }
    
    // s[i] != s[j]
    
    // s[j] < s[i] , s[j] <--- s[i]   
    if (s[j] < s[i])
    {
        // i = 1, j = 3
        //i:  01234
        //s:  12314 --> 12321
        
        while (j < n)
            s[j] = s[i], 
                    --i,
                    ++j;
        fputs(s, stdout);
        return 0;
    }
    
    //  12331 --> 12421
    //
    if (n & 1)
    {
        i = n / 2;
        j = n / 2;
    }
    else
    {
        i = n/2 - 1;
        j = n/2;
    }
    
    while(i >= 0 && s[i] == '9')
        s[i] = s[j] = '0',
                --i, ++j;

    if (i < 0)
    {
        s[0] = '1';
        for(int i= 1; i < n; ++i)
            s[i] = '0';
        s[n++] = '1';
        s[n++] = '\0';
        fputs(s, stdout);
        return 0;
    }
    
    s[ i ]++;
    while(i>=0)
        s[j] = s[i],
                --i,
                ++j;
    fputs(s, stdout);
    //s[i]++;

    return 0;
}
