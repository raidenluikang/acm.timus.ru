
#include <cstdio>


int main()
{
    char line[1024];
    int n, r ;
    fgets(line, 1024, stdin);
    
    sscanf(line, "%d",&n);
    
    r = 2; // Marshall and Lilli
    for(int i= 0; i != n;++i)
    {
        bool b = false;
        fgets(line, 1024, stdin);
        ++r;
        for(int j= 0; line[j] != '\n' && line[j] > 0; ++j)
            b = b || (line[j] == '+');
        
        r += b;
    }
    if (r == 13)
        ++r;
    printf("%d\n", r* 100);
    return 0;
}
