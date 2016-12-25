

// author c_pp.
// acm.timus.ru 1031. Railway Tickets

#include <cstdio>

static const unsigned N = 10008;
char in[ 1 << 18 ];

char const* o ;

void init_in()
{
    unsigned n;
    n = fread(in, 1, sizeof(in) - 4, stdin);
    in[n] = '\0';
    o = in;
}

unsigned readInt()
{
    unsigned u = 0;
    while(*o && *o <= 32)++o;
    while(*o >= 48) u = (u<<3) + (u<<1) + *o++ - 48;
    return u;
}

unsigned n, L1, L2, L3, C1, C2, C3, a_pos, b_pos; // from a_pos to b_pos
unsigned dp[ N ];
unsigned dst[ N ];

int solve()
{
    init_in();

    L1 = readInt();
    L2 = readInt();
    L3 = readInt();
    C1 = readInt();
    C2 = readInt();
    C3 = readInt();
   
    n = readInt();

    a_pos = readInt();
    b_pos = readInt();

    dst[0] = 0;
    dst[1] = 0;
    for(unsigned i = 2; i<= n; ++i)
    {
        dst[i] = readInt() ;
    }

    //dst[i] = distance from 1 to (i) th stations.
    if ( a_pos > b_pos )
    {
        //change they 
        unsigned t = a_pos;
        a_pos = b_pos;
        b_pos = t;
    }

    dp[ a_pos ] = 0;

    // dp[i] <= dp[i+k], k > 0, so min(dp[i], i = a..b) = dp[a].
    for(unsigned i = a_pos + 1, i_1 = a_pos, i_2 = a_pos, i_3 = a_pos; i <= b_pos; ++i)
    {
        // distance from i_1 to i equal to dst[i] - dst[i_1]
        while( dst[ i ] - dst[ i_1 ] > L1 ) ++ i_1 ;
        while( dst[ i ] - dst[ i_2 ] > L2 ) ++ i_2 ;
        while( dst[ i ] - dst[ i_3 ] > L3 ) ++ i_3 ;
        
        dp[i] = 1234567890;// greater tha 10^9
        // dp[i] = min(dp[i_1] + C1, dp[i_2] + C2, dp[i_3] + C3);
        if (dp[i] > dp[i_1] + C1)
            dp[i] = dp[i_1] + C1;
        if (dp[i] > dp[i_2] + C2)
            dp[i] = dp[i_2] + C2;
        if (dp[i] > dp[i_3] + C3)
            dp[i] = dp[i_3] + C3;
    }

    printf("%u\n", dp[b_pos]);
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
