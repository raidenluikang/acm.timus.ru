#include <cstdio>
#include <cstdlib>

void myassert(bool b){if(!b)printf("%d",1/b);}
int gcd(int x, int y){return (!y) ? x : gcd(y,x%y);}
const int MAXN = 40;
int N, K;
int F[ MAXN ], Rev[MAXN];
bool divisible[MAXN];
int nextdiv[ MAXN ], prevdiv[ MAXN ], pidiv[ MAXN ];
int lastdiv, firstdiv;

bool candiv  [ MAXN ][ MAXN ] ;
int  G[MAXN][MAXN];
//long long maskdiv [ MAXN ] ;

bool visited[MAXN];

struct cycle_t
{
    int s, e, n ; // s - start, e - end, n - number
    cycle_t(): s(0), e(0), n(0){}
    cycle_t(int s, int e, int n): s(s), e(e),n(n){}
};

cycle_t cycles[ MAXN ]; int nc;
int idxcycles [ MAXN ]; // idxcycles[ cycles[ i ].s ] = i;
int frequence[ MAXN ];

struct group_t
{
    int sum;
    long long mask;

    group_t(): sum(0), mask(0){}

    group_t(int s, long long m): sum(s), mask(m){}

    group_t & operator += (cycle_t const& cycle)
    {
        int i = idxcycles[ cycle.s ];
        sum += cycle.n;
        mask |= 1ll << i ;
        return *this;
    }
    group_t& operator -=(cycle_t const& cycle)
    {
        int i = idxcycles[cycle.s];
        if( (mask & (1ll << i)))
        {
            sum -= cycle.n;
            mask ^= (1ll << i);
        }
        return *this;
    }
};


group_t groups[ MAXN ]; int ng;


bool checkF(){
    for(int i = 1; i <= N; ++i)if(F[i] == 0)return false;
   // return true;
    for(int i = 1; i<= N; ++i)visited[i] = false;

    for(int i = 1; i<= N; ++i){
        if(!visited[i]){
            int s = i, n = 0;
            while(!visited[s])
            {
                visited[s] = true;
                ++n;
                s = F[ s ];
            }
            if (s != i)return false;
            if (!divisible[n])return false;
        }
    }
    return true;
}
void writeNo(){
    printf("No\n");
    exit(0);
}
void writeYes(){
//    myassert(checkF());
    printf("Yes\n");

    for(int i = 1; i<=N;++i){
        printf("%d ",F[i]);
    }
    printf("\n");
    exit(0);
}

void ReadInit()
{
    scanf("%d%d",&N,&K);
    divisible[0] = false;
    for(int i = 1; i<= N; ++i)divisible[i] = K % i == 0;

    for(int i = 1; i<= N; ++i)scanf("%d",F + i);

    bool self = true;

    for(int i = 0; i < MAXN;++i)Rev[i] = 0;

    for(int i = 1; i<= N; ++i)
    {
        if( F[ i ] == 0 )continue;

        if ( Rev[ F[ i ] ] > 0)writeNo();
        Rev[ F[ i ] ] = i;
        self = self && F[i] == i;
    }

    if (self){
        for(int i = 1; i<=N;++i)F[i] = i;
        writeYes();
    }

    //N == 1 --> self==true
    // K == 1 -->
    if( K == 1 )writeNo();

    //memset(divisible, 0, sizeof(divisible));

    lastdiv = 1;
    for(int i = 1; i <= N; ++i)if(divisible[i])lastdiv = i;

    firstdiv = 1;
    for(int i = N; i > 1; --i)if(divisible[i])firstdiv = i;

    if ( lastdiv == 1) // there no divisible in [2..N] for K.
      writeNo();

    nextdiv[ N + 1 ] = MAXN ;
    for(int i = N; i >= 1; --i){
        if(divisible[i])
            nextdiv[i] = i;
        else
            nextdiv[i] = nextdiv[i+1];
    }

    prevdiv[ 0 ] = 0;
    for(int i = 1; i<=N;++i){
        if(divisible[i])
            prevdiv[i] = i;
        else
            prevdiv[i] = prevdiv[i-1];
    }

    pidiv[0] = 0;
    for(int i = 0, c = 0; i <= N; ++i)
    {
        c += int(divisible[i]);
        pidiv[ i ] = c; // number of divisibles up to i.
    }
}

