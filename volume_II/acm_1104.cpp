//1104. Don’t Ask Woman about Her Age

#include <cstdio>

// given a number , find minimum base which this number divisible to base-1

//  A = sum(d[i] * base^i)
//  base^i = (base-1 + 1)^i = V*(base-1) + 1
//  A divisible to base-1, only if sum of digits divisible to base-1

static const unsigned char digit[128] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 
0, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 

};

char in[ 1 << 20 ];

bool visit[128] = {};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    int n, s = 0;
    n = fread(in,1,sizeof(in)-4,stdin);
    
    for(int i = 0; i != n; ++i)
    {
        visit[in[i]] = true;
        s += digit[in[i]];//( in[ i ] >='A' ) ? ( in[ i ] - 'A' + 10 ) : ( (in[i] >='0' ? in[ i ] - '0' : 0));
    }
    
    int b = 127;
    while ( b > 0 && !visit[b])--b;
    
    if (b >='A')
        b = b- 'A' + 10 + 1;
    else
        b = b - '0' + 1;
    
    if (b < 2) b = 2;
    // b - minimum base
    while (b <= 36 && s%(b-1) != 0) ++ b;
    
    if (b > 36)
    {
        puts("No solution.");
    }
    else
    {
        printf("%d\n",b);
    }
    
    
}
