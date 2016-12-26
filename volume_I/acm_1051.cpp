


// acm.timus.ru 1051. Simple game.
// author solution: c_pp.
// date: 26.12.2016 14:11:40 :)

#include <cstdio>

int calc(int n, int m)
{
    // x    n == 1 and m == 1 -> ans = 1
    // xx   n == 1 and m == 2 -> ans = 1
    // xxx  n == 1 and m == 3 -> ans = 2 
    if ( n == 1 || m == 1) return ( m + n ) / 2;
    //
    // xxx --> xxo      xoo
    // xxx --> xxo  --> xoo
    //           x      0xx 
    //
    if (n % 3 == 0 || m % 3 == 0)
       return 2;

    if (n % 3 == 1 && m % 3 == 1)
       return 1;

    if (n % 3 == 1 && m % 3 == 2)
       return 1;  

    if (n % 3 == 2 && m % 3 == 2)
       return 1;
    if (n % 3 == 2 && m % 3 == 1)
      return 1;
    return 0;
}
int solve()
{

    int n,m;
    scanf("%d%d",&n,&m);
    printf("%d\n",calc(n,m));
    return 0;
}

int main(int argc, char* argv[])
{

#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    solve();

    return 0;
}