void BuildCycles()
{
    nc = 0;
    for(int i = 0; i < MAXN; ++i)visited[i] = false;

    for(int i = 1; i<= N; ++i)
    {
        if(visited[ i ])continue;
        if( F[ i ] == 0 )continue;

        cycle_t c;
        c.n = 0;
        c.s = i;
        c.e = i;

        while( ! visited[c.e])
        {
            visited[c.e] = true;
            ++c.n;
            if(F[c.e] == 0)break;
            c.e = F[ c.e ];
        }

        while(Rev[c.s] != 0 && !visited[ Rev[ c.s ] ])
        {
            c.s = Rev[c.s];
            ++c.n;
            visited[c.s] = true;
        }

        if (F[c.e] != 0)
        {
            if (! divisible[c.n] )writeNo();
            continue;
        }

        if( c.n > lastdiv)writeNo();

        if (c.n == lastdiv){
            F[ c.e ] = c.s;
            continue;
        }

        cycles[ nc++ ] = c;
    }

    for(int i = 1; i <= N; ++i)
    {
        if( ! visited[ i ] )
        {
            myassert(F[i] == 0 && Rev[i] == 0 );
            cycle_t c;
            c.s = i;
            c.e = i;
            c.n = 1;
            cycles[ nc++ ] = c;

            visited[i] = true;
        }
    }

    //sort by increasing order of cycle.n
    for(int i = 0; i < nc; ++i)
        for(int j = i+1; j < nc; ++j)
            if(cycles[i].n > cycles[j].n){
                cycle_t tmp = cycles[i];
                cycles[i] = cycles[j];
                cycles[j] = tmp;
            }

    for(int i = 0; i < nc; ++i)
        idxcycles[ cycles[i].s ] = i;

    bool alldiv = true;
    for(int i = 0; i < nc; ++i)
        alldiv = alldiv && divisible[cycles[i].n];
    if (alldiv)
    {
        for(int i = 0; i < nc; ++i)F[cycles[i].e] = cycles[i].s;
        writeYes();
    }


    for(int i = 0; i < MAXN; ++i)frequence[i] = 0;
    for(int i = 0; i < nc; ++i)frequence[ cycles[ i ].n ] ++;

    int g = 0; for(int i = 0; i < nc; ++i)g = gcd(cycles[i].n, g);

    if ( ! divisible[ g ])writeNo();

}

void buildgroup(group_t const& g)
{
    int s = -1, t = -1;
    if (g.mask == 0)return;
    myassert(divisible[g.sum]);
    for(int i = 0; i < nc; ++i)
    {
        if(g.mask & (1ll << i)){
            if(s==-1)s =  t = i;

            F[ cycles[ i ].e] = cycles[t].s;
            t = i;
        }
    }
    F[cycles[s].e] = cycles[t].s;
}

void downto_lastdiv()
{
    int s = 0;

    for(int i = 0; i < nc; ++i)s += cycles[i].n;

    if(s == lastdiv)
    {
        //all
        buildgroup( group_t(s, (1ll << nc)-1 ) ) ;
        writeYes();
    }

    if(s > lastdiv )return ;

    if( s == 0 )writeYes();

    // s < lastdiv

    lastdiv = prevdiv[ s ];

    if (cycles[ nc - 1 ].n > lastdiv)writeNo();

    while(nc > 0 && cycles[nc-1].n == lastdiv){
        F[cycles[nc-1].e] = cycles[nc-1].s;
        --nc;
    }

    if (nc > 1 && !divisible[cycles[nc-1].n] && (cycles[nc-1].n + cycles[0].n > lastdiv ))
        writeNo();

    downto_lastdiv();
}

void simpleSolve()
{
    int s = 0;
    for(int i = 0; i < nc; ++i)
    {
        if(!divisible[cycles[i].n])s += cycles[i].n;
    }

    if (s == 0)//all divisible
    {
        for(int i = 0; i<nc; ++i)F[cycles[i].e] = cycles[i].s;
        writeYes();
    }

    if(divisible[s])
    {
        group_t g;
        for(int i = 0; i < nc; ++i)
            if(!divisible[cycles[i].n])
                g += cycles[i];
            else
                F[cycles[i].e] = cycles[i].s;

        buildgroup( g );
        writeYes();
    }
} // end simpleSolution

void buildCan()
{

    G[ 0 ][ 0 ] = 1;
    for(int i = 1; i <= frequence[1]; ++i)
    {
        G[0][i] = 1 | ( 1 << 1 ) | (0 << 8);
    }

    // if G[i][j] = true --> G[i][j + k]=   true, also
    for(int i = 1; i <= frequence[2]; ++i)
    {
        for(int j = 0; j <= frequence[1]; ++j)
        {
            G[ i ][ j ] = 0;

            for(int u = 0; u <= i; ++u)
            {
                for (int v = 0; v <= j; ++v)
                    if ( divisible[u * 2 + v ] && G[i - u][j - v]) {
                        G[i][j] = 1 | (v << 1) | (u << 8);
                        u = 40, v = 40;//break
                    }
            }
        }
    }
}

