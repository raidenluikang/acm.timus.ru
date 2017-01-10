




// 1169. Pairs.

#include <cstdio>

static const int N = 128;

char * w;
int n, k, total;
int col[ N ];

char out[1<<19];

void readData()
{
    scanf("%d%d",&n,&k);
    w = out;
}

int digits(int x){ return (x>=100)?3:(x>=10)?2: 1;}

void writeInt(int x, char c)
{
    int n = digits(x);
    for(int i= 0; i != n;++i)
        w[n-i-1] = x % 10 + '0', x/=10;
    w += n;
    *w++ = c;
}

void writeln(int x, int y)
{
    writeInt(x, ' ');
    writeInt(y, '\n');
}
bool search(int left, int need)
{
    if (!need)
        return true;
    
    if (left*(left-1) /2 < need) 
        return false;
    
    for(int l = 3; l <= left; ++l)
    {
        int t = l * ( l - 1 ) / 2;
        ++total;
        col[ total ] = l;
        if ( need >= t )
        {
            if (search(left - l, need - t))
                return true;
            --total;
        }
        else 
        {
            --total;
            break;
        }
    }
    
    return false;
}

int solve()
{
    readData();
    if (n == 1 && k == 0) return 0; // nothing output
    
    if (n == 2)
    {
        if (k == 0)puts("-1");
        else if (k == 1)puts("1 2");
        return 0;
    }
    
    total = 0;
    if (!search(n, n*(n-1) /2 - k))
    {
        puts("-1");
        return 0;
    }
    
    int cur = 0;
    for(int i= 1; i <= total; ++i)
    {
        if (i > 1)
            writeln(1, cur + 1);
    
        for(int j = cur + 1; j <=  cur + col[i]; ++j)
        {
            for(int k = j + 1; k <=  cur + col[i]; ++k)
                writeln(j, k);
        }
        
        cur += col[i];
    }
    if (cur == 0)cur =1;
    for(int i = cur + 1; i <= n; ++i)
    {
        writeln(1,i);
    }
    
    fwrite(out, 1, w - out, stdout);
    return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    solve();
    
}
