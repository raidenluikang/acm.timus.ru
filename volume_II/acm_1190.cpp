 //  acm.timus.ru 1190. Bar of Chocolate


#include <cstdio>


int n;
char const* o;

char in[1<<17];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    n = 0;
    while(*o && *o <= 32)++o;
    while(*o >='0' && *o <= '9') n = n * 10 + (*o++ - '0');
    //scanf("%d\n",&n);
    //printf("n = %d\n",n);
    //return 0;
    int total = 0;
    int zero = 0;
    int total_min = 0, total_max= 0;
    int last = 10000;
    for(int i= 0; i!=n;++i)
    {
        while(*o && *o  != '\n')
            ++o;
        if (*o == '\n')
            ++o;
#if 1
        while (*o >= 'a' && *o <= 'z' ||
                *o >='A' && *o <='Z' ||
                *o == '-' ||
                *o == '_')
            ++o;
        
        if (*o == ' ')++o;
        
        //while(*o != '1' && *o != '0')++o;
        
        char c = *o++ ;
        //printf("char c = '%c'\n", c);
#endif 
        //char c ;
        //int ci;
        //scanf("%s%d",&in,&ci);
        //c = ci + '0';
        if (c == '0')
            zero++;
        else if(c == '1')
        {
            int p = 0;
            //scanf("%d\n",&p);
            ++o; //skip space
          while(*o >='0' && *o <='9') p = (p << 3) + (p << 1) + (*o ++ - '0');
            
            total_min += zero * p    + p;
            total_max += zero * last + p;
            
            zero  = 0;
            last  = p;
        }
        else
        {
            printf("%d\n",1/(c == '0'));
        }
    }
    
    // total += zero;
    
    if ( !(total_min + zero <= 10000 && total_max + last * zero >= 10000 ) )
    {
        puts("NO");
    }
    else
    {
        puts("YES");
    }
    
    return 0;
}
