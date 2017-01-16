

#include <cstdio>
#include <unordered_map>
#include <map>

// 
typedef long long ll;

int N, H, M;
ll K;

std::map<long, ll> A;

int nmax[64][88];
int nmin[64][88];

char const * o;
char in[1<<16];


char * w;
char out[ 1 << 17 ];

void writeLong(ll u, char c)
{
    ll v = u;
    int n = 0,m;
    do ++n; while(v/=10);
    m = n;
    while(m-->0)w[m] = u % 10 + '0', u/=10;
    w += n;
    *w++ = c;
}
void writeInt(int u, char c)
{
    int v = u;
    int n = 0,m;
    do ++n; while(v/=10);
    m = n;
    while(m-->0)w[m] = u % 10 + '0', u/=10;
    w += n;
    *w++ = c;
}

unsigned readInt()
{
    unsigned u = 0;
    while(*o && *o <= 32)++o;
    while(*o >='0' && *o <= '9') u = (u << 3) + (u << 1) + (*o++ - '0');
    return u;
}

ll readLong()
{
    ll u = 0;
    while(*o && *o <= 32)++o;
    if (*o == '-')return -1LL;
    while(*o >='0' && *o <='9') u = (u << 1)+ (u<<3) + (*o++ - '0');
    return u;
}

int NMin(int h, int m)
{
    if (h == m)							/* M, M -1, ..., 1 */
            return m * (m + 1) / 2;
    else if (h < m)
            return m * (m + 1) / 2 - (m - h) * (m - h + 1) / 2;	/* M, M - 1, ..., M - H + 1 */
    else
            return m * (m + 1) / 2 + h - m + (h - m + 1) / 2;	/* M, M - 1, ..., 1, 2, 1, 2, ... */
}

int NMax(int h, int m)
{
    return h * m + h * (h - 1) / 2;					/* M, M + 1, ..., M + H - 1 */
}

long Hash(int n, int h, int m)
{
    // 0<= h <= 60 : 7 bits
    // 0<= m <= 70 : 7 bits
    // 0<= n <= 2375 : 12 bits
    // total: 7 + 7 + 12 = 26 bits < 32 bits
    
    // high 8 bits put h
    // second 8 bits put m
    // low 16 bits put n
    return ( h << 24 ) | (m << 16 ) | n ;
   // return (long)h * 100 * 10000 + (long)m * 10000 + (long)n;
}

ll Solve(int n, int h, int m)
{
    if (m == 0 || n == 0 || n < m)
        return 0;
    
    if (h == 1)
        return 1;
    
    if (n <  nmin[h][m]) //NMin(h, m))
        return 0;

    if (n > nmax[h][m]) //NMax(h, m))
            n = nmax[h][m];//NMax(h, m);
    long hash1 = Hash(n - m, h - 1, m - 1);
    long hash2 = Hash(n - m, h - 1, m + 1);
    ll s1 = -1;
    ll s2 = -1;

    auto s1_it = A.find(hash1);
    
    if (s1_it != A.end())
    {
        s1 = (*s1_it).second;
    }
    else
    {
        s1 = Solve(n - m, h - 1, m - 1);
      //  if (n&1)
            A[hash1] = s1;
    }
    
    auto s2_it = A.find(hash2);
   
    if (s2_it != A.end())
    {
        s2 = (*s2_it).second;
    }
    else
    {
        s2 = Solve(n - m, h - 1, m + 1);
        //if (n & 1)
                A[hash2] = s2;
    }

    if (n & 1)
        A[Hash(n, h, m)] = s1 + s2;

    return s1 + s2;

}

void Recurse(int n, int h, int m, ll k)
{
    if (n > nmax[h][m] ) //NMax(h, m))
        n = nmax[h][m];//NMax(h, m);

    while( h != 1)
    {
        ll s1 = -1;
        long hash = Hash(n - m, h - 1, m - 1);

        if (A.find(hash) != A.end()) 
                s1 = A[hash];
        else
        {
            /* if n is even we don't have it in the map so recompute it */
            s1 = Solve(n - m, h - 1, m - 1);
        }

        if (k > s1)
        {
                /* m + 1 branch */
                writeInt(m+1, ' ');
                k = k - s1; h = h -1; n = n - m; m = m + 1;  //Recurse(n - m, h - 1, m + 1, k - s1);
        }
        else
        {
                /* m - 1 branch */
                writeInt(m-1, ' ');//printf("%d ", m - 1);
                k = k; h = h -1; n = n - m; m = m - 1; //Recurse(n - m, h - 1, m - 1, k);
        }
    }
    *w++ = '\n';
    
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt","w",stdout);
#endif
    for(int h = 0; h <= 63; ++h)
    {
        for(int m = 0; m <= 87; ++m)
        {
            nmin[h][m] = NMin(h,m);
            nmax[h][m] = NMax(h,m);
        }
    }
    
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    w = out;
    
    N = readInt();
    H = readInt();
    M = readInt();
    
    //scanf("%d %d %d", &N, &H, &M);
    
    if (N > NMax(H, M))
            N = NMax(H, M);

    ll sol = Solve(N, H, M);
    //printf("%lld\n", sol);
    writeLong(sol, '\n');
    while (true)
    {
        K = readLong();
        if (K == -1)
            break;
       // scanf("%lld", &K);
        //if (K == -1)
        //        break;
        
        if (K > sol)
                K = sol;

        writeInt(M,' ');
       // printf("%d ", M);
        Recurse(N, H, M, K);
    }

    fwrite(out,1,w- out, stdout);
    return 0;
}
