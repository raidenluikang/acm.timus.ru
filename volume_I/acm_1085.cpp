
// acm.timus.ru 1085. Meeting



#include <cstdio>

static inline int min_(int x, int y){ return x < y ? x : y;}
static inline int max_(int x, int y){ return x > y ? x : y;}


static const int N = 100;
static const int M = 100;
static const int L = 100;
static const int K = 100;
static const int MAX_MONEY = 1000; // ruble
static const int PAY_PER_TRAIN = 4; // 4 ruble.
static const int MANY_MONEY = 100000000;
//input data : 
int n_stop, n_train, n_friend; // n - number of stops. m - number of tram routes. 
//int routes[ M ][ L ];
//int rn[ M ]; // rn[i] - number of stops of i-th tram route . 

//int trains[ N ][ M ]; // trains[i][j] -- index of trains running i-th stop
//int tn[ N ]; // number of trains running from i-th stop

bool g[ N ][ N ]; // can i-th stop go j-th stop from one train 

int start[ K ]; // start[i] - start stop number of i-th friend .
int money[ K ];
int ticket[ K ]; // ticket[i] = 1 or 0  means has month ticket or not 

int queue[ N ] ;
int hq, tq ;

// useful data: 
int dist[ K ][ N ]; // dist[ i ][ j ] - minimum pay from start[i]-th stop to j-stop. 


char in[ 1 << 18 ];
char const* o;

int readInt()
{
    //only non-negative integers 
    int u = 0;
    while(*o && *o <=32)++o;
    while(*o >= 48) u  = (u << 3)  + (u << 1)+ (*o++ - 48);
    return u;
}

void readData()
{
    o = in;
    in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;

    n_stop = readInt();
    n_train = readInt();
    for(int i= 0; i != n_train; ++i)
    {
        //rn[i] = readInt();
        hq = readInt();
        for(int j = 0; j != hq; ++j)
        {
            queue[j] = readInt() - 1;
           // routes[i][j] = readInt() - 1;
        }

        for(int j = 0; j != hq; ++j)
        {
            for(int k = 0; k != hq; ++k)
            {
                g[ queue[ j ] ][ queue[ k ] ] = true;
            }
        }
    }

    n_friend = readInt();
    for(int i= 0; i != n_friend; ++i)
    {
        money [ i ] = readInt();
        start [ i ] = readInt() - 1;
        ticket[ i ] = readInt();
    }
}


int solve()
{
    readData();

    //now BFS from every start[i] , i = 0..n_friend-1 
    for(int i_friend = 0; i_friend != n_friend; ++i_friend)
    {
        int const stop = start[i_friend]; // where it starts i-th friend 
        int const money_per_train = ticket[i_friend] ? 0 : PAY_PER_TRAIN ;
        
        for(int i_stop = 0; i_stop != n_stop; ++i_stop)
           dist[ i_friend ][ i_stop ] = MANY_MONEY; // infinity
        
        dist[ i_friend ] [stop] = 0;

        hq = tq = 0;
        queue[tq++] = stop;

        while(hq < tq)
        {
            int const stop = queue[hq++];
            int const money = dist[ i_friend ][ stop ];
            
            for(int i_stop = 0; i_stop != n_stop; ++i_stop)
            {
                if (g[stop][i_stop])
                {
                    if (dist[i_friend][i_stop] > money + money_per_train )
                    {
                        dist[i_friend][i_stop] = money + money_per_train;
                        queue[tq++] = i_stop;
                    }
                }
                
            }
        }
    }
    
    bool cans[N] ={};
    int  sum[N] = {};
    for(int i = 0; i != N;++i)cans[i] = true;
    for(int i_friend = 0; i_friend != n_friend; ++i_friend)
    {
        for(int i_stop = 0; i_stop != n_stop; ++i_stop)
        {
            cans[i_stop] &= (dist[i_friend][i_stop] <= money[ i_friend ]);
            sum[i_stop] += dist[i_friend][i_stop];
        }
    }

    int min_money  = MANY_MONEY ;
    int min_stop = -1;
    for(int i = 0 ;i != n_stop; ++i)
    {
        if (cans[i] && sum[i] < min_money)
        {
            min_money = sum[i];
            min_stop = i;
        }
    }

    if (min_stop < 0)
    {
        puts("0");
    }
    else
    {
        printf("%d %d\n",min_stop + 1, min_money);
    }

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
