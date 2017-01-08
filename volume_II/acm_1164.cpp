




// acm.timus.ru 1164. Fillwords.

#include <stdio.h>


int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w",stdout);
#endif 

    char s[1024];
    int n, m, p;
    int x[26] = {};
    fgets(s, 1024, stdin);
    sscanf(s, "%d%d%d",&n,&m,&p);
    for(int i= 0; i != n; ++i)
    {
        fgets(s, 1024, stdin);
        for(int j = 0; j != m; ++j)
            x[s[j]-'A']++;
    }
    for(int i = 0; i != p; ++i)
    {
        fgets(s, 1024, stdin);
        for(int j = 0; s[j] >= 'A' && s[j] <='Z'; ++j)
            x[s[j] - 'A']--;
            
    }
    
    for(int i = 0; i != 26; ++i)
    {
        while (x[i] > 0)fputc(i + 'A', stdout), --x[i];  
    }
    
}
