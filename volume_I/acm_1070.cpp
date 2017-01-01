

// acm.timus.ru 1070. Local Time



#include <cstdio>

char in[1024];
const char* o ;

int readTime()
{
    int t = 0;
    while(*o && *o <= 32)++o;
    while(*o >= 48 && *o <= 57)t = t * 10 + *o++ - 48;
    
    t = 60 * t;// convert to minutes
    if (*o == '.') // a minute
    {
        ++o;
        int m = 0;
        while(*o >= 48 && *o <= 57)m = m  * 10 + *o++ - 48;
        t += m;
    }
    return t;

}

int main(int argc, char* argv[])
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    
   
    
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    
    int t_0 = readTime();
    int t_1 = readTime();
    int h_0 = readTime();
    int h_1 = readTime();
    
    if ( t_1 < t_0) t_1 += 24 * 60;
    if ( h_1 < h_0) h_1 += 24 * 60;
    
    
    
    int dif_t = t_1 - t_0;
    int dif_h = h_1 - h_0;
    
    for(int r = 0; r != 6;++r)
    {
        // r - hours different
        // so 
        
        
        // dif_t + r*60    and dif_h - r * 60  musdn't diff than 10 minutes
        //1. if h - city r hour far
        // and flieht time is  x  , y  
        
        // t_0 + x  + r = t_1  
        // h_0 + y  - r = h_1
        // x + r = dif_t
        // y - r = dif_h
        // (x-y) + 2r = dif_t - dif_h ,  we know  |(x-y)| <= 10
        // let a = x - y  -->  2r = dif_t - dif_h - a
        // (x-y) = dif_t - dif_h - 2r
        int dd = dif_t - dif_h -   r * 120;
        if (dd >= -10 && dd <= 10)
        {
            printf("%d\n",r);
            return 0;
        }
        dd = dif_h - dif_t - r * 120;
        if (dd >= -10 && dd <= 10)
        {
            printf("%d\n",r);
            return 0;
        }
    }

    printf("5\n");
    
    return 0;
}