void recurse(int p)
{
    if (p == 0){
        bool yes = true;
        for(int i = 0; i < ng; ++i)yes = yes && divisible[groups[i].sum];
        if(!yes)return ;
        for(int i = 0; i < ng; ++i)buildgroup(groups[i]);
        writeYes();
    }

    //if( cycles[ p - 1 ].n > 2 )


    if (cycles[p-1].n == 1)
    {
        int s = 0;
        for(int i = 0; i < ng; ++i)
            s += nextdiv[ groups[ i ].sum ] - groups[ i ].sum;
        if(s > p )return ;
        //s <= p
        int k = 0;
        for(int i = 0; i < ng; ++i)
        {
            for(int dx = nextdiv[groups[i].sum] - groups[i].sum; dx > 0; --dx){

                    groups[i] += cycles[k++];

            }
        }

        for( ; k < p; ++k)
        {
            groups[ ng++ ] = group_t(cycles[k].n, 1ll << k);
        }
        for(int i = 0; i < ng; ++i)buildgroup(groups[i]);
        writeYes();
    }

    // cycles[p-1].n == 2
    if(cycles[p-1].n == 2)
    {
        int  const freq1 = frequence[ 1 ];
        int  const freq2 = p - freq1;

        int idx1 = 0, idx2 = freq1;

        myassert(cycles[idx2].n == 2);

        int s2 = 0, odd = 0;

        for (int i = 0; i < ng; ++i)
        {
            int dx = nextdiv[groups[i].sum] - groups[i].sum;
            int o = dx & 1;
            odd += o;
            s2 += dx - o;
        }

        if (odd <= freq1 && s2 <= freq2 * 2 + freq1 - odd)
        {
            if (divisible[ 2 ] || s2 >= freq2 * 2)
            {
                // urra find solution.
                for (int i = 0; i < ng; ++i) {
                    int dx = nextdiv[groups[i].sum] - groups[i].sum;
                    if (dx & 1) {
                        groups[i] += cycles[idx1++];
                        --dx;
                    }
                    while (dx > 0 && idx2 < p)
                    {
                        groups[i] += cycles[idx2++];
                        dx -= 2;
                    }
                    while(dx > 0)
                        groups[i] += cycles[idx1++], dx--;
                }

                while (idx2 < p) {
                    groups[ng++] = group_t(cycles[idx2].n, 1ll << idx2);
                    ++idx2;
                }
                while (idx1 < freq1) {
                    groups[ng++] = group_t(cycles[idx1].n, 1l << idx1);
                    ++idx1;
                }
                for (int i = 0; i < ng; ++i)buildgroup(groups[i]);
                writeYes();
            }

            // ! divisible[2] && s2 < freq2 * 2
            int remain2 =  freq2 - s2 / 2 ;
            int remain1 = freq1 - odd;

            if ( G[ remain2 ][ remain1 ] )
            {

                // a found solution.
                // urra find solution.
                for (int i = 0; i < ng; ++i)
                {
                    int dx = nextdiv[groups[i].sum] - groups[i].sum;
                    if (dx & 1) {
                        groups[i] += cycles[idx1++];
                        --dx;
                    }
                    while (dx > 0) {
                        groups[i] += cycles[idx2++];
                        dx -= 2;
                    }
                }

                while(remain2 > 0)
                {
                    int gval = G[ remain2 ][ remain1 ];
                    int u1 = (gval >> 1) & 127;
                    int u2 = (gval >> 8) & 127;

                    group_t g;
                    myassert(divisible[u2*2 + u1]);
                    for(int u = 0; u < u1; ++u)g += cycles[idx1++];
                    for(int v = 0; v < u2; ++v)g += cycles[idx2++];

                    groups[ng++] = g;

                    remain2 -= u2;
                    remain1 -= u1;
                }

                while(remain1-->0)groups[ng++] = group_t(cycles[idx1].n, 1ll << idx1), ++idx1;

                for (int i = 0; i < ng; ++i)buildgroup(groups[i]);
                writeYes();

            }
            else
            {
                if(p == nc)writeNo();
                //return ;


            }
        } // if s2 <= freq2 && odd <= freq1
        else
        {

            // WELL : this return Gives ACCEPTED 0.015 s.
            return;
        }
    } // end if (cycles[p-1].n == 2).


    // groups[i].n >= 2;
    {

        // or ADD  cycles[p-1] to a new group.
        groups[ng++] = group_t(cycles[p-1].n, 1ll << (p-1));


        recurse(p-1);

        --ng;

        for(int i = 0; i < ng; ++i){
            if(groups[i].sum + cycles[p-1].n <= lastdiv){
                groups[i] += cycles[p-1];

                recurse( p - 1);

                groups[i] -= cycles[ p - 1 ];
            }
        }

    }
}
void recursiveSolve()
{
    buildCan();

    ng = 0;

    recurse( nc );

    writeNo();
}

int solve()
{
    ReadInit();

    BuildCycles();

    downto_lastdiv();

    simpleSolve();

    recursiveSolve();

    return 0;
}

int main(int argc, char* argv[]){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    solve();

    return 0;
}
