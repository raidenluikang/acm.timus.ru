/// 1196. History Exam


#include <cstdio>
#include <set>
#include <unordered_set>
#include <algorithm>


char const*o;
char in[1<<23];

unsigned d[15000];

static 
unsigned readInt()
{
    unsigned u = *o++ - '0';
    while(*o >='0') u = (u << 3) +(u << 1) + (*o ++ -'0');
    
    return ++o, u;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    //std::set<unsigned int> s;
    unsigned int n;
    unsigned int r = 0;
    unsigned int m;
    
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    n = readInt();
    
    std::unordered_set<unsigned> s;
    for(unsigned i = 0 ; i!=n;++i)
    {
        unsigned x = readInt();
        //d[i] = x;
         s.insert(x);
    }
    
    m = readInt();
    
    for(unsigned i = 0; i != m; ++i)
    {
        unsigned x = readInt();
        r += s.count(x);
        //r += std::binary_search(d, d + n, x);//s.count(x);
    }
    
    printf("%u\n",r);
    
    return 0;
}
