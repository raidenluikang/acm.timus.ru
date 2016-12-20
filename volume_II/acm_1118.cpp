

// acm.timus.ru 1118. Nontrivial Numbers.

#include <cstdio>
#include <cstring>

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    unsigned int x,y,n;
    scanf("%u%u",&x,&y);
    if (x == 1)
    {
        n = 1;//triviality(1) = 0
    }
    else  
    {
        double min_triviality = 1.0E+8;
        n = x;
        for( ; x <= y; --y)
        {
            //1. check x - is prime
            bool prime = true;
            int d = 1;
            for(int t = 2; t*t <= y; ++t)
            {
                if (y%t == 0)
                {
                    prime = false;
                    d += t;
                    if (t*t < x)d += y / t;
                }
            }
            if (prime )
            {
                n = y;

                break;
            }
            else
            {
                double triv = d/(double)y;
                if (triv < min_triviality)
                {
                    min_triviality = triv;
                    n = y;
                }
            }
        }

    }
    printf("%u\n",n);
    return 0;
}
