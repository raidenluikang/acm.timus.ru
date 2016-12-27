

// acm.timus.ru 1078. Segments


#include <cstdio>

#include <algorithm> // sort, and swap c++03 mode
#include <utility> // swap in c++11 mode 

static const int N  = 500;

struct segment
{
    int a, b, i; // a and b - is endpoints  a<=b , i - index of segment

};

struct segment_cmp
{
    bool operator()(segment const& lhs, segment const& rhs)const 
    {
        return (lhs.b - lhs.a) < (rhs.b - rhs.a); // compare by length of segments
    }
};

segment s[ N ];
int n;
int dp[ N ];
int pv[ N ];
int ans_dp = 0;
int ans_idx = 0;
int ans_arr[N];
int na = 0;

char in[ 65536 ] ;
char const* o    ;

static inline 
int readInt()
{
    unsigned s = 0, u = 0;

    while(*o && *o <= 32)++o;
    if (*o == '-')s = ~s, ++o;
    else if (*o == '+') ++o;

    while(*o >= 48) u = ( u << 3 ) + ( u << 1 ) + ( *o++ - 48 );
   
    return static_cast< int >( (u ^ s) + !!s );
}

static 
int readData()
{
    o = in;
    in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;

    n = readInt();
    for(int i = 0; i != n; ++i)
    {
        s[i].a = readInt();
        s[i].b = readInt();
        s[i].i  = i;
        if (s[i].a > s[i].b)
            std::swap( s[ i ].a, s[ i ].b );
    }

    return 0;
}

int solve()
{

    readData();

    std::sort(s, s + n, segment_cmp());

    for(int i = 0; i!=n;++i)
    {
        dp[i] = 1; // itself
        pv[i] = -1; // nothing

        for(int j= 0; j < i; ++j)
        {
            // length of s[j] < s[i]
            if (s[j].a > s[i].a && s[j].b < s[i].b ) // s[i] outside of s[j] segment 
            {
                if (dp[i] < 1 + dp[j])
                {
                    dp[i] = 1 + dp[j];
                    pv[i] = j;
                }
            }
        }
    }

    for(int i= 0; i != n; ++i)
    {
        if (dp[i] > ans_dp)
        {
            ans_dp = dp[i];
            ans_idx = i;
        }
    }

    char *w = in + 16384;
    for(int i= 0; i != ans_dp; ++i, ans_idx = pv[ans_idx])
    {
        unsigned u = s[ans_idx].i + 1;
        *--w = ' ';
        do *--w = u % 10 + '0'; while(u/=10);
    }
    *--w = '\n';
    do *--w = ans_dp % 10 + '0'; while(ans_dp/=10);
    in[16383] = '\n';
    fwrite(w, 1, in + 16384 - w, stdout);
    
    



    return 0;
}
int main(int argc, char *argv[])
{

#ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
#endif
    solve();
    return 0;
}
