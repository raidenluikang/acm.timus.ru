

//acm.timus.ru 1029. Ministry

#include <cstdio> // fread/fwrite  printf scanf
#include <cstring> // memset, memcpy

#ifdef _MSC_VER 

#define JUDGE_ALIGN_P   __declspec(align(64))
#define JUDGE_ALIGN_S    

#else 

#define JUDGE_ALIGN_P   
#define JUDGE_ALIGN_S __attribute__((aligned(8)))

#endif


static const unsigned N = 508;
static const unsigned M = 108;

JUDGE_ALIGN_P
char in[1 << 20] JUDGE_ALIGN_S ;
// N*M = 5*10^4 numbers each 10 digit + 1 for space/line break = > total 12 symbol: < 10^6 symbol

JUDGE_ALIGN_P 
unsigned fee[ N ] JUDGE_ALIGN_S; 

JUDGE_ALIGN_P 
unsigned dp[ 2 ][ N ] JUDGE_ALIGN_S;

JUDGE_ALIGN_P 
unsigned char prev[ M ][ N ] JUDGE_ALIGN_S;


JUDGE_ALIGN_P
int plist[ 65536 ] JUDGE_ALIGN_S;

int np;
unsigned n,m;

const char* o;


int solve()
{
     int cur_i = 0, next_i = 1;
     memset(dp, 0, sizeof(dp));
     memset(prev, 0, sizeof(prev)); // 0 - no used, 1 - from down, 2 - from left, 3 - from right
     memset(fee , 0, sizeof(fee));
    //printf("sizeof node = %d\n", sizeof(node));
    //1. read data 
    {
        n = fread(in,1,sizeof(in) - 4, stdin);
        in[n] = '\0';
        o = in;

        n = m = 0;

        //1. m 
        while(*o && *o <= 32)++o;
        while(*o>= 48) m = (m<<3) + (m<<1) + *o++ - 48;

        //2. n 
        while ( *o && *o <= 32 ) ++ o;
        while ( *o >= 48 ) n = ( n << 3 ) + ( n << 1 ) + *o++ - 48;

        //3. fee 
        for(unsigned i = 1; i <= m; ++i)
        {
            fee[0] = 0;
            for(unsigned j = 1; j <= n;++j)
            {
                fee[j] = 0;
                while(*o && *o <= 32)++o;
                while(*o >= 48)fee[j] = (fee[j] << 3) + (fee[j] << 1) + *o ++ - 48;
            }
            
            for(unsigned j = 1; j <= n; ++j)
            {
                dp[next_i][j] = dp[cur_i][j] + fee[j];
                prev[i][j] = 1; 
            }

            for(unsigned j = 2; j <= n; ++j)
            {
                if (dp[next_i][j] > dp[next_i][j-1] + fee[j])
                {
                    dp[next_i][j] = dp[next_i][j-1] + fee[j];
                    prev[i][j] = 2;
                }
            }

            for(unsigned j = n-1; j >= 1; --j)
            {
                if (dp[next_i][j] > dp[next_i][j+1] + fee[j])
                {
                    dp[next_i][j] = dp[next_i][j+1] + fee[j];
                    prev[i][j] = 3;
                }
            }

            cur_i  ^= 1 ;
            next_i ^= 1 ;
        }
        
    }//end read data

    unsigned ans = 0xFFFFFFFF;
    unsigned ar = 0, ac = 0;
    for(unsigned c = 1; c <= n; ++c)
    {
        if (dp[cur_i][c] < ans && prev[m][c] == 1)
        {
            ans = dp[cur_i][c];
            ar = m;
            ac = c;
        }
    }

    np = 0;
    while(ar >= 1)
    {
        plist[ ++np ] = ac;
        switch(prev[ar][ac])
        {
            case 0: break;
            case 1: // from down -
               --ar;break;
            case 2: // from left 
               --ac; break;
            case 3: // from right 
              ++ ac;
              break;
        }
    }

    //III. write result 
    char * w = in;
    for(int i = np; i > 0; --i)
    {
        unsigned u = plist[i];
        unsigned v = u, vn = 0, wn;
        do vn++; while(v/=10);
        wn = vn;
        while(vn-->0)w[vn] = u%10 + '0', u/=10;
        w += wn;
        *w ++ = ' ';
    }
    w[-1] = '\n';
    //flush 
    fwrite(in, 1, w - in, stdout);
    return 0;
}

int main(int argc, char * argv[])
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    solve();

    return 0;
}
