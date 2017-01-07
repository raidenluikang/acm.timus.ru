


#include <cstdio>
#include <cmath>

#include <algorithm>

static const int N = 10008;

struct node
{
    int x;
    int i;
};
bool operator < (node const& lhs, node const& rhs){ return lhs.x > rhs.x; }

node d[N];
int n;
char in[1<<18];
const char* o;

void readData();
int readInt()
{
    unsigned u = 0, s = 0;
    while(*o && *o <= 32)++o;
    if (*o == '-')s = ~0, ++o; else if (*o == '+')++o;
    while(*o >='0' && *o <='9') u = (u << 3) + (u << 1) + (*o++ - 48);
    return (u ^ s) + !!s;
}

void readData()
{
    o = in;
    in[fread(in,1,sizeof(in),stdin)] = 0;
    n = readInt();
    for(int i = 0, y; i != n; ++i)
    {
        d[i].x = readInt();
        y = readInt();
        //d[i].y = readInt();
        d[i].i = i;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    
    readData();
    
    std::sort(d, d + n);
    
    char * w =in + sizeof(in);
    
    for(int i= 0; i < n; i += 2)
    {
        unsigned u = d[i].i + 1, v = d[i+1].i + 1;
        *--w = '\n';
        do *--w = u % 10 + '0'; while(u/=10);
        *--w = ' ';
        do *--w = v % 10 + '0'; while(v/=10);
    }
    
    fwrite(w, 1, in + sizeof(in) - w, stdout);
    return 0;
}
