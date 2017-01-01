#include <cstdio>
#include <cstdlib>

char in[ 4096 ];
char const*o ;

int n;
int pos[51];

bool diag [ 108 ]  = {}; // x + y  -- queen
bool diag2[ 108 ]  = {}; // x - y + n  -- queen 

int check(int i, int j, int k)
{
    // i <-- j    j <--- k    k <--- old i
    // check can obtained peaceful position
    // (i, pos[i])
    // (j, pos[j])
    // (k, pos[k])
    
    // 1. horizontal positions always filled
    // 2. vertical positions always filled
   
    //...........................................................
    // i-th:   .......Q1...............P2....................
    ///.....................................................
    ///.....................................................
    // j-th    ...............P3.......Q2....................
    //........................................................
    ///........................................................
    //k-th ...........P1......Q3...............................
    //...........................................................
    
    int si = i + pos[i], sj = j + pos[j], sk = k + pos[k];
    int mi = i - pos[i] + n, mj = j - pos[j] + n, mk = k - pos[k] + n;
    
    bool res = false;
    
    diag[si] = diag[sj] = diag[sk] = false;
    
    diag2[mi] = diag2[mj] = diag2[mk] = false;
    
    int hi = i + pos[j], hj = j + pos[k], hk = k + pos[i];
    int li = i - pos[j] + n, lj = j - pos[k] + n, lk = k - pos[i] + n;
    
    res = !diag[ hi ] && !diag[hj] && !diag[hk] && (hi != hj && hi != hk && hj != hk) &&
          !diag2[li] && !diag2[lj] && !diag2[lk] && (li != lj && li != lk && lj != lk);
    
    diag[si] = diag[sj] = diag[sk] = true;
    
    diag2[mi] = diag2[mj] = diag2[mk] = true;
    
    return res;
}

int readInt()
{
    int u = 0;
    while(*o && *o <= 32)++o;
    while(*o >= 48 && *o <= 57) u = (u << 3) + (u << 1) + (*o ++ - 48);
    return u;
}

void swap(int i, int j, int k)
{
   int  tmp = pos[i]; 
   pos[i] = pos[j];
   pos[j] = pos[k]; 
   pos[k] = tmp;
}


void judge_assert(bool b){if (!b)printf("%d\n",1/b);}

int  main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    n = readInt();
    for(int i= 1; i <= n; ++i)
        pos[i] = 0;
    
    for(int i = 1; i <=n;++i)
    {
        int x, y;
        x = readInt();
        y = readInt();
        judge_assert(pos[x] == 0);
        pos[x] = y;
        
        diag  [ x + y    ] = true;
        diag2 [ x - y + n] = true;
    }
     
    
    int ans = 0;
     for ( int  i = 1 ;i <= n - 2 ; ++ i)
         for ( int  j = i + 1 ;j <= n - 1 ; ++ j)
             for ( int  k = j + 1 ;k <= n; ++ k)
             {
                 //swap(i,j,k);
                 ans += check(i,j,k);
                 
                 //     j k i
                 //swap(i,j,k);   
                 ans += check( i, k, j);
                 //swap(i,j,k);
            }
    printf("%d\n",ans);
     return   0 ;
}
